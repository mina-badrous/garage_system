/*
 * lcd.c
 *
 * Created: 27/03/2018 2:50:21
 *  Author: BADROUS
 */ 
//--------------------------------------------------------------
#include "lcd.h"
//-------------------------------------------------------------
static void send_cmd(u8 command);
static void send_data(u8 data);
static void latch_data();
//-------------------------------------------------------------
void clear_screen()
{
	send_cmd(0x01);
	_delay_ms(100);
}
//----------------------------------------------------------
void lcd_init()
{
	_delay_ms(15);       //delay 15 ms
	LCD_DIR=0xFF;           //output
	send_cmd(0x33);     //4 bit 2  line
	send_cmd(0x32);
	send_cmd(0x28);
	send_cmd(0x0C);   //to open display cursor off and blink off
		
}
//--------------------------------------------------------
u8 lcd_print(u8 data,u8 line,u8 position)
{
	u8 l=0;
	if(line>1 || line<0)
	{
		return 1;   //error
	}
	if(position>15 || position<0)
	{
		position=position % 16;  //error
	}
	switch (line)
	{
		case 0:
				l=0x80 +position;
				break;
		default:
				l=0xc0+position;
				break;
		
	}
	send_cmd(l);    //position    11
	send_data(data);  //data
	return 0;
}
//----------------------------------------------------------
u8 lcd_print_string(u8* str,u8 line,u8 position)
{
	u8 length =(u8)strlen((char*)str);
	if(length > 16-position)
	{
		return 1;    // error 
	}
	else
	{
		while(*str !='\0')
		{
			lcd_print(*str,line,position);
			position++;
			str++;
		}
		return 0;
	}
}
//----------------------------------------------------
u8 lcd_print_string_sequence(u8* str,u8 line,u8 position)
{
	u8 length =strlen((char*)str);
	if(length > 16-position)
	{
		return 1;    // error
	}
	else
	{
		while(*str !='\0')
		{
			lcd_print(*str,line,position);
			position++;
			str++;
			_delay_ms(SEQUENCE_DELAY);
		}
		return 0;
	}
}
//----------------------------------------------------------------
static void send_cmd(u8 command)
{
	/*
	First, send Higher nibble of command.
	Make RS pin low, RS=0 (command reg.)
	Give High to Low pulse at Enable (E).
	Send lower nibble of command.
	Give High to Low pulse at Enable (E)
	*/
	LCD_PORT= (LCD_PORT & (0xf0)) | ((command & 0xf0)>>4);
	clear_bit(LCD_PORT,LCD_RS);
	latch_data();
	_delay_ms(2);
	LCD_PORT= (LCD_PORT & (0xf0)) | (command & 0x0f);
	latch_data();
	_delay_us(150);
	
}
//------------------------------------------------------------
static void send_data(u8 data)
{
	LCD_PORT = (LCD_PORT & (0xf0)) | ((data & 0xf0)>>4);
	set_bit(LCD_PORT,LCD_RS);
	latch_data();
	_delay_ms(2);
	LCD_PORT = (LCD_PORT & (0xf0)) | (data & 0x0f);
	latch_data();
	_delay_us(150);
}
//-----------------------------------------------------------
static void latch_data()
{
	set_bit(LCD_PORT,LCD_ENABLE);
	_delay_us(20);
	clear_bit(LCD_PORT,LCD_ENABLE);
}
//------------------------------------------------------------