/*
 * pwm.c
 *
 * Created: 01/04/2018 19:36:50
 *  Author: BADROUS
 */ 
#include "pwm.h"
//-----------------------------------------------------
void pwm_init()
{
	set_bit(TCCR2,WGM20);
	clear_bit(TCCR2,WGM21);//phase corect pwm
	clear_bit(TCCR2,COM20);
	set_bit(TCCR2,COM21); //set on compare match when upcount
	TCCR2 |=(1<<CS20) | (1<<CS21)| (1<<CS22);  //1024 prescaller
	OCR2=0;
	TCNT2=0;
}

void pwm_duty(u8 duty)
{
	OCR2=(duty*255/100);
}
