#pragma once
#include <assert.h>
#include <memory.h>
#include <fstream>

#pragma pack(push,1)

typedef enum SHIYUBX_SOURCE {
	SHIYUBX_SOURCE_ZERO = 0x00000000,
	SHIYUBX_SOURCE_CH1 = 0x00000001,
	SHIYUBX_SOURCE_CH2 = 0x00000002,
	SHIYUBX_SOURCE_REF = 0x00000004
} SHIYUBX_SOURCE;

////////////////////////////////////////////////////////V1////////////////////////////////////////////////////////
//注意：定义此类结构体要考虑字节对齐
typedef struct tMsoFormatV1
{
	char             type[6];		/* 类型 "MSO"*/
	unsigned short  Version;         /* 版本 1.0*/

	unsigned char   nOscChannels;    /* 示波器 通道数 */
	unsigned char   nOscBits;           /* 示波器 ADC bits */
	unsigned char	nAdcSymbol;			/* 示波器 正负号 0正数  1正负*/
	unsigned int    nOscSamplesPerSec;  /* 示波器 采样率 */
	unsigned int    nOscTriggerPoint;    /* 示波器  触发点 */
	unsigned char	nOscAcquireMode;	//AcquireModeNormal = 0x00, AcquireModePeakDetect = 0x01, AcquireModeAverage = 0x02

	unsigned char   nLogicChannels;    /* 逻辑分析仪 通道数 */
	unsigned int   nDecoderChannelsMask;    /* 解码器 通道数Mask */
	unsigned int   nLogicChannelsMasks;    /* 逻辑分析仪 通道数Mask */
	unsigned int    nLogicSamplesPerSec;  /* 逻辑分析仪 采样率 */
	unsigned int    nLogicTriggerPoint;    /* 逻辑分析仪  触发点 */

	unsigned short nBlockAlign;		/* 块字节数 */

	explicit tMsoFormatV1()
		: Version(1)
		, nOscChannels(0)
		, nOscBits(0)
		, nAdcSymbol(0)
		, nOscSamplesPerSec(0)
		, nOscTriggerPoint(0)
		, nOscAcquireMode(0)
		//, nOscFormat(errorSample)
		, nLogicChannels(0)
		, nDecoderChannelsMask(0)
		, nLogicChannelsMasks(0)
		, nLogicSamplesPerSec(0)
		, nLogicTriggerPoint(0)
		//, nLogicFormat(errorSample)
		, nBlockAlign(0)
	{
		memcpy(type, "MSO    ", 6);
	};

} MsoFormatV1;

//通道的放大倍数和偏置
typedef struct tOscZoomBiasV1
{
	char            type[8];         /* 类型 "ZOOMBIAS"*/
	SHIYUBX_SOURCE         nBoxing;          //时域波形
	double          nZoom;           /* 放大倍数 */
	double          nBias;           /* 偏置 */

	explicit tOscZoomBiasV1()
		: nBoxing(SHIYUBX_SOURCE_ZERO)
		, nZoom(0.0)
		, nBias(0.0)
	{
		memcpy(type, "ZOOMBIAS", 8);
	}
} OscZoomBiasV1;

//通道的放大倍数和偏置
typedef struct tOscDataV1
{
	char            type[4];         /* 类型 "DATA"*/
	unsigned int    nDatasSize;      /* 数据字节长度 */

	explicit tOscDataV1()
		: nDatasSize(0)
	{
		memcpy(type, "DATA", 4);
	};

} OscDataV1;

////////////////////////////////////////////////////////V2////////////////////////////////////////////////////////

