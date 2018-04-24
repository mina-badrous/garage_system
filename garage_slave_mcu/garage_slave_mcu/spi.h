/*
 * spi.h
 *
 * Created: 31/03/2018 3:11:42
 *  Author: BADROUS
 */ 
#ifndef SPI_H_
#define SPI_H_
//----------------------------------------------------------
#include "slave_config.h"
//-------------------------------------------------define
#define MSB 0
#define LSB 1
#define SPI_MASTER 1
#define SPI_SLAVE 0
//------------------------------------------config SPI 
#define SPI_INTERRUPT_ENABLE 1
#define SPI_DATA_ORDER MSB
#define SPI_MODE SPI_SLAVE
//-------------------------------------------------
void spi_master_init();
void spi_slave_init();
//--------------------------------------------------
void spi_start(void);
void spi_end(void);
//----------------------------------------------------
void spi_send(u8);
u8 spi_read(void);
//------------------------------------------------------
#endif /* SPI_H_ */