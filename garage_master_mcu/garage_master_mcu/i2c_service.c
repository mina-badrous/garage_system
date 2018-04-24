/*
 * i2c_service.c
 *
 * Created: 01/04/2018 0:31:54
 *  Author: BADROUS
 */ 
#include "i2c_service.h"


u8 write_data_to_device(u8 device_address,u8 byte_address,u8 data)
{
	u8 temp;
	temp=i2c_start_condition();
	if(temp==1) return 1; //error
	temp=i2c_send_address(device_address,I2C_WRITE);
	if(temp==1) return 1; //error
	temp=i2c_send_data(byte_address);
	if(temp==1) return 1; //error
	temp=i2c_send_data(data);
	if(temp==1) return 1; //error
	i2c_stop_condition();
	return 0;
}

u8 read_data_from_device(u8 device_address,u8 byte_address,u8* data)
{
	u8 temp;
	temp=i2c_start_condition();
	if(temp==1) return 1; //error
	temp=i2c_send_address(device_address,I2C_WRITE);
	if(temp==1) return 1; //error
	temp=i2c_send_data(byte_address);
	if(temp==1) return 1; //error
	temp=i2c_restart_condition();
	if(temp==1) return 1; //error
	temp=i2c_send_address(device_address,I2C_READ);
	if(temp==1) return 1; //error
	*data=i2c_nack_read_data();
	i2c_stop_condition();
	return 0;
}

void i2c_service_init()
{
	i2c_init();
}
