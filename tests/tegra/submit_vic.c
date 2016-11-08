/*
 * Copyright © 2015 NVIDIA Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <tegra_drm.h>

#include "host1x.h"
#include "vic04.h"
#include "xf86drm.h"
#include "tegra.h"

static const char default_device[] = "/dev/dri/card0";

int main(int argc, char *argv[])
{
	struct drm_tegra_get_syncpt get_syncpt_args;
	struct drm_tegra_bo *cmdbuf_bo, *histbuf_bo, *outbuf_bo,
		*configbuf_bo;
	uint32_t cmdbuf_bo_handle, histbuf_bo_handle,
		outbuf_bo_handle, configbuf_bo_handle;
	struct drm_tegra_open_channel open_channel_args = {0};
	struct drm_tegra_syncpt submit_syncpt_incr = {0};
	struct drm_tegra_cmdbuf submit_cmdbuf = {0};
	struct drm_tegra_submit submit_args = {0};
	struct drm_tegra_reloc submit_relocs[3];
	struct drm_tegra_syncpt_wait wait_args = {0};
	ConfigStruct *config_struct;
	struct drm_tegra *tegra;
	drmVersionPtr version;
	const char *device;
	uint32_t *cmdbuf;
	uint32_t *outbuf;
	uint32_t i, j;
	void *histbuf;
	int err, fd;

	if (argc < 2)
		device = default_device;
	else
		device = argv[1];

	fd = open(device, O_RDWR);
	if (fd < 0) {
		printf("Failed to open device %s\n", device);
		return fd;
	}

	version = drmGetVersion(fd);
	if (version) {
		printf("Version: %d.%d.%d\n", version->version_major,
		       version->version_minor, version->version_patchlevel);
		printf("  Name: %s\n", version->name);
		printf("  Date: %s\n", version->date);
		printf("  Description: %s\n", version->desc);

		drmFreeVersion(version);
	}

	err = drm_tegra_new(&tegra, fd);
	if (err < 0) {
		printf("Failed to open Tegra DRM device (%d)\n", err);
		return err;
	}

	/* open channel */
	open_channel_args.client = HOST1X_CLASS_VIC;
	err = drmIoctl(fd, DRM_IOCTL_TEGRA_OPEN_CHANNEL, &open_channel_args);
	if (err) {
		printf("Failed to open channel (%d)\n", err);
		return err;
	}

	/* allocate cmdbuf */
	err = drm_tegra_bo_new(&cmdbuf_bo, tegra, 0, 4096);
	if (err) {
		printf("Failed to create cmdbuf (%d)\n", err);
		return err;
	}

	/* get command buffer handle */
	err = drm_tegra_bo_get_handle(cmdbuf_bo, &cmdbuf_bo_handle);
	if (err) {
		printf("Failed to get cmdbuf handle (%d)\n", err);
		return err;
	}

	/* map cmdbuf */
	err = drm_tegra_bo_map(cmdbuf_bo, (void **)&cmdbuf);
	if (err) {
		printf("Failed to mmap cmdbuf (%d)\n", err);
		return err;
	}

	/* create the config struct buffer */
	err = drm_tegra_bo_new(&configbuf_bo, tegra, 0, sizeof(ConfigStruct));
	if (err) {
		printf("Failed to create config struct (%d)\n", err);
		return err;
	}

	/* get command buffer handle */
	err = drm_tegra_bo_get_handle(configbuf_bo, &configbuf_bo_handle);
	if (err) {
		printf("Failed to get cmdbuf handle (%d)\n", err);
		return err;
	}

	/* get offset for the config struct buffer */
	err = drm_tegra_bo_map(configbuf_bo, (void **)&config_struct);
	if (err) {
		printf("Failed to mmap config struct (%d)\n", err);
		return err;
	}

	/* allocate the hist buffer */
	err = drm_tegra_bo_new(&histbuf_bo, tegra, 0, 4096);
	if (err) {
		printf("Failed to create histbuf (%d)\n", err);
		return err;
	}

	/* get command buffer handle */
	err = drm_tegra_bo_get_handle(histbuf_bo, &histbuf_bo_handle);
	if (err) {
		printf("Failed to get histbuf handle (%d)\n", err);
		return err;
	}

	/* get offset for the hist buffer */
	err = drm_tegra_bo_map(histbuf_bo, (void **)&histbuf);
	if (err) {
		printf("Failed to mmap histbuf (%d)\n", err);
		return err;
	}

	/* allocate the output surface */
	err = drm_tegra_bo_new(&outbuf_bo, tegra, 0, 32 * 1024);
	if (err) {
		printf("Failed to create outbuf (%d)\n", err);
		return err;
	}

	/* get command buffer handle */
	err = drm_tegra_bo_get_handle(outbuf_bo, &outbuf_bo_handle);
	if (err) {
		printf("Failed to get outbuf handle (%d)\n", err);
		return err;
	}

	/* get the offset for the outbuf */
	err = drm_tegra_bo_map(outbuf_bo, (void **)&outbuf);
	if (err) {
		printf("Failed to mmap outbuf (%d)\n", err);
		return err;
	}

	/* get channel syncpoint */
	get_syncpt_args.context = open_channel_args.context;
	get_syncpt_args.index = 0;
	err = drmIoctl(fd, DRM_IOCTL_TEGRA_GET_SYNCPT, &get_syncpt_args);
	if (err) {
		printf("Failed to get syncpoint (%d)\n", err);
		return err;
	}

	memset(histbuf, 0, 4096);

	memset(config_struct, 0, sizeof(*config_struct));
	config_struct->outputConfig.TargetRectRight = 199;
	config_struct->outputConfig.TargetRectBottom = 31;
	config_struct->outputConfig.BackgroundAlpha = 1023;
	config_struct->outputConfig.BackgroundR = 0;
	config_struct->outputConfig.BackgroundG = 1023;
	config_struct->outputConfig.BackgroundB = 0;

    config_struct->outputSurfaceConfig.OutPixelFormat = 34; /* R8G8B8A8 */
    config_struct->outputSurfaceConfig.OutSurfaceHeight = 31;
    config_struct->outputSurfaceConfig.OutSurfaceWidth = 199;
	config_struct->outputSurfaceConfig.OutLumaWidth = 255;
	config_struct->outputSurfaceConfig.OutLumaHeight = 31;
	config_struct->outputSurfaceConfig.OutChromaWidth = 16383;
	config_struct->outputSurfaceConfig.OutChromaHeight = 16383;

	i = 0;
	cmdbuf[i++] = host1x_opcode_setclass(HOST1X_CLASS_VIC, 0, 0);

	/* setup size of config_struct */
	cmdbuf[i++] = host1x_opcode_incr(VIC_UCLASS_METHOD_OFFSET, 2);
	cmdbuf[i++] = NVB0B6_VIDEO_COMPOSITOR_SET_CONTROL_PARAMS >> 2;
	cmdbuf[i++] = (sizeof(*config_struct) / 16) << 16;

	/* set configuration buffer offset */
	cmdbuf[i++] = host1x_opcode_incr(VIC_UCLASS_METHOD_OFFSET, 2);
	cmdbuf[i++] = NVB0B6_VIDEO_COMPOSITOR_SET_CONFIG_STRUCT_OFFSET >> 2;
	submit_relocs[0].cmdbuf.handle = cmdbuf_bo_handle;
	submit_relocs[0].cmdbuf.offset = i * 4;
	submit_relocs[0].target.handle = configbuf_bo_handle;
	submit_relocs[0].target.offset = 0;
	submit_relocs[0].shift = 8;
	submit_relocs[0].pad = 0;
	cmdbuf[i++] = 0xdeadbeef;

	/* set history buffer offset */
	cmdbuf[i++] = host1x_opcode_incr(VIC_UCLASS_METHOD_OFFSET, 2);
	cmdbuf[i++] = NVB0B6_VIDEO_COMPOSITOR_SET_HIST_OFFSET >> 2;
	submit_relocs[1].cmdbuf.handle = cmdbuf_bo_handle;
	submit_relocs[1].cmdbuf.offset = i * 4;
	submit_relocs[1].target.handle = histbuf_bo_handle;
	submit_relocs[1].target.offset = 0;
	submit_relocs[1].shift = 8;
	submit_relocs[1].pad = 0;
	cmdbuf[i++] = 0xdeadbeef;

	/* set output buffer */
	cmdbuf[i++] = host1x_opcode_incr(VIC_UCLASS_METHOD_OFFSET, 2);
	cmdbuf[i++] = NVB0B6_VIDEO_COMPOSITOR_SET_OUTPUT_SURFACE_LUMA_OFFSET >> 2;
	submit_relocs[2].cmdbuf.handle = cmdbuf_bo_handle;
	submit_relocs[2].cmdbuf.offset = i * 4;
	submit_relocs[2].target.handle = outbuf_bo_handle;
	submit_relocs[2].target.offset = 0;
	submit_relocs[2].shift = 8;
	submit_relocs[2].pad = 0;
	cmdbuf[i++] = 0xdeadbeef;

	/* execute */
	cmdbuf[i++] = host1x_opcode_incr(VIC_UCLASS_METHOD_OFFSET, 2);
	cmdbuf[i++] = NVB0B6_VIDEO_COMPOSITOR_EXECUTE >> 2;
	cmdbuf[i++] = 1 << 8;

	/* increment syncpoint */
	cmdbuf[i++] = host1x_opcode_nonincr(0, 1);
	cmdbuf[i++] = get_syncpt_args.id | 1 << 8;

	/* initialize submit: we make a single syncpoint increment */
	submit_syncpt_incr.id = get_syncpt_args.id;
	submit_syncpt_incr.incrs = 1;

	/* ..and we have a single command buffer */
	submit_cmdbuf.handle = cmdbuf_bo_handle;
	submit_cmdbuf.offset = 0;
	submit_cmdbuf.words = i;

	/* make the submit */
	submit_args.context = open_channel_args.context;
	submit_args.num_syncpts = 1;
	submit_args.num_cmdbufs = 1;
	submit_args.num_relocs = 3;
	submit_args.syncpts = (uintptr_t)&submit_syncpt_incr;
	submit_args.cmdbufs = (uintptr_t)&submit_cmdbuf;
	submit_args.relocs = (uintptr_t)&submit_relocs;

	err = drmIoctl(fd, DRM_IOCTL_TEGRA_SUBMIT, &submit_args);
	if (err) {
		printf("Failed to submit work (%d)\n", err);
		return err;
	}

	/* wait for completion */
	wait_args.id = get_syncpt_args.id;
	wait_args.thresh = submit_args.fence;
	wait_args.timeout = DRM_TEGRA_NO_TIMEOUT;
	err = drmIoctl(fd, DRM_IOCTL_TEGRA_SYNCPT_WAIT, &wait_args);
	if (err)
		printf("Failed to wait for completion (%d)\n", err);

	for (i = 0; i < 32; i++) {
		for (j = 0; j < 199; j++) {
			uint32_t offset = i * 256 + j;
			if (outbuf[offset] != 0x00ff00ff) {
				printf("Content mismatch at offset %u (%x != 0x00ff00ff)\n",
				       offset, outbuf[offset]);
				return -1;
			}
		}
	}

	printf("\nTest passed\n\n");

	drm_tegra_close(tegra);
	close(fd);

	return 0;
}
