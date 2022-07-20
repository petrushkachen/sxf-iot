#include "hal_button.h"

#include "hal_system.h"

#include "stm32f0xx_gpio.h"

static void (*halButtonOnClick)(void) = 0;

void halButtonInit(void (*onClick)(void))
{
    halButtonOnClick = onClick;

    GPIO_InitTypeDef buttonGPIO;

    /* Use interrupt handler */
#ifdef HAL_BUTTON_USE_IRQ
    EXTI_InitTypeDef buttonEXTI;
    NVIC_InitTypeDef buttonNVIC;
#endif

    buttonGPIO.GPIO_Mode = GPIO_Mode_IN;
    buttonGPIO.GPIO_PuPd = GPIO_PuPd_UP,
    buttonGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    buttonGPIO.GPIO_Pin = HAL_BUTTON_PIN;

    RCC_AHBPeriphClockCmd(HAL_BUTTON_CLOCK, ENABLE);

    GPIO_Init(HAL_BUTTON_PORT, &buttonGPIO);

    /* Use interrupt handler */
#ifdef HAL_BUTTON_USE_IRQ
    buttonEXTI.EXTI_Line = EXTI_Line0;
    buttonEXTI.EXTI_Mode = EXTI_Mode_Interrupt;
    buttonEXTI.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    buttonEXTI.EXTI_LineCmd = ENABLE;

    buttonNVIC.NVIC_IRQChannel = EXTI0_1_IRQn,
    buttonNVIC.NVIC_IRQChannelPriority = 0,
    buttonNVIC.NVIC_IRQChannelCmd = ENABLE,

    EXTI_Init(&buttonEXTI);
    NVIC_Init(&buttonNVIC);

    SYSCFG_EXTILineConfig(HAL_BUTTON_EXTI_PORT, HAL_BUTTON_EXTI_PIN);
#endif /* #ifndef HAL_BUTTON_USE_IRQ */
}

/* Without use interrupt handler*/
#ifndef HAL_BUTTON_USE_IRQ

void halButtonPoll(void)
{
    /* Pressed */
    if (GPIO_ReadInputDataBit(HAL_BUTTON_PORT, HAL_BUTTON_PIN) != HAL_BUTTON_TRIGGER_LEVEL) return;

    /* Debounce */
    halSystemDelayUs(1000 * 10);

    /* Valid or not */
    if (GPIO_ReadInputDataBit(HAL_BUTTON_PORT, HAL_BUTTON_PIN) != HAL_BUTTON_TRIGGER_LEVEL) return;

    /* Wait for release */
    while(GPIO_ReadInputDataBit(HAL_BUTTON_PORT, HAL_BUTTON_PIN) == HAL_BUTTON_TRIGGER_LEVEL) halSystemDelayUs(1000);

    /* Callback to userspace */
    if (halButtonOnClick != 0) halButtonOnClick();
}

/* Use interrupt handler */
#else

/* IRQ */
void EXTI0_1_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET && halButtonOnClick != 0) {
        /* Debounce */
        halSystemDelayUs(1000 * 10);

        if (GPIO_ReadInputDataBit(HAL_BUTTON_PORT, HAL_BUTTON_PIN) == HAL_BUTTON_TRIGGER_LEVEL) halButtonOnClick();
    }

	EXTI_ClearFlag(EXTI_Line0);
}

#endif /* #ifndef HAL_BUTTON_USE_IRQ */
