/*
 * master_config.h
 *
 * Created: 01/04/2018 19:29:53
 *  Author: BADROUS
 */ 
//--------------------------------------------------
#ifndef MASTER_CONFIG_H_
#define MASTER_CONFIG_H_
//--------------------------------------------------
#include "int.h"
#include "bitwise.h"
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
//---------------------------------------------------------
/*spi connection*/
#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SPI_PIN PINB

#define SPI_SS 4
#define SPI_MOSI 5
#define SPI_MISO 6
#define SPI_SCK 7
/*spi connection*/
//----------------------------------------------------
/*motor connection */
#define MOTOR_PORT PORTD
#define MOTOR_DDR DDRD
#define MOTOR_PIN PIND
#define MOTOR_IN1 5
#define MOTOR_IN2 6
#define MOTOR_PWM 7
//--------------------------------------------------
typedef	enum 
{
	INIT_STATE,
	LOGGED_OUT_STATE,
	MENU_STATE,
	RESET_ADMIN_PASSWORD_STATE,
	RESET_USER_PASSWORD_STATE,
	OPEN_GARAGE_STATE,
	CLOSE_GARAGE_STATE,
	UNLOCK_SLAVE_STATE,
	EXIT_MENU_STATE
		
} MASTER_MCU_STATE;
//-----------------------------------------------------
#endif /* MASTER_CONFIG_H_ */