#include <Arduino.h>
#include "TCS3200.h"

TCS3200::TCS3200(const int S0, const int S1, const int S2, const int S3, const int sensorOut) : m_S0(S0), m_S1(S1), m_S2(S2), m_S3(S3), m_sensorOut(sensorOut)
{
		// setup of pins
	pinMode(m_S0, OUTPUT);
	pinMode(m_S1, OUTPUT);
	pinMode(m_S2, OUTPUT);
	pinMode(m_S3, OUTPUT);

		// Setting the sensorOut as an input
	pinMode(m_sensorOut, INPUT);

	digitalWrite(m_S0, HIGH);
	digitalWrite(m_S1, LOW);
}

	//set what photodiode to use and return color
int TCS3200::Photodiode(int S2_IN, int S3_IN, int upperBound, int lowerBound, int m_sensorOut_IN)
{
		//store freq and color
	int frequency = 0;
	int color = 0;

		// set photodiodes to read
	digitalWrite(m_S2, S2_IN);
	digitalWrite(m_S3, S3_IN);

		// read output freq
	frequency = pulseIn(m_sensorOut_IN, LOW);
		// arduino map() function to convert freq
	color = map(frequency, upperBound, lowerBound, 255, 0);

	return color;
}

	//get specific photodiode
int TCS3200::getPhotodiode(char rgb)
{
	if (rgb == 'r')
	{
		return Photodiode(LOW, LOW, 100, 50, m_sensorOut);
	}
	else if (rgb == 'g')
	{
		return Photodiode(LOW, HIGH, 500, 200, m_sensorOut);
	}
	else if (rgb == 'b')
	{
		return Photodiode(HIGH, HIGH, 1000, 300, m_sensorOut);
	}
}

  // get rgb
int* TCS3200::getRGB()
{
  int* rgb = new int[3];
  rgb[0] = getPhotodiode('r');
  rgb[1] = getPhotodiode('g');
  rgb[2] = getPhotodiode('b');

  return rgb;
}
