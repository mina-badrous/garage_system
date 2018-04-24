/*
 * usart.c
 *
 * Created: 01/04/2018 23:18:33
 *  Author: BADROUS
 */ 
#include "usart.h"
//-----------------------------------------------------
void serial_init()
{
	clear_bit(UCSRA,U2X);
	clear_bit(UCSRA,MPCM);
	clear_bit(UCSRB,UCSZ2);
	set_bit(UCSRB,TXEN);  //enable transmition
	set_bit(UCSRB,RXEN);  //enable reciver
	
	UCSRC = (1<<UCSZ0) | (1<<UCSZ1) | (1<<URSEL);  //8 data no parity 1 stop bit
	UBRRL = BAUD_VALUE ;  //0x33
	UBRRH = 0;
}
//---------------------------------------------------
//if using interrupt or not
#if (INTERRUPT_ENABLE !=1)
u8 serial_write(u8 data )
{
	if(!(UCSRA & (1<<UDRE))) return 1; //error 
	UDR=data;
	return 0;
}

u8 serial_read(u8* data )
{
	if(!(UCSRA & (1<<RXC))) return 1; //error
	*data=UDR;
	return 0;
}

u8 serial_printf( char* data )
{
	u8 length=strlen(data);
	u8 index,error;
	for(index=0;index<length;index++)
	{
		while(1)
		{
			error=serial_write(*data);
			if(error) continue;
			break;
		}
		data++;
	}
	return 0;
}

void serial_print_new_line( void )
{
	u8 error;
	while(1)
	{
		error=serial_write(0x0D);
		if(error) continue;
		break;
	}
}

void serial_print_tab( void )
{
	u8 index,error;
	for(index=0;index<10;index++)
	{
		while(1)
		{
			error=serial_write(' ');
			if(error) continue;
			break;
		}
	}
}

#else
void disable_rx_interrupt()
{
	clear_bit(UCSRB,RXCIE);
}

void disable_tx_interrupt()
{
	clear_bit(UCSRB,UDRIE);
}

void enable_rx_interrupt()
{
	set_bit(UCSRB,RXCIE);
}

void enable_tx_interrupt()
{
	set_bit(UCSRB,UDRIE);
}
#endif

