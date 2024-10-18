#pragma once
#include <assert.h>
#include <memory.h>
#include <fstream>
#include "OscFormat.h"

class OscFormatInfoV1
{
public:
	explicit OscFormatInfoV1()
		: oscfmt()
		, data()
		, zoompbias(NULL)
	{
	}

	~OscFormatInfoV1()
	{
		if (zoompbias != NULL)
		{
			for (int i = 0; i < oscfmt.nOscChannels; i++)
			{
				if (zoompbias[i] != NULL)
					delete zoompbias[i];
			}
			delete zoompbias;
		}
	}

	//获取data记录文件大小字节位置
	unsigned int GetDataSizeOffset() const { return sizeof(MsoFormatV1) + oscfmt.nOscChannels * sizeof(OscZoomBiasV1) + 4; };
	//获取data记录开始的位置
	unsigned int GetDatasOffset() const { return sizeof(MsoFormatV1) + oscfmt.nOscChannels * sizeof(OscZoomBiasV1) + sizeof(OscDataV1); };
	//获取数据总字节数
	unsigned int GetDatasByteSize() const { return data.nDatasSize; };

	//读入
	bool read(std::fstream& file)
	{
		memset((char*)(&oscfmt), 0, sizeof(MsoFormatV1));
		file.read((char*)(&oscfmt), sizeof(MsoFormatV1));
		if (strncmp(oscfmt.type, "MSO", 3) != 0)
			return false;

		if (zoompbias != NULL)
		{
			for (int i = 0; i < oscfmt.nOscChannels; i++)
			{
				if (zoompbias[i] != NULL)
					delete zoompbias[i];
			}
		}
		zoompbias = new OscZoomBiasV1 * [oscfmt.nOscChannels];

		for (unsigned char i = 0; i < oscfmt.nOscChannels; ++i)
		{
			zoompbias[i] = new OscZoomBiasV1();
			file.read((char*)(zoompbias[i]), sizeof(OscZoomBiasV1));
			if (strncmp(zoompbias[i]->type, "ZOOMBIAS", 8) != 0)
				return false;
		}

		file.read((char*)(&data), sizeof(OscDataV1));
		if (strncmp(data.type, "DATA", 4) != 0)
			return false;
		return true;
	}

	MsoFormatV1 oscfmt;
	OscZoomBiasV1** zoompbias;
	OscDataV1 data;
};
