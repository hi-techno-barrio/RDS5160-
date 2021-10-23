/*
  PCA9685 PWM Servo Driver Example
  pca9685-servomotor-demo.ino
  Demonstrates use of 16 channel I2C PWM driver board with 4 servo motors
  Uses Adafruit PWM library
Hi-Techno Barrio
*/

// Include Wire Library for I2C Communications
#include <Wire.h>
#include <Servo.h>
// Include Adafruit PWM Library
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define FREQUENCY             50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define Potentiometer Inputs
String readString;
int servoA = A0;
int servoB = A1;
int servoA9685 = 0;
int servoB9685 = 1;
int DegservoA ;
int DegservoB ;
   char ch; 
void setup() 
{
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}


void moveMotorDeg(int moveDegree, int motorOut)
{
  int pulse_wide, pulse_width;  
  // Convert to pulse width
  pulse_wide = map(moveDegree, 0, 270, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  //Control Motor
  pwm.setPWM(motorOut, 0, pulse_width);
}



void loop() {
while (Serial.available()) {
   ch = Serial.read();  //gets one byte from serial buffer
    readString += ch; //makes the string readString
    delay(2);  //slow looping to allow buffer to fill with next character
  }

  if (readString.length() >0) {
    Serial.println(readString);  //so you can see the captured string 
      int n = readString.toInt();
      moveMotorDeg(n,servoA9685);
      Serial.print("writing Angle: ");
      Serial.println(n);
      ch = '\0';
     readString = '\0';
  }

}
