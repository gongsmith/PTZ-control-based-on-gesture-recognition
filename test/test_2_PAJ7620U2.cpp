
#include "gesture_detect.h"
#include "PAJ7620U2.h"

using namespace std;


/******************* PAJ7620U2 Driver Interface *****************************/
char PAJ7620U2::I2C_readByte(int reg)
{
	return wiringPiI2CReadReg8(this->fd, reg);
}

unsigned short PAJ7620U2::I2C_readU16(int reg)
{
	return wiringPiI2CReadReg16(this->fd, reg);
}
void PAJ7620U2::I2C_writeByte(int reg, int val)
{
	wiringPiI2CWriteReg8(this->fd, reg, val);
}
unsigned char PAJ7620U2::PAJ7620U2_init()
{
	unsigned char i,State;
	if (wiringPiSetup() < 0) return 1;
	delay(5);
	this->fd=wiringPiI2CSetup(PAJ7620U2_I2C_ADDRESS);
	delay(5);
	State = I2C_readByte(0x00);												//Read State
	if (State != 0x20) return 0;											//Wake up failed
	I2C_writeByte(PAJ_BANK_SELECT, 0);										//Select Bank 0
	for (i=0;i< Init_Array;i++)
	{
		I2C_writeByte(Init_Register_Array[i][0], Init_Register_Array[i][1]);//Power up initialize
	}
	return 1;
}

/******************* SERVO Driver Interface *****************************/
SERVO::SERVO(char _UD_PIN,char _LR_PIN)
{
	UD_PIN = _UD_PIN;
	LR_PIN = _LR_PIN;
}

void SERVO::pwm_init()
{
	pinMode(this->LR_PIN, PWM_OUTPUT);    // set pwm pin as output
    pwmSetMode(PWM_MODE_MS);        // set pwm mode as nomal
    pwmSetClock(192);                // set frequency division
    pwmSetRange(2000);                // divide pwm period into 2000 
	pinMode(this->UD_PIN, PWM_OUTPUT);    // set pwm pin as output
    pwmSetMode(PWM_MODE_MS);        // set pwm mode as nomal
    pwmSetClock(192);                // set frequency division
    pwmSetRange(2000);                // divide pwm period into 2000 
    
    pwmWrite(this->LR_PIN, this->LR_pwm);
    pwmWrite(this->UD_PIN, this->UD_pwm);
}

void SERVO::change_pwm()
{
	pwmWrite(this->LR_PIN, this->LR_pwm);
	pwmWrite(this->UD_PIN, this->UD_pwm);
}

/******************* LED Driver Interface *****************************/
LED::LED(char _led_u_pin,char _led_d_pin,char _led_r_pin,char _led_l_pin)
{
	led_u_pin = _led_u_pin;
	led_d_pin = _led_d_pin;
	led_r_pin = _led_r_pin;
	led_l_pin = _led_l_pin;
}
void LED::led_init()
{
	pinMode(this->led_d_pin, OUTPUT);
	pinMode(this->led_u_pin, OUTPUT);
	pinMode(this->led_l_pin, OUTPUT);
	pinMode(this->led_r_pin, OUTPUT);
	digitalWrite(this->led_d_pin, LOW);
	digitalWrite(this->led_u_pin, LOW);
	digitalWrite(this->led_l_pin, LOW);
	digitalWrite(this->led_r_pin, LOW);
}
void LED::led_u_on()
{
	digitalWrite(this->led_u_pin, HIGH);
}
void LED::led_d_on()
{
	digitalWrite(this->led_d_pin, HIGH);
}
void LED::led_r_on()
{
	digitalWrite(this->led_r_pin, HIGH);
}
void LED::led_l_on()
{
	digitalWrite(this->led_l_pin, HIGH);
}
void LED::led_u_off()
{
	digitalWrite(this->led_u_pin, LOW);
}
void LED::led_d_off()
{
	digitalWrite(this->led_d_pin, LOW);
}
void LED::led_r_off()
{
	digitalWrite(this->led_r_pin, LOW);
}
void LED::led_l_off()
{
	digitalWrite(this->led_l_pin, LOW);
}
/******************* Main func *****************************/
PAJ7620U2 gesture_mod;
SERVO servo(23,1); //set pin as GPIO23 & GPIO1
LED led(3,2,4,5);  //set pin as GPIO3 & GPIO2 & GPIO4 & GPIO5
void *led_control(void *);
void *servo_control(void *);

int main(int argc, char** argv)
{
	unsigned char i;
	system("./camera.sh &");
	
	cout<<"\nGesture Sensor Test Program ...\n";
	if(!gesture_mod.PAJ7620U2_init())
	{	cout<<"\nGesture Sensor Error\n";
		return 0;
	}
	cout<<"\nGesture Sensor OK\n";
		
	gesture_mod.I2C_writeByte(PAJ_BANK_SELECT, 0);//Select Bank 0
	for (i = 0; i < Gesture_Array_SIZE; i++)
	{
		gesture_mod.I2C_writeByte(Init_Gesture_Array[i][0], Init_Gesture_Array[i][1]);//Gesture register initializes
	}
	
	servo.pwm_init();
	led.led_init();
	cout<<"pwm/LED init\n";
	
	//Create a function thread and specify the function to be executed by the function thread
	pthread_t led_ctl_id;
	int led_ctl_res = pthread_create(&led_ctl_id,NULL,led_control,NULL);
	assert(led_ctl_res == 0);
	pthread_t servo_ctl_id;
	int servo_ctl_res = pthread_create(&servo_ctl_id,NULL,servo_control,NULL);
	assert(servo_ctl_res == 0);
	
	while (1)
	{
		gesture_mod.Gesture_Data = gesture_mod.I2C_readU16(PAJ_INT_FLAG1);
		if (gesture_mod.Gesture_Data)
		{
			switch (gesture_mod.Gesture_Data)
			{
				case PAJ_UP:	cout<<"Up & pwm is:"<<servo.UD_pwm<<endl;break;
				case PAJ_DOWN:	cout<<"down & pwm is:"<<servo.UD_pwm<<endl;break;
				case PAJ_LEFT:	cout<<"left & pwm is:"<<servo.LR_pwm<<endl;break;
				case PAJ_RIGHT:	cout<<"right & pwm is:"<<servo.LR_pwm<<endl;break;
				default: break;
			}
			delay(50);
		}
	}
	return 0;
}
//Define thread functions
void* led_control(void *arg)
{
	while(1)
	{
		if (gesture_mod.Gesture_Data)
		{
			switch (gesture_mod.Gesture_Data)
			{
				case PAJ_UP:	led.led_u_on();break;
				case PAJ_DOWN:	led.led_d_on();break;
				case PAJ_LEFT:	led.led_l_on();break;
				case PAJ_RIGHT:	led.led_r_on();break;
				default: break;
			}
			delay(1000);
			led.led_u_off();
			led.led_d_off();
			led.led_l_off();
			led.led_r_off();
		}
	}
}

void* servo_control(void *arg)
{
	while(1)
	{
		if (gesture_mod.Gesture_Data)
		{
			switch (gesture_mod.Gesture_Data)
			{
				case PAJ_UP:	servo.UD_pwm+=40;break;
				case PAJ_DOWN:	servo.UD_pwm-=40;break;
				case PAJ_LEFT:	servo.LR_pwm+=40;break;
				case PAJ_RIGHT:	servo.LR_pwm-=40;break;
				default: break;
			}
			servo.UD_pwm = constrain(servo.UD_pwm,160,680);
			servo.LR_pwm = constrain(servo.LR_pwm,120,720);
			servo.change_pwm();
			delay(100);
		}
	}
}
