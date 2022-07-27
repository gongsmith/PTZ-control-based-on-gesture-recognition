#ifndef _GESTURE_
#define _GESTURE_

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <iostream>
#include <math.h>
#include <pthread.h>
#include <cassert>
#include <opencv2/opencv.hpp>

#define constrain(amt,low,high) \
	((amt)<(low)?(low):((amt)>(high)?(high):(amt)))


class PAJ7620U2 {
	public:
		PAJ7620U2() {};
		unsigned char PAJ7620U2_init();
		char I2C_readByte(int reg);
		unsigned short I2C_readU16(int reg);
		void I2C_writeByte(int reg, int val);
		unsigned short  Gesture_Data;
	private:
		int fd;
};

class LED {
	public:
		LED(char _led_u_pin,char _led_d_pin,char _led_r_pin,char _led_l_pin);
		void led_init();
		void led_u_on();
		void led_d_on();
		void led_r_on();
		void led_l_on();
		void led_u_off();
		void led_d_off();
		void led_r_off();
		void led_l_off();
	private:
		char led_u_pin;
		char led_d_pin;
		char led_r_pin;
		char led_l_pin;
};

class SERVO {
	public:
		SERVO(char _UD_PIN,char _LR_PIN);
		void pwm_init();
		void change_pwm();

		int UD_pwm = 400;
		int LR_pwm = 400;
	private:
		char UD_PIN;
		char LR_PIN;
};

#endif
