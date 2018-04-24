/*
 * eeprom.h
 *
 * Created: 03/04/2018 0:58:18
 *  Author: BADROUS
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
//-----------------------------------------------
#include "i2c_service.h"
//----------------------------------------------globals
#define MAX_PASSWORD_DIGIT 4
extern char user_password[MAX_PASSWORD_DIGIT];
extern char admin_password[MAX_PASSWORD_DIGIT];
//---------------------------------------
#define EEPROM_DEVICE_ADDRESS 0xA0
#define FIRST_TIME_FLAG_ADDRESS 0x00
#define ADMIN_PASS_ADDRESS 0x01
#define USER_PASS_ADDRESS 0x05
//------------------------------------------------------------
void load_recent_password(void);      //check if factory default pass or user set new pass
void set_admin_password(void);
void set_user_password(void);
//-------------------------------------------------------interface
void get_private_admin_password(char* temp_password);
void get_private_user_password(char* temp_password);
void set_private_admin_password(char* temp_password);
void set_private_user_password(char* temp_password);
//----------------------------------------------------------
#endif /* EEPROM_H_ */