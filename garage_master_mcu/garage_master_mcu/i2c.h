/*
 * i2c.h
 *
 * Created: 31/03/2018 20:30:54
 *  Author: BADROUS
 */ 


#ifndef I2C_H_
#define I2C_H_
//------------------------------------------------
#include "master_config.h"
//----------------------------------
#define I2C_SCL_FREQUENCY 10000
#define I2C_BIT_RATE (((F_CPU/I2C_SCL_FREQUENCY)-16)/2)  /*42*/
//-----------------------------------
#define I2C_SCL 0
#define I2C_SDA 1
#define I2C_DDR DDRC
#define I2C_PORT PORTC
#define I2C_PIN PINC
//------------------------------------------------------
#define I2C_READ 1
#define I2C_WRITE 0
#define I2C_ACK 0
#define I2C_NACK 1
//------------------------------------------------
#define START_CONDITION_STATUS 0x08
#define RESTART_CONDITION_STATUS 0x10
#define SLAVE_ADDRESS_WRITE_ACK_STATUS 0x18
#define SLAVE_ADDRESS_READ_ACK_STATUS 0x40
#define DATA_SENT_ACK_STATUS 0x28
#define DATA_READ_ACK_STATUS 0x50
//---------------------------------------------------------
void i2c_init(void); 
u8 i2c_start_condition();
void i2c_stop_condition();
u8 i2c_restart_condition();
u8 i2c_send_address(u8,u8);
u8 i2c_send_data(u8);
u8 i2c_ack_read_data();
u8 i2c_nack_read_data();
#endif /* I2C_H_ */