/*
 * serial_interrupt.h
 *
 * Created: 23/04/2018 11:23:35
 *  Author: BADROUS
 */ 


#ifndef SERIAL_INTERRUPT_H_
#define SERIAL_INTERRUPT_H_
//------------------------------------------------
#include "master_config.h"
#include "usart.h"
#include "avr/interrupt.h"
//--------------------------------------------
typedef union
{
	char* string;
	u8 ascii;
} STRING_CHAR;

typedef struct
{
	STRING_CHAR data;
	u8 length;
	u8 index;
} SHELL_DATA;
//-----------------------------------------------------
#define MAX_INPUT_CHAR 20
//------------------------------------------------------
extern volatile u8 rx_interrupt_status;
extern SHELL_DATA* data_to_send_address;
extern SHELL_DATA rx_buffer;
//-----------------------------------------------------------
void serial_interrupt_init();
void flush_buffer();
void new_line();
void back_line();
//-----------------------------------------------
#endif /* SERIAL_INTERRUPT_H_ */