#include "init.h"

extern uint32_t disable_mcycle_minstret();

void s_init() {
    SystemInit();
    eclic_init(ECLIC_NUM_INTERRUPTS);
    eclic_mode_enable();
    disable_mcycle_minstret();
}

void rcu_init() {
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);

    //rcu_periph_clock_enable(RCU_TIMER0);
    rcu_periph_clock_enable(RCU_USART0);

    rcu_periph_clock_enable(RCU_AF);
}

void pin_init() {
    //lcd
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6);
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
    
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_14);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_15);

    //motor
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_bit_reset(GPIOB, GPIO_PIN_9);


    // GPIO_OCTL(GPIOA) = 0;
    // GPIO_OCTL(GPIOB) = 0;
    //usart
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);




}

void usart_init() {
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 57600U);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);

    while (RESET == usart_flag_get(USART0, USART_FLAG_TC));
    usart_interrupt_enable(USART0, USART_INT_RBNE);
}

void TIMER_init() {
    timer_parameter_struct timer_initpara;


    timer_deinit(TIMER0);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER0 configuration */
    timer_initpara.prescaler = 10799; // 10khz 10000
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 9999; //10000/10000 = 1s 
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER0, &timer_initpara);


    
    /* TIMER0 channel control update interrupt enable */
    timer_interrupt_enable(TIMER0, TIMER_INT_UP);

    /* TIMER0 counter enable */
    timer_enable(TIMER0);
}





void interrupt_init() {
    eclic_global_interrupt_enable();
    eclic_priority_group_set(ECLIC_PRIGROUP_LEVEL3_PRIO1);
    eclic_irq_enable(USART0_IRQn, 1, 0);
    
    // eclic_set_nlbits(ECLIC_GROUP_LEVEL3_PRIO1);
    // eclic_irq_enable(TIMER0_UP_IRQn, 6, 1);
}


void init() {
    s_init();
    rcu_init();
    interrupt_init();
    pin_init();
    //TIMER_init();
    usart_init();
    //lcd_init();
}








