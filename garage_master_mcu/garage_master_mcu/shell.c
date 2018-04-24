/*
 * shell.c
 *
 * Created: 02/04/2018 14:44:38
 *  Author: BADROUS
 */ 
//--------------------------------------------------------
#include "shell.h"
//-----------------------------------------------------------------
static void menu_func_0();
static void menu_func_1();
static void menu_func_2();
static void menu_func_3();
static void menu_func_4();
static void menu_func_5();
static void opening_garage_from_shell();
static void closing_garage_from_shell();
static void shell_print_with_new_line(SHELL_DATA* strings);
//-----------------------------------------------------------------
ptr_to_function ptrfunc[MENU_OPTIONS]={menu_func_0,menu_func_1,menu_func_2,menu_func_3,menu_func_4,menu_func_5};
//-----------------------------------------------------
SHELL_DATA init_data={{"ENTER ADMIN PASSWORD TO LOGIN : "},32,0};
SHELL_DATA success_data={{"LOGIN SUCCESSFULLY ..... "},25,0};
SHELL_DATA unsuccess_data={{"WRONG PASSWORD TRY AGAIN ..... "},31,0};
//---------------------------------------------------------------	
SHELL_DATA menu_data[MENU_OPTIONS]={{{"ENTER 0 TO SET ADMIN PASSWORD "},30,0},
						 {{"ENTER 1 TO SET USER PASSWORD "},29,0},
						 {{"ENTER 2 TO OPEN GARAGE "},23,0},	
						 {{"ENTER 3 TO CLOSE GARAGE "},24,0},	
						 {{"ENTER 4 TO UNLOCK GARAGE "},24,0},
						 {{"ENTER 5 TO EXIT "},16,0}};
//-------------------------------------------------------------------
SHELL_DATA prompt_data={{">>> "},4,0};		

//----------------------------------------------------------
SHELL_DATA new_admin_pass={{"ENTER ADMIN NEW PASSWORD : "},27,0};
SHELL_DATA new_user_pass={{"ENTER USER NEW PASSWORD : "},26,0};
SHELL_DATA open_garage_string=  {{"GARAGE IS OPENING ....... "},26,0};	
SHELL_DATA close_garage_string=  {{"GARAGE IS CLOSING ....... "},26,0};	
SHELL_DATA log_out_data={{"LOGING OUT , PLEASE WAIT ....... "},33,0};
SHELL_DATA unlock_data={{"UNLOCKING  , GARAGE IS OPENING ....... "},39,0};
SHELL_DATA unlock_data_error={{"SLAVE IS ALREADY UNLOCKED ....... "},34,0};
SHELL_DATA open_garage_error={{"GARAGE IS ALREADY OPENED ....... "},33,0};
SHELL_DATA close_garage_error={{"GARAGE IS ALREADY CLOSED ....... "},32,0};	
//-------------------------------------------			
volatile u8 spi_unlock_flag=0;
//--------------------------------------------------------------				
void shell_init()
{
	data_to_send_address=&init_data;
	enable_tx_interrupt();
}
//-------------------------------------------------------------
void admin_shell_password_enter()
{
	enable_rx_interrupt();
	rx_interrupt_status=1;
}
//----------------------------------------------------------
u8 admin_shell_password_check()
{
	volatile u8 index,error=0;
	if(rx_buffer.length !=4)
	{ 
		data_to_send_address=&unsuccess_data;
		enable_tx_interrupt();
		return 1; //error 
	}	
	for(index=0;index<MAX_PASSWORD_DIGIT;index++)
	{
		if(rx_buffer.data.string[index]!=admin_password[index])
		{
			error=1;
		}
	}
	if(error==1)
	{
		
		data_to_send_address=&unsuccess_data;
		enable_tx_interrupt();
		
	}
	else
	{
			data_to_send_address=&success_data;
			enable_tx_interrupt();
	}
	return error;
}
//------------------------------------------------------
void menu()
{
	u8 index;
	for(index=0;index<MENU_OPTIONS;index++)
	{
		data_to_send_address=&(menu_data[index]);
		enable_tx_interrupt();
		_delay_ms(100);	
		new_line();
	}
	data_to_send_address=&prompt_data;
	enable_tx_interrupt();
}
//-------------------------------------------------------
u8 menu_selected_check()
{
	u8 volatile index;
	
	index=rx_buffer.data.string[0];
	if(rx_buffer.length !=1) return 255; // many input
	flush_buffer();
	if(index >='0' && index<='5')
	{
		index=index-48;
		ptrfunc[index]();
		return index;
	}
	else
	{
		return 255;  //not in range 
	}
}
//---------------------------------------------------------
static void menu_func_0()  //reset admin pass
{
	u8 index;
	data_to_send_address=&new_admin_pass;
	enable_tx_interrupt();
	_delay_ms(100);
	rx_interrupt_status=1;
	enable_rx_interrupt();
	while(rx_interrupt_status==1);
	for(index=0;index<MAX_PASSWORD_DIGIT;index++)
	{
		admin_password[index]=rx_buffer.data.string[index];
	}
	flush_buffer();
	set_admin_password();
}
//----------------------------------------------------
static void menu_func_1()  // reset user pass
{
	u8 index;
	data_to_send_address=&new_user_pass;
	enable_tx_interrupt();
	_delay_ms(100);
	rx_interrupt_status=1;
	enable_rx_interrupt();
	while(rx_interrupt_status==1);
	for(index=0;index<MAX_PASSWORD_DIGIT;index++)
	{
		user_password[index]=rx_buffer.data.string[index];
	}
	flush_buffer();
	set_user_password();
}
//-----------------------------------------------------------
static void menu_func_2()  //open garage 
{
	if(e_garage_state==GARAGE_IS_CLOSED)
	{
		shell_print_with_new_line(&open_garage_string);
		open_garage();
	}
	else
	{
		shell_print_with_new_line(&open_garage_error);
	}
	
}
//---------------------------------------------------------
static void menu_func_3()  //close garage
{
	if(e_garage_state==GARAGE_IS_OPENED)
	{
		shell_print_with_new_line(&close_garage_string);
		close_garage();
	}
	else
	{
		shell_print_with_new_line(&close_garage_error);
	}
	
}
//--------------------------------------------------------
static void menu_func_4()  // unlock garage 
{	
	if(spi_master_state ==LOCK_SLAVE_STATE)
	{
		spi_unlock_flag=1;
		spi_send_recieve(SLAVE_UNLOCK);
		_delay_ms(500);
		spi_send_recieve(OPEN_GARAGE_DATA);
		opening_garage_from_shell();
		spi_send_recieve(CLOSE_GARAGE_DATA);
		closing_garage_from_shell();
	}
	else
	{
		shell_print_with_new_line(&unlock_data_error);
	}	
}
//----------------------------------------------------------
static void menu_func_5()  // exit menu
{
	shell_print_with_new_line(&log_out_data);
}
//------------------------------------------------------------
void opening_garage_from_shell()
{
	shell_print_with_new_line(&unlock_data);
	open_garage();
}
//------------------------------------------------------------
void closing_garage_from_shell()
{
	shell_print_with_new_line(&close_garage_string);
	close_garage();
}
//---------------------------------------------------------
static void shell_print_with_new_line(SHELL_DATA* strings)
{
	data_to_send_address=strings;
	enable_tx_interrupt();
	_delay_ms(100);
	new_line();
	_delay_ms(100);
	new_line();
	_delay_ms(100);
}
//----------------------------------------------------------