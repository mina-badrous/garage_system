/*
 * dc_motor.h
 *
 * Created: 01/04/2018 20:13:07
 *  Author: BADROUS
 */ 
//---------------------------------------------------
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
//-----------------------------------------
#include "pwm.h"
//----------------------------------------
#define DC_MOTOR_ROTATE_CLOCKWISE 0
#define DC_MOTOR_ROTATE_ANTICLOCKWISE 1
#define GARAGE_TIME 8
//-------------------------------------------------
typedef enum
{
	GARAGE_IS_OPENED,
	GARAGE_IS_CLOSED	
} GARAGE_STATE;
//----------------------------------------------------
extern GARAGE_STATE e_garage_state;
//--------------------------------------------------
void dc_motor_init();    //init dc motor
void open_garage_close();  //open garage then wait then close
void open_garage();			//open garage
void close_garage();		//close garage
//--------------------------------------------------------------
#endif /* DC_MOTOR_H_ */