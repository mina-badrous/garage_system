/*
 * pwm.h
 *
 * Created: 01/04/2018 19:36:36
 *  Author: BADROUS
 */ 


#ifndef PWM_H_
#define PWM_H_
//------------------------------------------------------
#include "master_config.h"
//---------------------------------------------------
#define PRESCALER 1
#define PWM_FREQUENCY (F_CPU/PRESCALER/510)
//--------------------------------------------------------
void pwm_init();
void pwm_duty(u8 duty);
//---------------------------------------------------------
#endif /* PWM_H_ */