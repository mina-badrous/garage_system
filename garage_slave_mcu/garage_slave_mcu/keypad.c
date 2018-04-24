/*
 * keypad.c
 *
 * Created: 28/03/2018 6:08:57
 *  Author: BADROUS
 */ 
//------------------------------------------------------
#include "keypad.h"
//----------------------------------------------------------
const u8 keypad_char_map[4][3]={{'1','2','3'},
								{'4','5','6'},
								{'7','8','9'},
								{'*','0','#'}	};
//-------------------------------------------------------
static u8 read_column();
static u8 read_row();
//----------------------------------------------------
u8 keypad_read(void)
{
	u8 column=0,row=0;
	KEYPAD_DIR |=(1<<ROW0) | (1<<ROW1) | (1<<ROW2) | (1<<ROW3);
	KEYPAD_DIR &=~((1<<COL0) | (1<<COL1) | (1<<COL2));
	KEYPAD_PORT &=~((1<<ROW0) | (1<<ROW1) | (1<<ROW2) | (1<<ROW3));
	column=read_column();
	switch (column)
	{
		case FIRST_COLUMN :
					row=read_row();
					if(row !=255)
					{
						return keypad_char_map[row][0];	
					}		
							break;
		case SECOND_COLUMN :
							row=read_row();
							if(row !=255)
							{
								return keypad_char_map[row][1];
							}
							break;
		case THIRD_COLUMN :
					row=read_row();
					if(row !=255)
					{
						return keypad_char_map[row][2];
					}
							
					break;
		default:
		return 1;  //no button pressed
		
	}
		return 1;  //no button pressed
}


static u8 read_column()
{
	return ((KEYPAD_PIN & 0x70)>>4);
}

static u8 read_row()
{
	u8 column;
	clear_bit(KEYPAD_PORT,ROW0);
	set_bit(KEYPAD_PORT,ROW1);
	set_bit(KEYPAD_PORT,ROW2);
	set_bit(KEYPAD_PORT,ROW3);
	column=read_column();
	if(column !=NO_COLUMN)
	{
		while(column !=NO_COLUMN)
		{
			column=read_column();      //wait till button released
		}
		return 0;    //first row
	}
	set_bit(KEYPAD_PORT,ROW0);
	clear_bit(KEYPAD_PORT,ROW1);
	set_bit(KEYPAD_PORT,ROW2);
	set_bit(KEYPAD_PORT,ROW3);
	column=read_column();
	if(column !=NO_COLUMN)
	{
		while(column !=NO_COLUMN)
		{
			column=read_column();      //wait till button released
		}
		return 1;    //second row
	}
	set_bit(KEYPAD_PORT,ROW0);
	set_bit(KEYPAD_PORT,ROW1);
	clear_bit(KEYPAD_PORT,ROW2);
	set_bit(KEYPAD_PORT,ROW3);
	column=read_column();
	if(column !=NO_COLUMN)
	{
		while(column !=NO_COLUMN)
		{
			column=read_column();      //wait till button released
		}
		return 2;    //third row
	}
	set_bit(KEYPAD_PORT,ROW0);
	set_bit(KEYPAD_PORT,ROW1);
	set_bit(KEYPAD_PORT,ROW2);
	clear_bit(KEYPAD_PORT,ROW3);
	column=read_column();
	if(column !=NO_COLUMN)
	{
		while(column !=NO_COLUMN)
		{
			column=read_column();      //wait till button released
		}
		return 3;    //fourth row
	}
	
	return 255;     //if no row
}	