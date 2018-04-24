/*
 * keypad.h
 *
 * Created: 28/03/2018 6:06:39
 *  Author: BADROUS
 */ 
#ifndef KEYPAD_H_
#define KEYPAD_H_
//-----------------------------------------------------------
#include "slave_config.h"
//-----------------------------------------------------------------
#define FIRST_COLUMN 6
#define SECOND_COLUMN 5
#define THIRD_COLUMN 3
#define NO_COLUMN 7
//------------------------------------------------------------
u8 keypad_read(void);  //return 1 if no button pressed else ascii of digit
//--------------------------------------------------------
#endif /* KEYPAD_H_ */