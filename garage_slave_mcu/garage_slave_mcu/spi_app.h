/*
 * spi_app.h
 *
 * Created: 31/03/2018 5:35:03
 *  Author: BADROUS
 */ 
//-------------------------------------------------------
#ifndef SPI_APP_H_
#define SPI_APP_H_
//-------------------------------------------------------------
#include "slave_config.h"
#include "spi.h"
#include <avr/interrupt.h>
//-----------------------------------------------------------
typedef enum
{
	NO_SPI_DATA=0,       // ms
	REQUEST_SLAVE,    //m
	PASSWORD_CHECK_REQUEST,  //s
	PASSWORD_CHECK_RESPOND,  //m
	VALID_PASSWORD,    //m
	INVALID_PASSWORD,   //m
	SLAVE_LOCKED,			//s
	SLAVE_UNLOCK,      //m
	DONE_SPI,           //s
	OPEN_GARAGE_DATA,  //m
	CLOSE_GARAGE_DATA //m
} SPI_APP_PROTOCOL;
//-----------------------------------------------------------
typedef enum
{
	SPI_IDLE_STATE,
	PASSWORD_CHECK_STATE,
	VALID_PASSWORD_STATE,
	INVALID_PASSWORD_STATE,
	LOCK_SLAVE_STATE,
	SLAVE_UNLOCK_STATE
} SPI_SLAVE_STATUS;
//--------------------------------------------------
extern volatile SPI_APP_PROTOCOL spi_master_data;
//--------------------------------------------------
void spi_app_init();
//------------------------------------------------------
#endif /* SPI_APP_H_ */