#include "wheel.h"

void wheel_pins_init()
{
  pinMode(WHEEL_LF_A,OUTPUT);
  pinMode(WHEEL_LF_B,OUTPUT);
  pinMode(WHEEL_RG_A,OUTPUT);
  pinMode(WHEEL_RG_B,OUTPUT);
}

void wheel_stop()
{
  analogWrite(WHEEL_LF_A,0);
  analogWrite(WHEEL_LF_B,0);
  analogWrite(WHEEL_RG_A,0);
  analogWrite(WHEEL_RG_B,0);
}

void wheel_forword()
{
  analogWrite(WHEEL_LF_A,255);
  analogWrite(WHEEL_LF_B,0);  
  analogWrite(WHEEL_RG_A,255);
  analogWrite(WHEEL_RG_B,0);
}

void wheel_forback()
{
  analogWrite(WHEEL_LF_A,0);
  analogWrite(WHEEL_LF_B,220);  
  analogWrite(WHEEL_RG_A,0);
  analogWrite(WHEEL_RG_B,220);
}

void wheel_left()
{
  analogWrite(WHEEL_RG_A,220);
  analogWrite(WHEEL_RG_B,0);
  analogWrite(WHEEL_LF_A,0);
  analogWrite(WHEEL_LF_B,220);  
}

void wheel_right()
{
  analogWrite(WHEEL_LF_A,220);
  analogWrite(WHEEL_LF_B,0);  
  analogWrite(WHEEL_RG_A,0);
  analogWrite(WHEEL_RG_B,220);
}
