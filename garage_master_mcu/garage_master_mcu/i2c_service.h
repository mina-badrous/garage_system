/*
 * i2c_service.h
 *
 * Created: 01/04/2018 0:31:23
 *  Author: BADROUS
 */ 


#ifndef I2C_SERVICE_H_
#define I2C_SERVICE_H_
//-----------------------------------------------------
#include "i2c.h"
//----------------------------------------------------
void i2c_service_init();
u8 write_data_to_device(u8 device_address,u8 byte_address,u8 data);
u8 read_data_from_device(u8 device_address,u8 byte_address,u8* data);
//----------------------------------------------------------------------
#endif /* I2C_SERVICE_H_ */