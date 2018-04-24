/*
 * serial_interrupt.c
 *
 * Created: 23/04/2018 11:23:54
 *  Author: BADROUS
 */ 
#include "serial_interrupt.h"
//-------------------------------------------------------
char rx_flush_arr[MAX_INPUT_CHAR];
SHELL_DATA enter_key_stroke={{(char*)0x0D},1,0};   // new line char
SHELL_DATA backspace_key_stroke={{(char*)0x08},1,0};
//------------------------------------------------
char rx_arr[MAX_INPUT_CHAR];
SHELL_DATA rx_buffer={{rx_arr},MAX_INPUT_CHAR,0};
volatile u8 rx_interrupt_status=0;
SHELL_DATA* data_to_send_address;
//------------------------------------------------------
ISR(USART_UDRE_vect)   //serial tx interrupt service routine
{
	if(data_to_send_address->length >1)
	{
		UDR=data_to_send_address->data.string[(data_to_send_address->index)];
		(data_to_send_address->index)++;
		if((data_to_send_address->index)==data_to_send_address->length)
		{
			data_to_send_address->index=0;
			disable_tx_interrupt();
			
		}
	}
	else
	{
		UDR=data_to_send_address->data.ascii;
		disable_tx_interrupt();
	}
	
}


ISR(USART_RXC_vect)  //serial rx interrupt service routine
{
	char temp;
	if(rx_buffer.index <rx_buffer.length) //check buffer size limit
	{
		temp=UDR;
		if(temp !=0x0D)  //if not cariage return
		{
			rx_buffer.data.string[rx_buffer.index]=temp;  //save data in index
			(rx_buffer.index)++;  // increment index
		}
		else    //if the input is enter char
		{
			rx_buffer.length=(rx_buffer.index); //save length of the string
			rx_buffer.index=0;
			disable_rx_interrupt();
			rx_interrupt_status=0;
		}
		
	}
	else
	{
		rx_buffer.index=0;
	}
}

void serial_interrupt_init()
{
	serial_init();
}

//-------------------------------------------------------end of ISR
void flush_buffer()
{
	rx_buffer.data.string=rx_flush_arr;
	rx_buffer.length=MAX_INPUT_CHAR;
	rx_buffer.index=0;
}


void new_line()
{
	data_to_send_address=&enter_key_stroke;
	enable_tx_interrupt();
}
void back_line()
{
	data_to_send_address=&backspace_key_stroke;
	enable_tx_interrupt();
}