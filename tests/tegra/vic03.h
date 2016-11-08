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

#ifndef VIC_H
#define VIC_H

#define VIC_UCLASS_INCR_SYNCPT					0x00
#define VIC_UCLASS_METHOD_OFFSET				0x10
#define VIC_UCLASS_METHOD_DATA					0x11

#define NVA0B6_VIDEO_COMPOSITOR_EXECUTE				0x00000300
#define NVA0B6_VIDEO_COMPOSITOR_SET_CONTROL_PARAMS		0x00000700
#define NVA0B6_VIDEO_COMPOSITOR_SET_CONFIG_STRUCT_OFFSET	0x00000720
#define NVA0B6_VIDEO_COMPOSITOR_SET_HIST_OFFSET			0x00000728
#define NVA0B6_VIDEO_COMPOSITOR_SET_OUTPUT_SURFACE_LUMA_OFFSET	0x00000730

typedef struct _SurfaceCache0Struct {
	uint64_t DeNoise0            : 1;
	uint64_t CadenceDetect0      : 1;
	uint64_t MotionMap0          : 1;
	uint64_t MedianFilter0       : 1;
	uint64_t DeNoise1            : 1;
	uint64_t CadenceDetect1      : 1;
	uint64_t MotionMap1          : 1;
	uint64_t MedianFilter1       : 1;
	uint64_t DeNoise2            : 1;
	uint64_t CadenceDetect2      : 1;
	uint64_t MotionMap2          : 1;
	uint64_t MedianFilter2       : 1;
	uint64_t DeNoise3            : 1;
	uint64_t CadenceDetect3      : 1;
	uint64_t MotionMap3          : 1;
	uint64_t MedianFilter3       : 1;
	uint64_t DeNoise4            : 1;
	uint64_t CadenceDetect4      : 1;
	uint64_t MotionMap4          : 1;
	uint64_t MedianFilter4       : 1;
	uint64_t IsEven0             : 1;
	uint64_t IsEven1             : 1;
	uint64_t IsEven2             : 1;
	uint64_t IsEven3             : 1;
	uint64_t IsEven4             : 1;
	uint64_t MMapCombine0        : 1;
	uint64_t MMapCombine1        : 1;
	uint64_t MMapCombine2        : 1;
	uint64_t MMapCombine3        : 1;
	uint64_t MMapCombine4        : 1;
	uint64_t reserved0           : 2;
	uint64_t PixelFormat0        : 7;
	uint64_t reserved1           : 1;
	uint64_t PixelFormat1        : 7;
	uint64_t reserved2           : 1;
	uint64_t PixelFormat2        : 7;
	uint64_t reserved3           : 1;
	uint64_t PixelFormat3        : 7;
	uint64_t reserved4           : 1;
	uint64_t PixelFormat4        : 7;
	uint64_t reserved5           : 1;
	uint64_t reserved6           : 24;
	uint64_t PPMotion0           : 1;
	uint64_t PPMotion1           : 1;
	uint64_t PPMotion2           : 1;
	uint64_t PPMotion3           : 1;
	uint64_t PPMotion4           : 1;
	uint64_t reserved7           : 3;
	uint64_t ChromaEven0         : 1;
	uint64_t ChromaEven1         : 1;
	uint64_t ChromaEven2         : 1;
	uint64_t ChromaEven3         : 1;
	uint64_t ChromaEven4         : 1;
	uint64_t reserved8           : 3;
	uint64_t AdvancedDenoise0    : 1;
	uint64_t AdvancedDenoise1    : 1;
	uint64_t AdvancedDenoise2    : 1;
	uint64_t AdvancedDenoise3    : 1;
	uint64_t AdvancedDenoise4    : 1;
	uint64_t reserved9           : 3;
	uint64_t reserved10          : 8;
} SurfaceCache0Struct;


typedef struct _SurfaceList0Struct {
	uint64_t ClearRectMask0      : 8;
	uint64_t ClearRectMask1      : 8;
	uint64_t ClearRectMask2      : 8;
	uint64_t ClearRectMask3      : 8;
	uint64_t ClearRectMask4      : 8;
	uint64_t reserved0           : 22;
	uint64_t OutputFlipX         : 1;
	uint64_t OutputFlipY         : 1;
	uint64_t TargetRectLeft      : 14;
	uint64_t reserved1           : 2;
	uint64_t TargetRectRight     : 14;
	uint64_t reserved2           : 2;
	uint64_t TargetRectTop       : 14;
	uint64_t reserved3           : 2;
	uint64_t TargetRectBottom    : 14;
	uint64_t reserved4           : 2;
} SurfaceList0Struct;


