/*
 * main.c
 *
 * Created: 12/04/2018 16:22:19
 *  Author: BADROUS
 */ 
//----------------------------------------------------------
#include "slave_config.h"
#include "lcd.h"
#include "keypad.h"
#include "spi_app.h"
//---------------------------------globals
u8 temp_password_string[4];    //temp array to save user input pass
u8 invalid_password_counter=0;  //#of wrong pass
//--------------------------------states
volatile SLAVE_MCU_STATE slave_mcu_state=INIT_STATE;
//-------------------------------------------
static void mcu_state();        //slave mcu state machine 
static void user_setup(void);		//
static void password_read(void);
static void valid_message(void);
static void invalid_message(void);
static void invalid_locked_message(void);
static void slave_mcu_init(void);
static void opening_message(void);
static void closing_message(void);
static void unlocked_message();
//---------------------------------------------------------
int main()
{
	slave_mcu_init();
	while(1)
	{
		mcu_state();
		
	}
}
//----------------------------------------------------------
static void mcu_state()
{
	switch(slave_mcu_state)	
	{
		case INIT_STATE :
		{
					clear_screen();
					_delay_ms(100);
					lcd_print_string_sequence((u8*)"WELCOME",0,5);
					_delay_ms(500);
					slave_mcu_state = USER_INPUT_STATE;
					break;
		}			
		case USER_INPUT_STATE :
		{			
					user_setup();
					password_read();
					slave_mcu_state = CHECK_PASSWORD_STATE;
					SPDR=(u8)PASSWORD_CHECK_REQUEST;
					break;
		}					
		case CHECK_PASSWORD_STATE :
		{
					while(slave_mcu_state==(u8)CHECK_PASSWORD_STATE);
					break;
		}					
		case VALID_STATE :
		{
					valid_message();
					while (spi_master_data !=OPEN_GARAGE_DATA);
					opening_message();
					while (spi_master_data !=CLOSE_GARAGE_DATA);
					closing_message();
					while (spi_master_data ==CLOSE_GARAGE_DATA);
					_delay_ms(1000);
					slave_mcu_state=(u8)INIT_STATE;
					invalid_password_counter=0;
					break;
		}					
		case INVALID_STATE :
		{
					invalid_password_counter++;
					if(invalid_password_counter<3)
					{
						invalid_message();
						slave_mcu_state=(u8)USER_INPUT_STATE;
						break;
					}
					else
					{
						slave_mcu_state=(u8)LOCKED_MCU_STATE;
						SPDR=(u8)SLAVE_LOCKED;
					}
					break;
		}					
		case LOCKED_MCU_STATE :
		{
					invalid_locked_message();
					while(slave_mcu_state==(u8)LOCKED_MCU_STATE); //locked
					invalid_password_counter=0;
					clear_screen();
					_delay_ms(100);
					slave_mcu_state=(u8)UNLOCKED_MCU_STATE;
					break;
		}
		case UNLOCKED_MCU_STATE :
		{
			unlocked_message();
			_delay_ms(500);
			while (spi_master_data !=OPEN_GARAGE_DATA);
			opening_message();
			while (spi_master_data !=CLOSE_GARAGE_DATA);
			closing_message();
			while (spi_master_data ==CLOSE_GARAGE_DATA);
			slave_mcu_state=INIT_STATE;
			_delay_ms(500);
			break;
		}					
		default:
					break;
	}
}

//------------------------------------------------------------------
static void user_setup(void)
{
	clear_screen();
	_delay_ms(100);
	lcd_print_string_sequence((u8*)"ENTER PASSWORD",0,1);
}
//---------------------------------------------------------------
static void password_read(void)
{
	u8 index;
	for(index=0;index<4;index++)
	{
		temp_password_string[index]=1;  //to repeat till enter first char
		while(temp_password_string[index] ==1)
		{
			temp_password_string[index]=keypad_read();
		}
		lcd_print('*',1,index+5);
		_delay_ms(300);
	}
}
//-------------------------------------------------------------
static void valid_message(void)
{
	clear_screen();
	_delay_ms(100);
	lcd_print_string_sequence((u8*)"WELCOME  MINA",0,0);
}
//------------------------------------------------------------------
static void invalid_message(void)
{
	clear_screen();
	_delay_ms(100);
	lcd_print_string((u8*)"WRONG PASSWORD",0,0);
	_delay_ms(1000);
	clear_screen();
	_delay_ms(100);
	lcd_print_string((u8*)"WRONG PASSWORD",0,0);
	_delay_ms(1000);
	clear_screen();
	_delay_ms(100);
	lcd_print_string((u8*)"TRY AGAIN ..",0,0);
	_delay_ms(1000);
	clear_screen();
	_delay_ms(100);
}
//------------------------------------------------------
static void invalid_locked_message(void)
{
	clear_screen();
	_delay_ms(100);
	lcd_print_string((u8*)"WRONG PASSWORD",0,0);
	_delay_ms(1000);
	clear_screen();
	_delay_ms(100);
	lcd_print_string((u8*)"WRONG PASSWORD",0,0);
	_delay_ms(1000);
	clear_screen();
	_delay_ms(100);
	lcd_print_string((u8*)"LOCKED",0,5);
	_delay_ms(100);
}
//-----------------------------------------------------------------
static void slave_mcu_init( void )
{
	lcd_init();
	spi_app_init();
}
//---------------------------------------------------------
static void opening_message(void)
{
	clear_screen();
	_delay_ms(100);
	lcd_print_string_sequence((u8*)"OPENING GARAGE",0,0);
	_delay_ms(100);
}
static void closing_message(void)
{
	clear_screen();
	_delay_ms(100);
	lcd_print_string_sequence((u8*)"CLOSING GARAGE",0,0);
	_delay_ms(100);
}
static void unlocked_message()
{
	clear_screen();
	_delay_ms(100);
	lcd_print_string_sequence((u8*)"UNLOCKED",0,0);
	_delay_ms(100);
}
