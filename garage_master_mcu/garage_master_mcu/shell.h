/*
 * shell.h
 *
 * Created: 02/04/2018 14:44:21
 *  Author: BADROUS
 */ 


#ifndef SHELL_H_
#define SHELL_H_
//-------------------------------------------------------
#include "master_config.h"
#include "serial_interrupt.h"
#include "eeprom.h"
#include "dc_motor.h"
#include "spi_app.h"
//-----------------------------------------------------
#define MENU_OPTIONS 6
//----------------------------------------------------
extern volatile u8 spi_unlock_flag;
//-----------------------------------------------------
typedef void (*ptr_to_function)(void);
//------------------------------------------------
void shell_init();                  //enable tx interrupt
void admin_shell_password_enter();  //enable rx interrupt
u8 admin_shell_password_check();    //check admin password
void menu();						//menu functions
u8 menu_selected_check();			//return selected index
//------------------------------------------------------------
#endif /* SHELL_H_ */