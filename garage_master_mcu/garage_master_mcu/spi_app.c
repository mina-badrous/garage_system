/*
 * spi_app.c
 *
 * Created: 31/03/2018 5:35:28
 *  Author: BADROUS
 */ 
//--------------------------------------------------
#include "spi_app.h"
//-----------------------------------------------------------
u8 temp_password_string[4];   //temp array to store recived password from slave
u8 temp_password_index=0;      //
volatile SPI_MASTER_STATE spi_master_state=SPI_IDLE_STATE;
//--------------------------------------------------
void master_spi_state()
{
	u8 error=0,index=0,spi_slave_data;
	switch(spi_master_state)
	{
		case SPI_IDLE_STATE :
		{
				spi_slave_data=spi_send_recieve(REQUEST_SLAVE);
				if(spi_slave_data==PASSWORD_CHECK_REQUEST)
				{
					_delay_ms(50);
					spi_master_state=PASSWORD_RESPOND_STATE;
					spi_slave_data=spi_send_recieve(PASSWORD_CHECK_RESPOND);//ack
					_delay_ms(50);
				}
				else
				{
					_delay_ms(300);  //if no check request delay 300 ms
				}
				break;
		}		
		case PASSWORD_RESPOND_STATE ://send 3 respond and one done spi
		{
				for(temp_password_index=0;temp_password_index<3;temp_password_index++)
				{
					temp_password_string[temp_password_index]=spi_send_recieve(PASSWORD_CHECK_RESPOND); //first
					_delay_ms(50);
				}
				temp_password_string[temp_password_index]=spi_send_recieve(DONE_SPI); //last
				_delay_ms(200);
				temp_password_index=0;
				for(index=0;index<4;index++)
				{
					if(temp_password_string[index] != user_password[index])
					{
						error=1;
					}
				}
				if(error==0)
				{
					spi_master_state=VALID_PASSWORD_STATE;
					spi_slave_data=spi_send_recieve(VALID_PASSWORD);//send
				}
				else
				{
					spi_master_state=INVALID_PASSWORD_STATE;
					spi_slave_data=spi_send_recieve(INVALID_PASSWORD);//send
				}
				_delay_ms(50);
				break;
		}		
		case VALID_PASSWORD_STATE :
		{
			_delay_ms(2500);   //time matching
			spi_slave_data=spi_send_recieve(OPEN_GARAGE_DATA);
			open_garage();
			spi_slave_data=spi_send_recieve(CLOSE_GARAGE_DATA);
			close_garage();
			spi_master_state=SPI_IDLE_STATE;
		}		
		break;
		case INVALID_PASSWORD_STATE :
		{
				spi_slave_data=spi_send_recieve(NO_SPI_DATA);//recive
				if(spi_slave_data==SLAVE_LOCKED)
				{
					spi_master_state=LOCK_SLAVE_STATE;
				}
				else
				{
					spi_master_state=SPI_IDLE_STATE;
				}
				break;
		}		
		case LOCK_SLAVE_STATE :
		{
				if(spi_unlock_flag==1)
				{
					spi_unlock_flag=0;
					spi_master_state=SPI_IDLE_STATE;
				}
				break;
		}		
		default:
		break;
	}
}


