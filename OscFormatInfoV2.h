#pragma once
#include <assert.h>
#include <memory.h>
#include <fstream>
#include "OscFormat.h"

class OscFormatInfoV2
{
public:
	explicit OscFormatInfoV2()
		: oscfmt()
		, data()
		, zoompbias(NULL)
	{
	}

	~OscFormatInfoV2()
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

	//��ȡdata��¼�ļ���С�ֽ�λ��
	unsigned int GetDataSizeOffset() const { return sizeof(MsoFormatV2) + oscfmt.nOscChannels * sizeof(OscZoomBiasV2) + 4; };
	//��ȡdata��¼��ʼ��λ��
	unsigned int GetDatasOffset() const { return sizeof(MsoFormatV2) + oscfmt.nOscChannels * sizeof(OscZoomBiasV2) + sizeof(OscDataV2); };
	//��ȡ�������ֽ���
	uint64_t GetDatasByteSize() const { return data.nDatasSize64; };

	//����
	bool read(std::fstream& file)
	{
		memset((char*)(&oscfmt), 0, sizeof(MsoFormatV2));
		file.read((char*)(&oscfmt), sizeof(MsoFormatV2));
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
		zoompbias = new OscZoomBiasV2 * [oscfmt.nOscChannels];

		for (unsigned char i = 0; i < oscfmt.nOscChannels; ++i)
		{
			zoompbias[i] = new OscZoomBiasV2();
			file.read((char*)(zoompbias[i]), sizeof(OscZoomBiasV2));
			if (strncmp(zoompbias[i]->type, "ZOOMBIAS", 8) != 0)
				return false;
		}

		file.read((char*)(&data), sizeof(OscDataV2));
		if (strncmp(data.type, "DATA", 4) != 0)
			return false;
		return true;
	}

	MsoFormatV2 oscfmt;
	OscZoomBiasV2** zoompbias;
	OscDataV2 data;
};
