#ifndef INIT_H
#define INIT_H




#include "gd32vf103_gpio.h"
#include "gd32vf103_usart.h"
#include "gd32vf103.h"
#include "gd32vf103_libopt.h"
#include "systick.h"
#include "stdio.h"


//清屏
#define lcd_clear() write_command(0x1)
//光标复位
#define lcd_reset() write_command(0x2)
void write_string(char* str1, char* str2);


void lcd_init();

void init();

extern char str_read[];
uint32_t avaliable();
uint32_t readAll();
void buffClear();
uint32_t readLine();
uint32_t readbyte2();
uint32_t readch();
int _put_char(int ch);



//b0作为控制舵机管脚

void open_door();
void close_door();

//单位：分
extern int TIME_TICK;
extern int tick_1s;




#endif // !INIT_H