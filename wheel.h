#ifndef WHEEL_H
#define WHEEL_H

/*--------Wheel Pins------------*/
#define WHEEL_LF_A  21 
#define WHEEL_LF_B  20
#define WHEEL_RG_A  19
#define WHEEL_RG_B  18

/*--------Wheel Function------------*/
void wheel_pins_init();
void wheel_stop();
void wheel_forword();
void wheel_forback();
void wheel_left();
void wheel_right();

#endif