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
//ע�⣺�������ṹ��Ҫ�����ֽڶ���
typedef struct tMsoFormatV1
{
	char             type[6];		/* ���� "MSO"*/
	unsigned short  Version;         /* �汾 1.0*/

	unsigned char   nOscChannels;    /* ʾ���� ͨ���� */
	unsigned char   nOscBits;           /* ʾ���� ADC bits */
	unsigned char	nAdcSymbol;			/* ʾ���� ������ 0����  1����*/
	unsigned int    nOscSamplesPerSec;  /* ʾ���� ������ */
	unsigned int    nOscTriggerPoint;    /* ʾ����  ������ */
	unsigned char	nOscAcquireMode;	//AcquireModeNormal = 0x00, AcquireModePeakDetect = 0x01, AcquireModeAverage = 0x02

	unsigned char   nLogicChannels;    /* �߼������� ͨ���� */
	unsigned int   nDecoderChannelsMask;    /* ������ ͨ����Mask */
	unsigned int   nLogicChannelsMasks;    /* �߼������� ͨ����Mask */
	unsigned int    nLogicSamplesPerSec;  /* �߼������� ������ */
	unsigned int    nLogicTriggerPoint;    /* �߼�������  ������ */

	unsigned short nBlockAlign;		/* ���ֽ��� */

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

//ͨ���ķŴ�����ƫ��
typedef struct tOscZoomBiasV1
{
	char            type[8];         /* ���� "ZOOMBIAS"*/
	SHIYUBX_SOURCE         nBoxing;          //ʱ����
	double          nZoom;           /* �Ŵ��� */
	double          nBias;           /* ƫ�� */

	explicit tOscZoomBiasV1()
		: nBoxing(SHIYUBX_SOURCE_ZERO)
		, nZoom(0.0)
		, nBias(0.0)
	{
		memcpy(type, "ZOOMBIAS", 8);
	}
} OscZoomBiasV1;

//ͨ���ķŴ�����ƫ��
typedef struct tOscDataV1
{
	char            type[4];         /* ���� "DATA"*/
	unsigned int    nDatasSize;      /* �����ֽڳ��� */

	explicit tOscDataV1()
		: nDatasSize(0)
	{
		memcpy(type, "DATA", 4);
	};

} OscDataV1;

////////////////////////////////////////////////////////V2////////////////////////////////////////////////////////

//ע�⣺�������ṹ��Ҫ�����ֽڶ���
typedef struct tMsoFormatV2
{
	char             type[6];		/* ���� "MSO"*/
	unsigned short  Version;         /* �汾 2.0*/  //2.0 tOscData �ĳ�64bit

	int64_t			nWriteTime;      /* ��¼ʱ�� 2.0���� */

	unsigned char   nOscChannels;    /* ʾ���� ͨ���� */
	unsigned char   nOscBits;           /* ʾ���� ADC bits */
	unsigned char	nAdcSymbol;			/* ʾ���� ������ 0����  1����*/
	unsigned int    nOscSamplesPerSec;  /* ʾ���� ������ */
	unsigned int    nOscTriggerPoint;    /* ʾ����  ������ */
	unsigned char	nOscAcquireMode;	//AcquireModeNormal = 0x00, AcquireModePeakDetect = 0x01, AcquireModeAverage = 0x02
	//sampleFormat    nOscFormat;         /*ʾ����  ���ݸ�ʽ */

	unsigned char   nLogicChannels;    /* �߼������� ͨ���� */
	unsigned int   nDecoderChannelsMask;    /* ������ ͨ����Mask */
	unsigned int   nLogicChannelsMasks;    /* �߼������� ͨ����Mask */
	unsigned int    nLogicSamplesPerSec;  /* �߼������� ������ */
	unsigned int    nLogicTriggerPoint;    /* �߼�������  ������ */
	//sampleFormat    nLogicFormat;         /*ʾ����  ���ݸ�ʽ */

	unsigned short nBlockAlign;		/* ���ֽ��� */

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
//ͨ���ķŴ�����ƫ��
typedef struct tOscZoomBiasV2
{
	char            type[8];         /* ���� "ZOOMBIAS"*/
	SHIYUBX_SOURCE         nBoxing;          //ʱ����
	double          nZoom;           /* �Ŵ��� */
	double          nBias;           /* ƫ�� */

	//---------------------------V2����-----------------------------
	char            nUnitName[16];	//��λ

	char			nProbeIsCustomize;
	char            nProbeName[16];	//̽ͷ����
	double			nProbe;  //̽ͷ����

	char nInvert;	//����
	char nAcEnable; //AC/DC

	double          nAdjustZoom;           /* У׼�Ŵ��� */
	double          nAdjustBias;           /* У׼ƫ�� */

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


//2.0 tOscData �ĳ�64bit
typedef struct tOscDataV2
{
	char            type[4];         /* ���� "DATA"*/
	uint64_t    nDatasSize64;      /* �����ֽڳ��� */

	explicit tOscDataV2()
		: nDatasSize64(0)
	{
		memcpy(type, "DATA", 4);
	};

} OscDataV2;

#pragma pack(pop)
