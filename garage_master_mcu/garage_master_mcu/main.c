/*
 * main.c
 *
 * Created: 12/04/2018 13:54:24
 *  Author: BADROUS
 */ 
//---------------------------------------------------------
#include "master_config.h"
#include "shell.h"
#include "eeprom.h"
#include "spi_app.h"
#include "dc_motor.h"
//-----------------------------------------------------globals
volatile MASTER_MCU_STATE master_mcu_state=INIT_STATE;
//------------------------------------------------------------
void mcu_state(); 
void init_mcu();
void logged_out_mcu_func();
void menu_mcu_func();
//-------------------------------------------------------
int main(void)
{
	sei();
	while(1)
	{
		mcu_state();
	}
}
//-------------------------------------------------------
void mcu_state()
{
	switch(master_mcu_state)
	{
		case INIT_STATE :
		{
					init_mcu();	
					master_mcu_state=LOGGED_OUT_STATE;		
					break;
		}					
		case LOGGED_OUT_STATE:
		{
					logged_out_mcu_func();
					master_mcu_state=MENU_STATE;
					break;
		}					
		case MENU_STATE :
		{
					menu_mcu_func();
					master_mcu_state=LOGGED_OUT_STATE;
					break;
		}					
		default:
					break;		
	}
}
//----------------------------------------------------------
void init_mcu()
{
	serial_interrupt_init();
	spi_master_init();
	dc_motor_init();
	load_recent_password();   //check if the factory default or user set new password
}
//------------------------------------------------------------
void logged_out_mcu_func()
{
	u8 error=0;
	 while(1)  //init terminal wait for admin password
	 {
		 flush_buffer();
		 shell_init();
		 _delay_ms(100);
		 admin_shell_password_enter();
		 while(rx_interrupt_status==1)
		 {
			 master_spi_state();
		 }
		 error=admin_shell_password_check();
		 if(error==0) break;
		 _delay_ms(100);
		 new_line();
		 flush_buffer();
	 }
}
//-------------------------------------------------------------
void menu_mcu_func()
{
	u8 menu_selected_index=0;
	while(1)  //admin success password code
	{
		_delay_ms(100);
		new_line();
		_delay_ms(50);
		new_line();
		flush_buffer();
		menu();
		rx_interrupt_status=1;
		enable_rx_interrupt();
		while(rx_interrupt_status==1)
		{
			master_spi_state();
		}
		menu_selected_index=menu_selected_check();
		if(menu_selected_index==255) continue;
		else if(menu_selected_index==5) break;
	}  
}
//---------------------------------------------------------



