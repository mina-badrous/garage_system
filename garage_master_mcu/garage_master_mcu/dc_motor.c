/*
 * dc_motor.c
 *
 * Created: 01/04/2018 20:13:22
 *  Author: BADROUS
 */
//------------------------------------------------------------ 
#include "dc_motor.h"
//--------------------------------------------------------
GARAGE_STATE e_garage_state=GARAGE_IS_CLOSED;
//------------------------------------------------------------
static void dc_motor_rotate(u8 power,u8 direction);
static void dc_motor_rotate_seconds(u8 power,u8 direction,u8 seconds);
static void dc_motor_stop();
//---------------------------------------------------------------------
void dc_motor_init()
{
	MOTOR_DDR |= (1<<MOTOR_IN1) | (1<<MOTOR_IN2) | (1<<MOTOR_PWM);
	MOTOR_PORT &= ~((1<<MOTOR_IN1) | (1<<MOTOR_IN2));
	pwm_init();
}
//-----------------------------------------------------------
static void dc_motor_rotate(u8 power,u8 direction)
{
	if(direction==DC_MOTOR_ROTATE_CLOCKWISE)
	{
		set_bit(MOTOR_PORT,MOTOR_IN1);
		clear_bit(MOTOR_PORT,MOTOR_IN2);
	}
	else
	{
		clear_bit(MOTOR_PORT,MOTOR_IN1);
		set_bit(MOTOR_PORT,MOTOR_IN2);
	}
	pwm_duty(power);
	
}
//-----------------------------------------------------------
static void dc_motor_stop()
{
	clear_bit(MOTOR_PORT,MOTOR_IN1);
	clear_bit(MOTOR_PORT,MOTOR_IN2);
	pwm_duty(0);
}
//----------------------------------------------------------
static void dc_motor_rotate_seconds( u8 power,u8 direction,u8 seconds )
{
	u8 index;
	for(index=seconds;index>0;index--)
	{
		dc_motor_rotate(power,direction);
		_delay_ms(1000);
	}
	dc_motor_stop();
}
//---------------------------------------------------------------
void open_garage_close()
{
	dc_motor_rotate_seconds(100,DC_MOTOR_ROTATE_CLOCKWISE,GARAGE_TIME/2);
	_delay_ms(1000);
	dc_motor_rotate_seconds(100,DC_MOTOR_ROTATE_ANTICLOCKWISE,GARAGE_TIME/2);
}
//------------------------------------------------------------
void open_garage()
{
	e_garage_state=GARAGE_IS_OPENED;
	dc_motor_rotate_seconds(100,DC_MOTOR_ROTATE_CLOCKWISE,GARAGE_TIME);
}
//--------------------------------------------------------------
void close_garage()
{
	e_garage_state=GARAGE_IS_CLOSED;
	dc_motor_rotate_seconds(100,DC_MOTOR_ROTATE_ANTICLOCKWISE,GARAGE_TIME);
}
//----------------------------------------------------------------