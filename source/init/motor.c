#include "init.h"








void open_door() {
    gpio_bit_reset(GPIOB, GPIO_PIN_9);
    for (int i = 0;i < 25;i++) {
        gpio_bit_set(GPIOB, GPIO_PIN_9);
        delay_100us(5);
        gpio_bit_reset(GPIOB, GPIO_PIN_9);
        delay_1ms(20);
    }

}


void close_door() {
    gpio_bit_reset(GPIOB, GPIO_PIN_9);
    for (int i = 0;i < 25;i++) {
        gpio_bit_set(GPIOB, GPIO_PIN_9);
        delay_100us(25);
        gpio_bit_reset(GPIOB, GPIO_PIN_9);
        delay_1ms(20);
    }
}


