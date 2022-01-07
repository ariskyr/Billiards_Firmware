#include "Arduino.h"
#include "DCMDriverL298.h"

DCMDriverL298::DCMDriverL298(const int enA, const int enB, const int IN1, const int IN2, const int IN3, const int IN4) : m_enA(enA), m_enB(enB), m_IN1(IN1), m_IN2(IN2), m_IN3(IN3), m_IN4(IN4)
{
		// setup of pins
	pinMode(m_enA, OUTPUT);
	pinMode(m_enB, OUTPUT);
	pinMode(m_IN1, OUTPUT);
	pinMode(m_IN2, OUTPUT);
	pinMode(m_IN3, OUTPUT);
	pinMode(m_IN4, OUTPUT);

	stopMotors();
}

void DCMDriverL298::setMotor(int pinPWM, int pinDir1, int pinDir2, int speed, bool dir)
{
		//set direction of motor spin and analog input for speed
	analogWrite(pinPWM, speed);
	digitalWrite(pinDir1, !dir);
	digitalWrite(pinDir2, dir);
}

void DCMDriverL298::enMotorA(int speed, bool dir)
{
	setMotor(m_enA, m_IN1, m_IN2, speed, dir);
}

void DCMDriverL298::enMotorB(int speed, bool dir)
{
	setMotor(m_enB, m_IN3, m_IN4, speed, dir);
}

void DCMDriverL298::off(int pinPWM, int pinDir1, int pinDir2)
{
    //disable motor
  digitalWrite(pinDir1, LOW);
  digitalWrite(pinDir2, LOW);
}

void DCMDriverL298::stopMotorA()
{
  off(m_enA, m_IN1, m_IN2);
}

void DCMDriverL298::stopMotorB()
{
  off(m_enB, m_IN3, m_IN4);
}

void DCMDriverL298::stopMotors()
{
  stopMotorA();
  stopMotorB();
}