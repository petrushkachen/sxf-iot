#include "hal_led.h"

#include "stm32f0xx_gpio.h"

void halLedInit()
{
    GPIO_InitTypeDef  ledGPIO;

    ledGPIO.GPIO_Mode = GPIO_Mode_OUT;
    ledGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    ledGPIO.GPIO_Pin = HAL_LED_PIN;

    RCC_AHBPeriphClockCmd(HAL_LED_CLOCK, ENABLE);

    GPIO_Init(HAL_LED_PORT, &ledGPIO);
}

void halLedSetOn()
{
    GPIO_SetBits(HAL_LED_PORT, HAL_LED_PIN);
}

void halLedSetOff()
{
    GPIO_ResetBits(HAL_LED_PORT, HAL_LED_PIN);
}

void halLedToggle()
{
    uint8_t level;

    level = GPIO_ReadInputDataBit(HAL_LED_PORT, HAL_LED_PIN);

    if (level == 0) GPIO_SetBits(HAL_LED_PORT, HAL_LED_PIN);
    else GPIO_ResetBits(HAL_LED_PORT, HAL_LED_PIN);
}
