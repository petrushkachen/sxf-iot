#include "hal_timer.h"

#include "stm32f0xx_tim.h"

static void (*halTimerOnIRQ)(void) = 0;

void halTimerInit(unsigned int period, void (*onTimerIRQ)(void))
{
    TIM_TimeBaseInitTypeDef timer3;

    NVIC_InitTypeDef timer3NVIC;

    /* Callback on interrupt! */
    halTimerOnIRQ = onTimerIRQ;

    /*
     *  ((TIM_Period + 1) / Clock)*(TIM_Prescaler + 1) = N ms / 1000
     *
     *  So, when TIM_Prescaler is 47999, ((TIM_Period + 1) / 48MHz) * 48000 = N ms / 1000
     *
     *  TIM_Period + 1 = (N ms / 1000) / 48000 * 48MHz = (N ms * 48000000Hz) / (1000 * 48000)
     *
     *  TIM_Prescaler = N ms - 1
     *
     *  Another solution:
     *    Clock is 48MHz, 
     *    when TIM_Prescaler is 47999, number of pulses generated in 1 second: 48000000Hz / (47999 + 1) = 1000
     *    So, 10 pulses can be generated in 1 millisecond.
     */
    timer3.TIM_Period = (period > 1) ? (period - 1) : 1;
	timer3.TIM_Prescaler = 47999;
	timer3.TIM_ClockDivision = TIM_CKD_DIV1;
	timer3.TIM_CounterMode = TIM_CounterMode_Up;

    /* TIM3 NVIC */
    timer3NVIC.NVIC_IRQChannel = TIM3_IRQn;
    timer3NVIC.NVIC_IRQChannelPriority = 1;
    timer3NVIC.NVIC_IRQChannelCmd = ENABLE;

    /* Enable TIM3 clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* Initial TIM3 */
	TIM_TimeBaseInit(TIM3, &timer3);

    /* Enable IRQ */
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

    /* Initial TIM3 NVIC */
    NVIC_Init(&timer3NVIC);
}

void halTimerStart()
{
    TIM_Cmd(TIM3, ENABLE);
}

void halTimerStop()
{
    TIM_Cmd(TIM3, DISABLE);
}

/*
 * TIM3 interrupt handler.
 */
void TIM3_IRQHandler()
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET && halTimerOnIRQ != 0) halTimerOnIRQ();

    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
