/*
 *  Board:            Arduino Nano ESP32
 *  DC Motor Driver:  TB6612
 *  
 *  Scetch to control two DC motors
 * 
 *  Wiring:
 *  =======
 *  Nano ESP32    TB6612
 *  ---------------------
 *  D3            AI1
 *  D4            AI2
 *  D5            PWMA
 *  D6            PWMB
 *  D7            BI1
 *  D8            BI2
 *  D9            STBY
 *  D10           Motor1 Encoder A
 *  D11           Motor2 Encoder A
 *                VM --> Motor power +10V
 *  
 */
#include <Arduino.h>
#include "Sparkfun_TB6612.h"

#define SERIAL_BAUD     115200

#define SPEED_INTERVAL  100   // msec
#define PID_INTERVAL    100   // msec

#define AIN1    D3
#define AIN2    D4
#define PWMA    D5
#define PWMB    D6
#define BIN1    D7
#define BIN2    D8
#define STBY    D9

#define M1ENC   D10
#define M2ENC   D11

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

hw_timer_t *My_timer = NULL;


volatile int  speed1, speed2;
volatile int count1 = 0;
volatile int count2 = 0;

void IRAM_ATTR onTimer() {
  speed1 = count1;
  speed2 = count2;
  count1 = count2 = 0;
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void onEncoder1() {
  count1++;
}

void onEncoder2() {
  count2++;
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println("Nano ESP32 TB6612 Motors");

  pinMode(M1ENC, INPUT);
  pinMode(M2ENC, INPUT);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  Serial.println("I/O pins configured OK");

  attachInterrupt(digitalPinToInterrupt(M1ENC), onEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(M2ENC), onEncoder2, RISING);
  Serial.println("Encoders ISRs are set OK");

  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, SPEED_INTERVAL, true);
  timerAlarmEnable(My_timer); 
  Serial.println("Timer ISR is set OK. LED shall start blinking now");

  Serial.println("Setup completed OK");
}

void loop() {
  Serial.println("Motor1 --> FWD 255, Motor2 --> BCK 255");
  motor1.drive(255,2000);
  motor2.drive(-255,2000);
  Serial.println("Motor1, Motor2 - STOP");
  motor1.brake();
  motor2.brake();
  delay(2000);

  Serial.println("Motor1 --> BCK 120, Motor2 --> FWD 120");   
  motor1.drive(-120,2000);
  motor2.drive(120,2000);
  Serial.println("Motor1, Motor2 - STOP");
  motor1.brake();
  motor2.brake();
  delay(2000);
   
  Serial.println("Motor1, Motor2 --> FWD 180");
  forward(motor1, motor2, 180);
  delay(2000);
  Serial.println("Motor1, Motor2 - STOP");
  motor1.brake();
  motor2.brake();
  delay(2000);
   
  Serial.println("Motor1, Motor2 -->BCK 180");
  back(motor1, motor2, -180);
  delay(2000);
  Serial.println("Motor1, Motor2 - STOP");
  motor1.brake();
  motor2.brake();
  delay(2000);   

  Serial.println("----- Loop completed -----");
  delay(2000);
}
