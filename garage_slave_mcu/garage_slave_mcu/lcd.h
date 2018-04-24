/*
 * lcd.h
 *
 * Created: 27/03/2018 2:44:57
 *  Author: BADROUS
 */ 
//---------------------------------------------------------
#ifndef LCD_H_
#define LCD_H_
//---------------------------------------------------------
#include "slave_config.h"
#include <string.h>
//------------------------------------------------
#define SEQUENCE_DELAY 150
//-------------------------------------------------------------
void lcd_init();   /*initalize lcd*/
u8 lcd_print(u8 data,u8 line,u8 position);  /* print on ascii char at position*/
void clear_screen();  /*clear screen*/
u8 lcd_print_string(u8*,u8 line,u8 position);/*print string at position*/
u8 lcd_print_string_sequence(u8*,u8 line,u8 position);/*print string with delay  at position*/
//-------------------------------------------------------------
#endif /* LCD_H_ */