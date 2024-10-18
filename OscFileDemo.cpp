// OscFileDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "OscFormatInfo.h"
#include "OscFormatInfoV2.h"

void ReadV1()
{
	OscFormatInfoV1 formatinfo;
	std::fstream file(".\\v1.0.vmmso", std::fstream::in | std::fstream::binary);
	if (formatinfo.read(file))
	{
		std::cout << "Read file success\n";

		std::cout << " type " << formatinfo.oscfmt.type << "\n";
		std::cout << " Version " << formatinfo.oscfmt.Version << "\n";

		std::cout << " nOscChannels " << (unsigned int)formatinfo.oscfmt.nOscChannels << "\n";
		std::cout << " nOscBits " << (unsigned int)formatinfo.oscfmt.nOscBits << "\n";
		std::cout << " nAdcSymbol " << (unsigned int)formatinfo.oscfmt.nAdcSymbol << "\n";
		std::cout << " nOscSamplesPerSec " << formatinfo.oscfmt.nOscSamplesPerSec << "\n";
		std::cout << std::dec << " nOscTriggerPoint " << formatinfo.oscfmt.nOscTriggerPoint << "\n";
		std::cout << std::dec << " nOscAcquireMode " << (unsigned int)formatinfo.oscfmt.nOscAcquireMode << "\n";

		std::cout << " nLogicChannels " << (unsigned int)formatinfo.oscfmt.nLogicChannels << "\n";
		std::cout << " nDecoderChannelsMask " << formatinfo.oscfmt.nDecoderChannelsMask << "\n";
		std::cout << " nLogicChannelsMasks " << formatinfo.oscfmt.nLogicChannelsMasks << "\n";
		std::cout << " nLogicSamplesPerSec " << formatinfo.oscfmt.nLogicSamplesPerSec << "\n";
		std::cout << " nLogicTriggerPoint " << formatinfo.oscfmt.nLogicTriggerPoint << "\n";

		std::cout << " nBlockAlign " << formatinfo.oscfmt.nBlockAlign << "\n";

		std::cout << "\n";

		//zoompbias[0]
		std::cout << " zoompbias[0].type " << formatinfo.zoompbias[0]->type << "\n";
		std::cout << " zoompbias[0].nBoxing " << formatinfo.zoompbias[0]->nBoxing << "\n";
		std::cout << " zoompbias[0].nZoom " << formatinfo.zoompbias[0]->nZoom << "\n";
		std::cout << " zoompbias[0].nBias " << formatinfo.zoompbias[0]->nBias << "\n";
		std::cout << "\n";

		if (formatinfo.oscfmt.nOscChannels == 2)
		{
			std::cout << " zoompbias[1].type " << formatinfo.zoompbias[1]->type << "\n";
			std::cout << " zoompbias[1].nBoxing " << formatinfo.zoompbias[1]->nBoxing << "\n";
			std::cout << " zoompbias[1].nZoom " << formatinfo.zoompbias[1]->nZoom << "\n";
			std::cout << " zoompbias[1].nBias " << formatinfo.zoompbias[1]->nBias << "\n";
			std::cout << "\n";
		}

		//DATA
		std::cout << " data.type " << formatinfo.data.type << "\n";
		std::cout << " data.nDatasSize " << formatinfo.data.nDatasSize << "\n";

		//读取前10个数据
		const unsigned char blockalign = formatinfo.oscfmt.nBlockAlign;
		unsigned int length = 20;
		char* buffer = new char[length * blockalign];

		file.seekg(formatinfo.GetDatasOffset(), std::ios_base::beg);
		file.read(buffer, length * blockalign);

		for (unsigned int h = 0; h < length; h++)
		{
			if (formatinfo.oscfmt.nOscChannels == 2)
			{
				if ((formatinfo.oscfmt.nOscBits == 8) && (formatinfo.oscfmt.nAdcSymbol == 0))
				{
					std::cout << ((unsigned char*)buffer)[h * 2] * formatinfo.zoompbias[0]->nZoom + formatinfo.zoompbias[0]->nBias << " ";
					std::cout << ((unsigned char*)buffer)[h * 2 + 1] * formatinfo.zoompbias[1]->nZoom + formatinfo.zoompbias[1]->nBias << "\n";
				}
				else if ((formatinfo.oscfmt.nOscBits == 12) && (formatinfo.oscfmt.nAdcSymbol == 0))
				{
					std::cout << ((unsigned short*)buffer)[h * 2] * formatinfo.zoompbias[0]->nZoom + formatinfo.zoompbias[0]->nBias << " ";
					std::cout << ((unsigned short*)buffer)[h * 2 + 1] * formatinfo.zoompbias[1]->nZoom + formatinfo.zoompbias[1]->nBias << "\n";
				}
			}
			else
			{
				if ((formatinfo.oscfmt.nOscBits == 8) && (formatinfo.oscfmt.nAdcSymbol == 0))
				{
					std::cout << ((unsigned char*)buffer)[h] * formatinfo.zoompbias[0]->nZoom + formatinfo.zoompbias[0]->nBias << "\n";
				}
				else if ((formatinfo.oscfmt.nOscBits == 12) && (formatinfo.oscfmt.nAdcSymbol == 0))
				{
					std::cout << ((unsigned short*)buffer)[h] * formatinfo.zoompbias[0]->nZoom + formatinfo.zoompbias[0]->nBias << "\n";
				}
			}
		}

		delete[] buffer;
	}
	else
		std::cout << "Read file failed\n";
}

