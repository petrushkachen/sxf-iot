#include "hal_lcd_spi.h"

#include "hal_spi.h"

#include "stm32f0xx_gpio.h"

static void halLcdSpiTxByte(unsigned char b);

void halLcdSpiInit(void)
{
    /* DC: PA2 */
    GPIO_InitTypeDef  lcdGPIO;

    lcdGPIO.GPIO_Mode = GPIO_Mode_OUT;
    lcdGPIO.GPIO_Speed = GPIO_Speed_2MHz;
    lcdGPIO.GPIO_Pin = GPIO_Pin_2;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_Init(GPIOA, &lcdGPIO);

    /* Initial SPI */
    halSpiInit();
}

void halLcdSpiTxCmd(unsigned char cmd)
{
    halSpiEnable();

    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    halLcdSpiTxByte(cmd);

    halSpiDisable();
}

void halLcdSpiTxData(unsigned char dat)
{
    halSpiEnable();

    GPIO_SetBits(GPIOA, GPIO_Pin_2);
    halLcdSpiTxByte(dat);

    halSpiDisable();
}

static void halLcdSpiTxByte(unsigned char b)
{
    SPI1_Transfer(b);
}