typedef struct _SurfaceListClearRectStruct {
	uint64_t ClearRect0Left      : 14;
	uint64_t reserved0           : 2;
	uint64_t ClearRect0Right     : 14;
	uint64_t reserved1           : 2;
	uint64_t ClearRect0Top       : 14;
	uint64_t reserved2           : 2;
	uint64_t ClearRect0Bottom    : 14;
	uint64_t reserved3           : 2;
	uint64_t ClearRect1Left      : 14;
	uint64_t reserved4           : 2;
	uint64_t ClearRect1Right     : 14;
	uint64_t reserved5           : 2;
	uint64_t ClearRect1Top       : 14;
	uint64_t reserved6           : 2;
	uint64_t ClearRect1Bottom    : 14;
	uint64_t reserved7           : 2;
} SurfaceListClearRectStruct;


typedef struct _SurfaceListSurfaceStruct {
	uint64_t Enable              : 1;
	uint64_t FrameFormat         : 4;
	uint64_t PixelFormat         : 7;
	uint64_t reserved0           : 2;
	uint64_t ChromaLocHoriz      : 2;
	uint64_t ChromaLocVert       : 2;
	uint64_t Panoramic           : 12;
	uint64_t reserved1           : 4;
	uint64_t SurfaceWidth        : 14;
	uint64_t reserved2           : 1;
	uint64_t SurfaceHeight       : 14;
	uint64_t reserved3           : 1;
	uint64_t LumaWidth           : 14;
	uint64_t reserved4           : 1;
	uint64_t LumaHeight          : 14;
	uint64_t reserved5           : 1;
	uint64_t ChromaWidth         : 14;
	uint64_t reserved6           : 1;
	uint64_t ChromaHeight        : 14;
	uint64_t reserved7           : 1;
	uint64_t CacheWidth          : 3;
	uint64_t reserved8           : 1;
	uint64_t FilterLengthY       : 2;
	uint64_t FilterLengthX       : 2;
	uint64_t DetailFltClamp      : 6;
	uint64_t reserved9           : 2;
	uint64_t LightLevel          : 4;
	uint64_t reserved10          : 4;
	uint64_t reserved11          : 8;
	uint64_t reserved12          : 32;
	uint64_t BlkKind             : 4;
	uint64_t DestRectLeft        : 14;
	uint64_t reserved13          : 1;
	uint64_t DestRectRight       : 14;
	uint64_t reserved14          : 1;
	uint64_t DestRectTop         : 14;
	uint64_t reserved15          : 1;
	uint64_t DestRectBottom      : 14;
	uint64_t reserved16          : 1;
	uint64_t BlkHeight           : 4;
	uint64_t SourceRectLeft      : 30;
	uint64_t reserved17          : 2;
	uint64_t SourceRectRight     : 30;
	uint64_t reserved18          : 2;
	uint64_t SourceRectTop       : 30;
	uint64_t reserved19          : 2;
	uint64_t SourceRectBottom    : 30;
	uint64_t reserved20          : 2;
} SurfaceListSurfaceStruct;


typedef struct _ColorConversionLumaAlphaStruct {
	uint64_t l0                  : 20;
	uint64_t l1                  : 20;
	uint64_t l2                  : 20;
	uint64_t r_shift             : 4;
	uint64_t l3                  : 20;
	uint64_t PlanarAlpha         : 10;
	uint64_t ConstantAlpha       : 1;
	uint64_t ClipEnabled         : 1;
	uint64_t LumaKeyLower        : 10;
	uint64_t reserved6           : 3;
	uint64_t StereoInterleave    : 3;
	uint64_t LumaKeyUpper        : 10;
	uint64_t reserved7           : 2;
	uint64_t reserved8           : 1;
	uint64_t LumaKeyEnabled      : 1;
	uint64_t reserved9           : 2;
} ColorConversionLumaAlphaStruct;