void ReadV2()
{
	OscFormatInfoV2 formatinfo;
	std::fstream file(".\\v2.0.vmmso", std::fstream::in | std::fstream::binary);
	if (formatinfo.read(file))
	{
		std::cout << "Read file success\n";

		std::cout << " type " << formatinfo.oscfmt.type << "\n";
		std::cout << " Version " << formatinfo.oscfmt.Version << "\n";

		std::cout << " nWriteTime " << formatinfo.oscfmt.nWriteTime << "\n";

		std::cout << " nOscChannels " << (unsigned int)formatinfo.oscfmt.nOscChannels << "\n";
		std::cout << " nOscBits " << (unsigned int)formatinfo.oscfmt.nOscBits << "\n";
		std::cout << " nAdcSymbol " << (unsigned int)formatinfo.oscfmt.nAdcSymbol << "\n";
		std::cout << " nOscSamplesPerSec " << formatinfo.oscfmt.nOscSamplesPerSec << "\n";
		std::cout << std::dec << " nOscTriggerPoint " << formatinfo.oscfmt.nOscTriggerPoint << "\n";
		std::cout << std::dec << " nOscAcquireMode " << (unsigned int)formatinfo.oscfmt.nOscAcquireMode << "\n";

		std::cout << " nLogicChannels " << (unsigned int)formatinfo.oscfmt.nLogicChannels << "\n";
		std::cout << " nDecoderChannelsMask " << formatinfo.oscfmt.nDecoderChannelsMask << "\n";
		std::cout << " nLogicChannelsMasks " << formatinfo.oscfmt.nLogicChannelsMasks << "\n";
		std::cout << " nLogicSamplesPerSec " << formatinfo.oscfmt.nLogicSamplesPerSec << "\n";
		std::cout << " nLogicTriggerPoint " << formatinfo.oscfmt.nLogicTriggerPoint << "\n";

		std::cout << " nBlockAlign " << formatinfo.oscfmt.nBlockAlign << "\n";

		std::cout << "\n";

		//zoompbias[0]
		std::cout << " zoompbias[0].type " << formatinfo.zoompbias[0]->type << "\n";
		std::cout << " zoompbias[0].nBoxing " << formatinfo.zoompbias[0]->nBoxing << "\n";
		std::cout << " zoompbias[0].nZoom " << formatinfo.zoompbias[0]->nZoom << "\n";
		std::cout << " zoompbias[0].nBias " << formatinfo.zoompbias[0]->nBias << "\n";

		std::cout << " zoompbias[0].nUnitName " << formatinfo.zoompbias[0]->nUnitName << "\n";

		std::cout << " zoompbias[0].nProbeIsCustomize " << (unsigned int)formatinfo.zoompbias[0]->nProbeIsCustomize << "\n";
		std::cout << " zoompbias[0].nProbeName " << formatinfo.zoompbias[0]->nProbeName << "\n";
		std::cout << " zoompbias[0].nProbe " << formatinfo.zoompbias[0]->nProbe << "\n";

		std::cout << " zoompbias[0].nInvert " << (unsigned int)formatinfo.zoompbias[0]->nInvert << "\n";
		std::cout << " zoompbias[0].nAcEnable " << (unsigned int)formatinfo.zoompbias[0]->nAcEnable << "\n";

		std::cout << " zoompbias[0].nAdjustZoom " << formatinfo.zoompbias[0]->nAdjustZoom << "\n";
		std::cout << " zoompbias[0].nAdjustBias " << formatinfo.zoompbias[0]->nAdjustBias << "\n";

		std::cout << "\n";

		if (formatinfo.oscfmt.nOscChannels == 2)
		{
			std::cout << " zoompbias[1].type " << formatinfo.zoompbias[1]->type << "\n";
			std::cout << " zoompbias[1].nBoxing " << formatinfo.zoompbias[1]->nBoxing << "\n";
			std::cout << " zoompbias[1].nZoom " << formatinfo.zoompbias[1]->nZoom << "\n";
			std::cout << " zoompbias[1].nBias " << formatinfo.zoompbias[1]->nBias << "\n";

			std::cout << " zoompbias[1].nUnitName " << formatinfo.zoompbias[1]->nUnitName << "\n";

			std::cout << " zoompbias[1].nProbeIsCustomize " << formatinfo.zoompbias[1]->nProbeIsCustomize << "\n";
			std::cout << " zoompbias[1].nProbeName " << formatinfo.zoompbias[1]->nProbeName << "\n";
			std::cout << " zoompbias[1].nProbe " << formatinfo.zoompbias[1]->nProbe << "\n";

			std::cout << " zoompbias[1].nInvert " << formatinfo.zoompbias[1]->nInvert << "\n";
			std::cout << " zoompbias[1].nAcEnable " << formatinfo.zoompbias[1]->nAcEnable << "\n";

			std::cout << " zoompbias[1].nAdjustZoom " << formatinfo.zoompbias[1]->nAdjustZoom << "\n";
			std::cout << " zoompbias[1].nAdjustBias " << formatinfo.zoompbias[1]->nAdjustBias << "\n";
			std::cout << "\n";
		}

		//DATA
		std::cout << " data.type " << formatinfo.data.type << "\n";
		std::cout << " data.nDatasSize64 " << formatinfo.data.nDatasSize64 << "\n";

		//读取前10个数据
		const unsigned char blockalign = formatinfo.oscfmt.nBlockAlign;
		unsigned int length = 20;
		char* buffer = new char[length * blockalign];

		file.seekg(formatinfo.GetDatasOffset(), std::ios_base::beg);
		file.read(buffer, length * blockalign);

		for (unsigned int h = 0; h < length; h++)
		{
			if (formatinfo.oscfmt.nOscChannels == 2)
			{
				if ((formatinfo.oscfmt.nOscBits == 8) && (formatinfo.oscfmt.nAdcSymbol == 0))
				{
					std::cout << ((unsigned char*)buffer)[h * 2] * formatinfo.zoompbias[0]->nZoom + formatinfo.zoompbias[0]->nBias << " ";
					std::cout << ((unsigned char*)buffer)[h * 2 + 1] * formatinfo.zoompbias[1]->nZoom + formatinfo.zoompbias[1]->nBias << "\n";
				}
				else if ((formatinfo.oscfmt.nOscBits == 12) && (formatinfo.oscfmt.nAdcSymbol == 0))
				{
					std::cout << ((unsigned short*)buffer)[h * 2] * formatinfo.zoompbias[0]->nZoom + formatinfo.zoompbias[0]->nBias << " ";
					std::cout << ((unsigned short*)buffer)[h * 2 + 1] * formatinfo.zoompbias[1]->nZoom + formatinfo.zoompbias[1]->nBias << "\n";
				}
			}
			else
			{
				if ((formatinfo.oscfmt.nOscBits == 8) && (formatinfo.oscfmt.nAdcSymbol == 0))
				{
					std::cout << ((unsigned char*)buffer)[h] * formatinfo.zoompbias[0]->nZoom + formatinfo.zoompbias[0]->nBias << "\n";
				}
				else if ((formatinfo.oscfmt.nOscBits == 12) && (formatinfo.oscfmt.nAdcSymbol == 0))
				{
					std::cout << ((unsigned short*)buffer)[h] * formatinfo.zoompbias[0]->nZoom + formatinfo.zoompbias[0]->nBias << "\n";
				}
			}
		}

		delete[] buffer;
	}
}

int main()
{
	ReadV1();
	ReadV2();
}