#include "hal_lcd_spi.h"

#include "hal_spi.h"

#include "stm32f0xx_gpio.h"

static void halLcdSpiTxByte(unsigned char b);

void halLcdSpiInit(void)
{
#ifdef STM32F030x8
    /* DC: PA11 */
    GPIO_InitTypeDef  lcdGPIO;

    lcdGPIO.GPIO_Mode = GPIO_Mode_OUT;
    lcdGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    lcdGPIO.GPIO_Pin = GPIO_Pin_11;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_Init(GPIOA, &lcdGPIO);
#else
    /* DC: PA2 */
    GPIO_InitTypeDef  lcdGPIO;

    lcdGPIO.GPIO_Mode = GPIO_Mode_OUT;
    lcdGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    lcdGPIO.GPIO_Pin = GPIO_Pin_2;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_Init(GPIOA, &lcdGPIO);
#endif
    /* Initial SPI */
    halSpiInit();
}

void halLcdSpiTxCmd(unsigned char cmd)
{
    halSpiEnable();

#ifdef STM32F030x8
    GPIO_ResetBits(GPIOA, GPIO_Pin_11);
#else
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
#endif

    halLcdSpiTxByte(cmd);

    halSpiDisable();
}

void halLcdSpiTxData(unsigned char dat)
{
    halSpiEnable();

#ifdef STM32F030x8
    GPIO_SetBits(GPIOA, GPIO_Pin_11);
#else
    GPIO_SetBits(GPIOA, GPIO_Pin_2);
#endif

    halLcdSpiTxByte(dat);

    halSpiDisable();
}

static void halLcdSpiTxByte(unsigned char b)
{
    SPI1_Transfer(b);
}
