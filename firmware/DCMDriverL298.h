#pragma once
#ifndef _DCMDRIVERL298_H_
#define _DCMDRIVERL298_H_

class DCMDriverL298
{
	public:
		DCMDriverL298(const int enA, const int enB, const int IN1, const int IN2, const int IN3, const int IN4);
		void setMotor(int pinPWM, int pinDir1, int pinDir2, int speed, bool dir);
		void enMotorA(int speed, bool dir);
		void enMotorB(int speed, bool dir);
		void stopMotorA();
		void stopMotorB();
		void stopMotors();
		void off(int pinPWM, int pinDir1, int pinDir2);
	private:
		const int m_enA, m_enB, m_IN1, m_IN2, m_IN3, m_IN4;
};

#endif