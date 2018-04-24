/*
 * spi_app.c
 *
 * Created: 31/03/2018 5:35:28
 *  Author: BADROUS
 */ 
//------------------------------------------------------------
#include "spi_app.h"
//----------------------------------------------------------
extern u8 temp_password_string[4];
extern volatile SLAVE_MCU_STATE slave_mcu_state;
//-----------------------------------------------------
volatile SPI_APP_PROTOCOL spi_master_data=NO_SPI_DATA;
volatile u8 temp_password_index;
//-------------------------------------------------------
ISR(SPI_STC_vect)
{
	spi_master_data=(SPI_APP_PROTOCOL)SPDR;
	
	switch(spi_master_data)
	{
		case NO_SPI_DATA :
		{
				SPDR=(u8)NO_SPI_DATA;
				break;
		}				
		case REQUEST_SLAVE :
		{
			if(slave_mcu_state == CHECK_PASSWORD_STATE)
			{
				SPDR=(u8)PASSWORD_CHECK_REQUEST;//req
			}
			else
			{
				SPDR=(u8)NO_SPI_DATA;
			}
			break;
		}		
		case PASSWORD_CHECK_RESPOND :
		{
			SPDR=(u8)temp_password_string[temp_password_index];
			temp_password_index++;
			if(temp_password_index==4)
			{
				temp_password_index=0;
			}
			break;
		}			
		case VALID_PASSWORD :
		{
			slave_mcu_state=VALID_STATE;
			SPDR=(u8)DONE_SPI;
			break;
		}
		/*
		case OPEN_GARAGE_DATA :
		{
			slave_mcu_state=INVALID_STATE;
			SPDR=(u8)DONE_SPI;
			break;
		}
		case CLOSE_GARAGE_DATA :
		{
			slave_mcu_state=INVALID_STATE;
			SPDR=(u8)DONE_SPI;
			break;
		}	
		*/	
		case INVALID_PASSWORD :
		{
			slave_mcu_state=INVALID_STATE;
			SPDR=(u8)DONE_SPI;
			break;
		}		
		case SLAVE_UNLOCK :
		{
			slave_mcu_state=UNLOCKED_MCU_STATE;
			SPDR=(u8)NO_SPI_DATA;
			break;
		}		
		default:
		SPDR=(u8)NO_SPI_DATA;
		break;
		
	}
	
}

void spi_app_init()
{
	sei();
	spi_slave_init();
	_delay_ms(100);
}
