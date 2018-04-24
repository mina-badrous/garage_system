/*
 * i2c.c
 *
 * Created: 31/03/2018 20:31:08
 *  Author: BADROUS
 */ 
#include "i2c.h"

void i2c_init( void )
{
	TWSR=0;
	TWBR=(u8)I2C_BIT_RATE;  //casting
	set_bit(TWCR,TWEN);
}

u8 i2c_start_condition()
{
	TWCR= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & (0xF8)) != START_CONDITION_STATUS)
	{
		return 1;  //error 
	}
	else
	{
		return 0;  //start done
	}
}

u8 i2c_send_address(u8 address,u8 rw)
{
	TWDR= address+rw ;
	TWCR = (1<<TWINT) | (1<<TWEN);  //start transmition
	while(!(TWCR & (1<<TWINT)));
	if(((TWSR & (0xF8)) != SLAVE_ADDRESS_READ_ACK_STATUS) && ((TWSR & (0xF8)) != SLAVE_ADDRESS_WRITE_ACK_STATUS))
	{
		return 1;  //error
	}
	else
	{
		return 0;
	}			
}

u8 i2c_send_data(u8 data )
{
	
	TWDR= data ;
	TWCR = (1<<TWINT) | (1<<TWEN);  //start transmition
	while(!(TWCR & (1<<TWINT)));
		
	if((TWSR & (0xF8)) != DATA_SENT_ACK_STATUS)
	{
		return 1;  //error
	}
	else
	{
		return 0;
	}
}


void i2c_stop_condition()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

u8 i2c_restart_condition()
{
	TWCR= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	if((TWSR & (0xF8)) != RESTART_CONDITION_STATUS)
	{
		return 1;  //error
	}
	else
	{
		return 0;  //start done
	}
}


u8 i2c_ack_read_data()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

u8 i2c_nack_read_data()
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}




