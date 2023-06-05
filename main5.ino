#include "Ultrasonic.h"
#include "wheel.h"
#include "RPi_Pico_TimerInterrupt.h"
#include <Servo.h> 

#define Left_eye  27
#define Right_eye 26
#define TIMER0_INTERVAL_MS        100
#define TIMER1_INTERVAL_MS        33

int cover_stat = 0;
int SR_Distance = 0;
int Cover_Distance = 0;
uint16_t value1 = 0;
uint16_t range1 = 0;
uint16_t value2 = 0;
uint16_t range2 = 0;

//Init RPI_PICO_Timer, can use any from 0-15 pseudo-hardware timers
RPI_PICO_Timer ITimer0(0);
RPI_PICO_Timer ITimer1(1);
 
Servo myservo;  // create servo object to control a servo 

/*------Ultrasonic Function Init-------*/
Ultrasonic ultrasonic(3,4);

Ultrasonic Cover_ultrasonic(6,7);

bool TimerHandler0(struct repeating_timer *t)
{ 
  Cover_Distance = Cover_ultrasonic.Ranging(CM);
  cover_stat++;
  if((Cover_Distance<=20) && (Cover_Distance>1))
  {
    myservo.write(130);              // tell servo to go to position in variable 100
    cover_stat = 0 ;
  }
  if(cover_stat>(3*1000/TIMER0_INTERVAL_MS))
  {
    myservo.write(10);
  }
  ITimer0.restartTimer();
  return true;
}

bool TimerHandler1(struct repeating_timer *t)
{
  SR_Distance = ultrasonic.Ranging(CM);
  value1 = analogRead (Right_eye);
  range1 = get_gp2d12 (value1);
  value2 = analogRead (Left_eye);
  range2 = get_gp2d12 (value2);
  ITimer1.restartTimer();
  return true;
}

bool follow_me_trashbin()
{
  if((range1<=100) && (range2>100))
  {
    wheel_right();
    Serial.println("<");
  }
  else if((range2<=100) && (range1>100))
  {
    wheel_left();
    Serial.println(">");
  }
  else if((range1 < 100) && (range2 < 100) || (SR_Distance < 10))
  {
    wheel_stop();
  }
  else if((SR_Distance > 20))
  {
    wheel_forword(255);
  }
  else if((range1>100) && (range2>100) && (SR_Distance<15) && (SR_Distance>10))
  {
    wheel_forback();
  }
  else
  {
    wheel_stop();
  }
  return true;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("-------hello------");

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(10);
  
  wheel_pins_init();

  pinMode (Left_eye, INPUT);
  pinMode (Right_eye, INPUT);

  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
  ITimer0.restartTimer();

  ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS * 1000, TimerHandler1);
  ITimer1.restartTimer();
}

uint16_t get_gp2d12 (uint16_t value) {
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);
}

void loop()
{    
  follow_me_trashbin();
}
