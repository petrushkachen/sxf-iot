#include "hal_spi.h"

#include "stm32f0xx_spi.h"

/* Enable */
#define HAL_SPI_ENABLE()                                  \
    do {                                                  \
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);                \
        while(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4)); \
    } while(0)

/* Disable */
#define HAL_SPI_DISABLE()   GPIO_SetBits(GPIOA, GPIO_Pin_4)

void halSpiEnable()
{
    HAL_SPI_ENABLE();
}

void halSpiDisable()
{
    HAL_SPI_DISABLE();
}

void halSpiInit()
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    GPIO_InitTypeDef spiGpioConfig = {
        .GPIO_Mode = GPIO_Mode_AF,
        .GPIO_OType = GPIO_OType_PP,
        .GPIO_PuPd  = GPIO_PuPd_DOWN,
        .GPIO_Speed = GPIO_Speed_10MHz,
        .GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7,  /* PA5: CLK, PA6: MISO, PA7: MOSI */
    };
    GPIO_Init(GPIOA, &spiGpioConfig);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);

    GPIO_InitTypeDef csnConfig = {
        .GPIO_Mode = GPIO_Mode_OUT,
        .GPIO_Speed = GPIO_Speed_10MHz,
        .GPIO_Pin = GPIO_Pin_4, /* PA4: CS */
    };
    GPIO_Init(GPIOA, &csnConfig);
    GPIO_SetBits(GPIOA, GPIO_Pin_4);

    SPI_InitTypeDef spiConfig = {
        .SPI_Direction = SPI_Direction_2Lines_FullDuplex,
        .SPI_Mode = SPI_Mode_Master,
        .SPI_DataSize = SPI_DataSize_8b,
        .SPI_CPOL = SPI_CPOL_High,
        .SPI_CPHA = SPI_CPHA_2Edge,
        .SPI_NSS = SPI_NSS_Soft,
        .SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16,
        .SPI_FirstBit = SPI_FirstBit_MSB,
        .SPI_CRCPolynomial = 7,
    };

    SPI_I2S_DeInit(SPI1);
    SPI_Init(SPI1, &spiConfig);
    SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
    SPI_Cmd(SPI1, ENABLE);
}

uint8_t SPI1_Transfer(uint8_t data)
{
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_SendData8(SPI1, data);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_ReceiveData8(SPI1);
}

int halSpiTransfer(uint8_t byte, uint8_t *result)
{
    uint8_t tmp;
    uint16_t timeout = 0;

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) if (++timeout > 1024) return -1;
    SPI_SendData8(SPI1, byte);

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) if (++timeout > 2048) return -1;
    tmp = SPI_ReceiveData8(SPI1);

    if (result != 0) *result = tmp;

    return 0;
}
