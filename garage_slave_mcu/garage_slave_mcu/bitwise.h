#ifndef __BITWISE_H_
#define __BITWISE_H_
//----------------------------------------------------
#define set_bit(reg,position) (reg |=(1<<position))
#define clear_bit(reg,position) (reg &=~(1<<position))
#define toggle_bit(reg,position) (reg ^=(1<<position))
#define check_bit(reg,position) (((reg)&(1<<position))>>position)
//-----------------------------------------------------------------
#endif // __BITWISE_H_
