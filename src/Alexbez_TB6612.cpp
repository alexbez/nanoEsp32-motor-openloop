#include "Alexbez_TB6612.h"

Motor::Motor(int pwm, int dir1, int dir2, int standby, int offset) : _pwm(pwm), _dir1(dir1), _dir2(dir2), _standby(standby) {

    _offset = offset;
}
  
void Motor::drive(int speed)
{
    enable_motor();
    speed = speed * _offset;
    if (speed>=0) fwd(speed);
    else rev(-speed);
}

void Motor::fwd(int speed)
{
   _dir1 = 1;
   _dir2 = 0;
   _pwm = speed; // NOTE, speed is -255,255 Arduino analog.
}

void Motor::rev(int speed)
{
   _dir1 = 0;
   _dir2 = 1;
   _pwm = speed; // NOTE, speed is -255,255 Arduino analog.
}

void Motor::brake()
{
   _dir1 = 1;
   _dir2 = 1;
   _pwm = 0.0f; // NOTE, speed is -255,255 Arduino analog.
}

void Motor::standby()
{
    _standby = 0;
}

void Motor::enable_motor() {
    _standby = 1;
}

void forward(Motor motor1, Motor motor2, int speed)
{
	motor1.drive(speed);
	motor2.drive(speed);
}

void forward(Motor motor1, Motor motor2)
{
	motor1.drive(DEFAULTSPEED);
	motor2.drive(DEFAULTSPEED);
}

void back(Motor motor1, Motor motor2, int speed)
{
	int temp = abs(speed);
	motor1.drive(-temp);
	motor2.drive(-temp);
}
void back(Motor motor1, Motor motor2)
{
	motor1.drive(-DEFAULTSPEED);
	motor2.drive(-DEFAULTSPEED);
}
void left(Motor left, Motor right, int speed)
{
	int temp = abs(speed)/2;
	left.drive(-temp);
	right.drive(temp);
	
}


void right(Motor left, Motor right, int speed)
{
	int temp = abs(speed)/2;
	left.drive(temp);
	right.drive(-temp);
	
}
void brake(Motor motor1, Motor motor2)
{
	motor1.brake();
	motor2.brake();
}