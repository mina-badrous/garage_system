/*
 * spi.c
 *
 * Created: 31/03/2018 3:35:09
 *  Author: BADROUS
 */ 
//----------------------------------------------------------------
#include "spi.h"
//-------------------------------------------------------------------
void spi_master_init()
{
	
	#if SPI_INTERRUPT_ENABLE == 1
		set_bit(SPCR,SPIE);
	#endif
	
	set_bit(SPCR,SPE); //enable spi
	
	//data order config
	#if SPI_DATA_ORDER == MSB
	clear_bit(SPCR,DORD);
	#elif SPI_DATA_ORDER == LSB
	set_bit(SPCR,DORD);
	#endif
	
	set_bit(SPCR,MSTR);  //as master
	 
	clear_bit(SPCR,CPOL);   //low as idle
	 
	clear_bit(SPCR,CPHA);   //sample at leading edge  (rising) mode 0
	
	clear_bit(SPCR,SPR0);
	clear_bit(SPCR,SPR1);  //freq = fclk/4
	clear_bit(SPSR,SPI2X);
	 
	set_bit(SPI_DDR,SPI_MOSI);
	set_bit(SPI_DDR,SPI_SCK);
	set_bit(SPI_DDR,SPI_SS);
	clear_bit(SPI_DDR,SPI_MISO);
	set_bit(SPI_PORT,SPI_SS);
	
}
//--------------------------------------------------------------
void spi_slave_init()
{
	#if SPI_DATA_ORDER == MSB
	clear_bit(SPCR,DORD);
	#elif SPI_DATA_ORDER == LSB
	set_bit(SPCR,DORD);
	#endif
	clear_bit(SPCR,MSTR);  //as slave
	
	clear_bit(SPCR,CPOL);   //low as idle
	
	clear_bit(SPCR,CPHA);   //sample at leading edge
	
	clear_bit(SPI_DDR,SPI_MOSI);
	clear_bit(SPI_DDR,SPI_SCK);
	clear_bit(SPI_DDR,SPI_SS);
	set_bit(SPI_DDR,SPI_MISO);
	SPDR=0;
	#if SPI_INTERRUPT_ENABLE == 1
	set_bit(SPCR,SPIE);
	#endif
	set_bit(SPCR,SPE);  //enable spi
}

//------------------------------------------------------------------
void spi_send(u8 data)
{
	SPDR=data;
	while(!(SPSR & (1<<SPIF)));
}

u8 spi_read(void)
{
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}


void spi_start(void)
{
	clear_bit(SPI_PORT,SPI_SS);
}
void spi_end(void)
{
	set_bit(SPI_PORT,SPI_SS);
}
//-----------------------------------------------------
