#include "init.h"


#define lcd_rs (1<<13)
#define lcd_rw (1<<14)
#define lcd_en (1<<15)

#define HIGH 1
#define LOW 0


#define digitalWrite(pin,val) gpio_bit_write(GPIOB,pin,val)



void write(uint8_t dat) {
    GPIO_OCTL(GPIOA) &= 0xffffff00;
    GPIO_OCTL(GPIOA) |= dat;
}


void write_command(uint8_t command) {
    digitalWrite(lcd_rs, LOW);
    write(command);
    delay_1ms(5);
    digitalWrite(lcd_en, HIGH);
    delay_1ms(5);
    digitalWrite(lcd_en, LOW);

}

void write_data(uint8_t date) {
    digitalWrite(lcd_rs, HIGH);
    write(date);
    delay_1ms(5);
    digitalWrite(lcd_en, HIGH);
    delay_1ms(5);
    digitalWrite(lcd_en, LOW);
}


void lcd_init() {

    write_command(0x38);    //设置16*2显示,5*7点阵,8位数据口
    write_command(0x0c);     //设置打开显示，且没有光标
    write_command(0x06);     //写一个字符后地址加1
    write_command(0x01);     //显示清零，数据指针清零

}


void write_string(char* str1, char* str2) {
    lcd_clear();
    delay_1ms(5);
    for (int i = 0;str1[i];i++) {
        write_data(str1[i]);
        delay_1ms(5);
    }
    write_command(0x80 + 0x40);
    for (int i = 0;str2[i];i++) {
        write_data(str2[i]);
        delay_1ms(5);
    }
}