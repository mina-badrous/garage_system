/*
 * eeprom.c
 *
 * Created: 03/04/2018 0:58:36
 *  Author: BADROUS
 */ 
//-------------------------------------------------
#include "eeprom.h"
//-----------------------------------------------
static u8 first_time_check(void);
static void first_time_save(void);
static void get_admin_password(u8* temp_password); //from eeprom
static void get_user_password(u8* temp_password);
//------------------------------------------------------
char admin_password[MAX_PASSWORD_DIGIT]={'1','2','3','4'};
char user_password[MAX_PASSWORD_DIGIT]={'1','1','1','1'};
//--------------------------------------------------------
static u8 first_time_check( void )
{
	u8 data=0;
	i2c_service_init();
	read_data_from_device(EEPROM_DEVICE_ADDRESS,FIRST_TIME_FLAG_ADDRESS,&data);
	return data;
}

static void first_time_save( void )
{
	//i2c_service_init();
	write_data_to_device(EEPROM_DEVICE_ADDRESS,FIRST_TIME_FLAG_ADDRESS,0xAA);//10101010
	_delay_ms(20);
}

//--------------------------------------------------------------------
void get_admin_password(u8* temp_password)
{
	u8 index;
	for(index=ADMIN_PASS_ADDRESS;index<ADMIN_PASS_ADDRESS+4;index++)
	{
		read_data_from_device(EEPROM_DEVICE_ADDRESS,index,&(temp_password[index-ADMIN_PASS_ADDRESS]));
		_delay_ms(50);
	}
	

}

void set_admin_password( void )
{
	u8 index;
	for(index=ADMIN_PASS_ADDRESS;index<ADMIN_PASS_ADDRESS+4;index++)
	{
		write_data_to_device(EEPROM_DEVICE_ADDRESS,index,admin_password[index-ADMIN_PASS_ADDRESS]);
		_delay_ms(50);
	}
}

void get_user_password(u8* temp_password )
{
	u8 index;
	for(index=USER_PASS_ADDRESS;index<USER_PASS_ADDRESS+4;index++)
	{
		read_data_from_device(EEPROM_DEVICE_ADDRESS,index,&(temp_password[index-USER_PASS_ADDRESS]));
		_delay_ms(50);
	}
}

void set_user_password( void )
{
	u8 index;
	for(index=USER_PASS_ADDRESS;index<USER_PASS_ADDRESS+4;index++)
	{
		write_data_to_device(EEPROM_DEVICE_ADDRESS,index,user_password[index-USER_PASS_ADDRESS]);
		_delay_ms(50);
	}
}

void get_private_admin_password(char* temp_password )
{
	temp_password=admin_password;
}

void get_private_user_password( char* temp_password )
{
	temp_password=user_password;
}

void set_private_admin_password(char* temp_password )
{
	u8 index;
	for(index=0;index<MAX_PASSWORD_DIGIT;index++)
	{
		admin_password[index]=temp_password[index];
	}
}

void set_private_user_password(char* temp_password )
{
	u8 index;
	for(index=0;index<MAX_PASSWORD_DIGIT;index++)
	{
		user_password[index]=temp_password[index];
	}
}

void load_recent_password(void)
{
	u8 first_time_flag=first_time_check();
	if(first_time_flag==0xAA)
	{
		get_admin_password((u8 *)admin_password);
		get_user_password((u8 *)user_password);
	}
	else
	{
		first_time_save();
		set_admin_password();
		set_user_password();
	}
	
}