typedef struct _ColorConversionMatrixStruct {
	uint64_t c00                 : 20;
	uint64_t c10                 : 20;
	uint64_t c20                 : 20;
	uint64_t r_shift             : 4;
	uint64_t c01                 : 20;
	uint64_t c11                 : 20;
	uint64_t c21                 : 20;
	uint64_t reserved0           : 4;
	uint64_t c02                 : 20;
	uint64_t c12                 : 20;
	uint64_t c22                 : 20;
	uint64_t reserved1           : 4;
	uint64_t c03                 : 20;
	uint64_t c13                 : 20;
	uint64_t c23                 : 20;
	uint64_t reserved2           : 4;
} ColorConversionMatrixStruct;


typedef struct _ColorConversionClampStruct {
	uint64_t low                 : 10;
	uint64_t reserved0           : 6;
	uint64_t high                : 10;
	uint64_t reserved1           : 6;
	uint64_t reserved2           : 32;
	uint64_t reserved3           : 32;
	uint64_t reserved4           : 32;
} ColorConversionClampStruct;


typedef struct _Blending0Struct {
	uint64_t PixelFormat         : 7;
	uint64_t reserved0           : 1;
	uint64_t AlphaFillMode       : 3;
	uint64_t AlphaFillSlot       : 3;
	uint64_t BackgroundAlpha     : 10;
	uint64_t BackgroundR         : 10;
	uint64_t BackgroundG         : 10;
	uint64_t BackgroundB         : 10;
	uint64_t ChromaLocHoriz      : 2;
	uint64_t ChromaLocVert       : 2;
	uint64_t reserved1           : 6;
	uint64_t LumaWidth           : 14;
	uint64_t reserved2           : 2;
	uint64_t LumaHeight          : 14;
	uint64_t reserved3           : 2;
	uint64_t ChromaWidth         : 14;
	uint64_t reserved4           : 2;
	uint64_t ChromaHeight        : 14;
	uint64_t reserved5           : 2;
	uint64_t TargetRectLeft      : 14;
	uint64_t reserved6           : 2;
	uint64_t TargetRectRight     : 14;
	uint64_t reserved7           : 2;
	uint64_t TargetRectTop       : 14;
	uint64_t reserved8           : 2;
	uint64_t TargetRectBottom    : 14;
	uint64_t reserved9           : 2;
	uint64_t SurfaceWidth        : 14;
	uint64_t reserved10          : 2;
	uint64_t SurfaceHeight       : 14;
	uint64_t reserved11          : 2;
	uint64_t BlkKind             : 4;
	uint64_t BlkHeight           : 4;
	uint64_t OutputFlipX         : 1;
	uint64_t OutputFlipY         : 1;
	uint64_t OutputTranspose     : 1;
	uint64_t reserved12          : 21;
} Blending0Struct;


typedef struct _BlendingSurfaceStruct {
	uint64_t AlphaK1             : 10;
	uint64_t reserved0           : 6;
	uint64_t AlphaK2             : 10;
	uint64_t reserved1           : 6;
	uint64_t SrcFactCMatchSelect : 3;
	uint64_t reserved2           : 1;
	uint64_t DstFactCMatchSelect : 3;
	uint64_t reserved3           : 1;
	uint64_t SrcFactAMatchSelect : 3;
	uint64_t reserved4           : 1;
	uint64_t DstFactAMatchSelect : 3;
	uint64_t reserved5           : 1;
	uint64_t reserved6           : 4;
	uint64_t reserved7           : 4;
	uint64_t reserved8           : 4;
	uint64_t reserved9           : 4;
	uint64_t reserved10          : 2;
	uint64_t OverrideR           : 10;
	uint64_t OverrideG           : 10;
	uint64_t OverrideB           : 10;
	uint64_t OverrideA           : 10;
	uint64_t reserved11          : 2;
	uint64_t UseOverrideR        : 1;
	uint64_t UseOverrideG        : 1;
	uint64_t UseOverrideB        : 1;
	uint64_t UseOverrideA        : 1;
	uint64_t MaskR               : 1;
	uint64_t MaskG               : 1;
	uint64_t MaskB               : 1;
	uint64_t MaskA               : 1;
	uint64_t reserved12          : 12;
} BlendingSurfaceStruct;


