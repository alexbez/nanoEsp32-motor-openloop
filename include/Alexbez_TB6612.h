#ifndef ALEXBEZ_TB6612_H_
#define ALEXBEZ_TB6612_H_

#include    <Arduino.h>
#define     DEFAULTSPEED    255

class Motor
{
  public:
    // Constructor. Mainly sets up pins.
    Motor(int pwm, int dir1, int dir2, int standby, int offset = 1);      

    void drive(int speed);    
    void brake(); 
	void standby();	
    void enable_motor();
	
  private:
    //variables for the 2 inputs, PWM input, Offset value, and the Standby pin
	int _pwm;
    int _dir1, _dir2, _standby;
	int _offset;

	//private functions that spin the motor CC and CCW
	void fwd(int speed);
	void rev(int speed);


};

void forward(Motor motor1, Motor motor2, int speed);
void forward(Motor motor1, int speed);

void back(Motor motor1, Motor motor2, int speed);
void back(Motor motor1, int speed);

void left(Motor left, Motor right, int speed);
void right(Motor left, Motor right, int speed);

//This function takes 2 motors and and brakes them
void brake(Motor motor1, Motor motor2);

#endif // ALEXBEZ_TB6612_H_