//注意：定义此类结构体要考虑字节对齐
typedef struct tMsoFormatV2
{
	char             type[6];		/* 类型 "MSO"*/
	unsigned short  Version;         /* 版本 2.0*/  //2.0 tOscData 改成64bit

	int64_t			nWriteTime;      /* 记录时间 2.0增加 */

	unsigned char   nOscChannels;    /* 示波器 通道数 */
	unsigned char   nOscBits;           /* 示波器 ADC bits */
	unsigned char	nAdcSymbol;			/* 示波器 正负号 0正数  1正负*/
	unsigned int    nOscSamplesPerSec;  /* 示波器 采样率 */
	unsigned int    nOscTriggerPoint;    /* 示波器  触发点 */
	unsigned char	nOscAcquireMode;	//AcquireModeNormal = 0x00, AcquireModePeakDetect = 0x01, AcquireModeAverage = 0x02
	//sampleFormat    nOscFormat;         /*示波器  数据格式 */

	unsigned char   nLogicChannels;    /* 逻辑分析仪 通道数 */
	unsigned int   nDecoderChannelsMask;    /* 解码器 通道数Mask */
	unsigned int   nLogicChannelsMasks;    /* 逻辑分析仪 通道数Mask */
	unsigned int    nLogicSamplesPerSec;  /* 逻辑分析仪 采样率 */
	unsigned int    nLogicTriggerPoint;    /* 逻辑分析仪  触发点 */
	//sampleFormat    nLogicFormat;         /*示波器  数据格式 */

	unsigned short nBlockAlign;		/* 块字节数 */

	explicit tMsoFormatV2()
		: Version(2)
		, nWriteTime(-1)
		, nOscChannels(0)
		, nOscBits(0)
		, nAdcSymbol(0)
		, nOscSamplesPerSec(0)
		, nOscTriggerPoint(0)
		, nOscAcquireMode(0)
		//, nOscFormat(errorSample)
		, nLogicChannels(0)
		, nDecoderChannelsMask(0)
		, nLogicChannelsMasks(0)
		, nLogicSamplesPerSec(0)
		, nLogicTriggerPoint(0)
		//, nLogicFormat(errorSample)
		, nBlockAlign(0)
	{
		memcpy(type, "MSO    ", 6);
	};

} MsoFormatV2;

//---------------------------------------V1----------------------------------------
//通道的放大倍数和偏置
typedef struct tOscZoomBiasV2
{
	char            type[8];         /* 类型 "ZOOMBIAS"*/
	SHIYUBX_SOURCE         nBoxing;          //时域波形
	double          nZoom;           /* 放大倍数 */
	double          nBias;           /* 偏置 */

	//---------------------------V2增加-----------------------------
	char            nUnitName[16];	//单位

	char			nProbeIsCustomize;
	char            nProbeName[16];	//探头名称
	double			nProbe;  //探头倍数

	char nInvert;	//反向
	char nAcEnable; //AC/DC

	double          nAdjustZoom;           /* 校准放大倍数 */
	double          nAdjustBias;           /* 校准偏置 */

	static int GetSize(int version)
	{
		if (version == 1)
			return 8 + 4 + 8 + 8;
		else
			return sizeof(tOscZoomBiasV2);
	}

	explicit tOscZoomBiasV2()
		: nBoxing(SHIYUBX_SOURCE_ZERO)
		, nZoom(0.0)
		, nBias(0.0)
		, nProbeIsCustomize(false)
		, nProbe(1.0)
		, nInvert(0)
		, nAcEnable(0)
		, nAdjustZoom(1.0)
		, nAdjustBias(0.0)
	{
		memcpy(type, "ZOOMBIAS", 8);
		strcpy_s(nUnitName, sizeof(nUnitName), "V");
		strcpy_s(nProbeName, sizeof(nProbeName), "X1");
	}

private:
	tOscZoomBiasV2& operator=(const tOscZoomBiasV2& copy);
} OscZoomBiasV2;


//2.0 tOscData 改成64bit
typedef struct tOscDataV2
{
	char            type[4];         /* 类型 "DATA"*/
	uint64_t    nDatasSize64;      /* 数据字节长度 */

	explicit tOscDataV2()
		: nDatasSize64(0)
	{
		memcpy(type, "DATA", 4);
	};

} OscDataV2;

#pragma pack(pop)