typedef struct _FetchControl0Struct {
	uint64_t TargetRectLeft      : 14;
	uint64_t reserved0           : 2;
	uint64_t TargetRectRight     : 14;
	uint64_t reserved1           : 2;
	uint64_t TargetRectTop       : 14;
	uint64_t reserved2           : 2;
	uint64_t TargetRectBottom    : 14;
	uint64_t reserved3           : 2;
	uint64_t Enable0             : 8;
	uint64_t Enable1             : 8;
	uint64_t Enable2             : 8;
	uint64_t Enable3             : 8;
	uint64_t Enable4             : 8;
	uint64_t DownsampleHoriz     : 11;
	uint64_t reserved4           : 1;
	uint64_t DownsampleVert      : 11;
	uint64_t reserved5           : 1;
	uint64_t FilterNoise0        : 10;
	uint64_t FilterDetail0       : 10;
	uint64_t FilterNoise1        : 10;
	uint64_t reserved6           : 2;
	uint64_t FilterDetail1       : 10;
	uint64_t FilterNoise2        : 10;
	uint64_t FilterDetail2       : 10;
	uint64_t reserved7           : 2;
	uint64_t FilterNoise3        : 10;
	uint64_t FilterDetail3       : 10;
	uint64_t FilterNoise4        : 10;
	uint64_t reserved8           : 2;
	uint64_t FilterDetail4       : 10;
	uint64_t reserved9           : 22;
	uint64_t ChromaNoise0        : 10;
	uint64_t ChromaDetail0       : 10;
	uint64_t ChromaNoise1        : 10;
	uint64_t reserved10          : 2;
	uint64_t ChromaDetail1       : 10;
	uint64_t ChromaNoise2        : 10;
	uint64_t ChromaDetail2       : 10;
	uint64_t reserved11          : 2;
	uint64_t ChromaNoise3        : 10;
	uint64_t ChromaDetail3       : 10;
	uint64_t ChromaNoise4        : 10;
	uint64_t reserved12          : 2;
	uint64_t ChromaDetail4       : 10;
	uint64_t reserved13          : 22;
	uint64_t Mode0               : 4;
	uint64_t AccumWeight0        : 3;
	uint64_t Iir0                : 11;
	uint64_t reserved14          : 2;
	uint64_t Mode1               : 4;
	uint64_t AccumWeight1        : 3;
	uint64_t Iir1                : 11;
	uint64_t reserved15          : 2;
	uint64_t Mode2               : 4;
	uint64_t AccumWeight2        : 3;
	uint64_t Iir2                : 11;
	uint64_t reserved16          : 6;
	uint64_t Mode3               : 4;
	uint64_t AccumWeight3        : 3;
	uint64_t Iir3                : 11;
	uint64_t reserved17          : 2;
	uint64_t Mode4               : 4;
	uint64_t AccumWeight4        : 3;
	uint64_t Iir4                : 11;
	uint64_t reserved18          : 8;
	uint64_t OutputFlipX         : 1;
	uint64_t OutputFlipY         : 1;
	uint64_t reserved19          : 10;
	uint64_t reserved20          : 6;
} FetchControl0Struct;


typedef struct _FetchControlCoeffStruct {
	uint64_t f00                 : 10;
	uint64_t f10                 : 10;
	uint64_t f20                 : 10;
	uint64_t reserved0           : 2;
	uint64_t f01                 : 10;
	uint64_t f11                 : 10;
	uint64_t f21                 : 10;
	uint64_t reserved1           : 2;
	uint64_t f02                 : 10;
	uint64_t f12                 : 10;
	uint64_t f22                 : 10;
	uint64_t reserved2           : 2;
	uint64_t f03                 : 10;
	uint64_t f13                 : 10;
	uint64_t f23                 : 10;
	uint64_t reserved3           : 2;
} FetchControlCoeffStruct;

typedef struct _ConfigStruct {
	SurfaceCache0Struct                  surfaceCache0Struct;
	SurfaceList0Struct                   surfaceList0Struct;
	SurfaceListClearRectStruct           surfaceListClearRectStruct[4];
	SurfaceListSurfaceStruct             surfaceListSurfaceStruct[5];
	ColorConversionLumaAlphaStruct       colorConversionLumaAlphaStruct[5];
	ColorConversionMatrixStruct          colorConversionMatrixStruct[5];
	ColorConversionClampStruct           colorConversionClampStruct[5];
	Blending0Struct                      blending0Struct;
	BlendingSurfaceStruct                blendingSurfaceStruct[5];
	FetchControl0Struct                  fetchControl0Struct;
	FetchControlCoeffStruct              fetchControlCoeffStruct[520];
} ConfigStruct;

#endif
