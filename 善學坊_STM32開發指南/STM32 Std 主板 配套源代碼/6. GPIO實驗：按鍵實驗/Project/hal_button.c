#include "hal_button.h"

#include "hal_system.h"

#include "stm32f0xx_gpio.h"

static void (*halButtonOnClick)(void) = 0;

void halButtonInit(void (*onClick)(void))
{
    halButtonOnClick = onClick;

    GPIO_InitTypeDef buttonGPIO;

    buttonGPIO.GPIO_Mode = GPIO_Mode_IN;
    buttonGPIO.GPIO_PuPd = GPIO_PuPd_UP,
    buttonGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    buttonGPIO.GPIO_Pin = HAL_BUTTON_PIN;

    RCC_AHBPeriphClockCmd(HAL_BUTTON_CLOCK, ENABLE);

    GPIO_Init(HAL_BUTTON_PORT, &buttonGPIO);
}

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
