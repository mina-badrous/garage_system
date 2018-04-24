/*
 * slave_config.h
 *
 * Created: 27/03/2018 2:29:30
 *  Author: BADROUS
 */ 
#ifndef SLAVE_CONFIG_H_
#define SLAVE_CONFIG_H_
//-----------------------------------------------------------
#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "int.h"
#include "bitwise.h"
//--------------------------------------------------------
/* lcd connections  */
#define LCD_PORT PORTC
#define LCD_DIR DDRC
#define LCD0 0
#define LCD1 1
#define LCD2 2
#define LCD3 3
#define LCD_ENABLE 4
#define LCD_RS 5
/* lcd connections  */
//-------------------------------------------------------
/*keypad connection*/
#define KEYPAD_PORT PORTD
#define KEYPAD_DIR DDRD
#define KEYPAD_PIN PIND
#define ROW0 0
#define ROW1 1
#define ROW2 2
#define ROW3 3
#define COL0 4
#define COL1 5
#define COL2 6
/*keypad connection*/
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

typedef enum 
{
	INIT_STATE=0,
	USER_INPUT_STATE,
	CHECK_PASSWORD_STATE,
	VALID_STATE,
	INVALID_STATE,
	LOCKED_MCU_STATE,
	UNLOCKED_MCU_STATE
	
} SLAVE_MCU_STATE;
//----------------------------------------------------------


#endif /* SLAVE_CONFIG_H_ */