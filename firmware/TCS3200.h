#pragma once
#ifndef _TCS3200_H_
#define _TCS3200_H_

class TCS3200
{
	public:
		TCS3200(const int S0, const int S1, const int S2, const int S3, const int sensorOut);
		int Photodiode(int S2_IN, int S3_IN, int upperBound, int lowerBound, int m_sensorOut_IN);
		int getPhotodiode(char rgb);
    int* getRGB();
  private:
    const int m_S0, m_S1, m_S2, m_S3, m_sensorOut;
  
};

#endif

