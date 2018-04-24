/*
 * usart.h
 *
 * Created: 01/04/2018 23:18:16
 *  Author: BADROUS
 */ 


#ifndef USART_H_
#define USART_H_
//-----------------------------------------------------
#include "master_config.h"
#include <string.h>
//-----------------------------------------------------------
#define INTERRUPT_ENABLE 1
#define BAUDRATE 9600
#define BAUD_VALUE ((F_CPU)/16/(BAUDRATE))-1
//-----------------------------------------------------------
void serial_init();
//---------------------------------------------
#if (INTERRUPT_ENABLE !=1)
u8 serial_write(u8 data);
u8 serial_read(u8* data);
u8 serial_printf(char* data);
void serial_print_new_line(void);
void serial_print_tab(void);
//----------------------------------------------
#else
void disable_rx_interrupt();
void disable_tx_interrupt();
void enable_rx_interrupt();
void enable_tx_interrupt();
#endif
//----------------------------------------------
#endif /* USART_H_ */