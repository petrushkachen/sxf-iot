#include "hal_dht11.h"
#include "hal_system.h"

#include "stm32f0xx_gpio.h"

#include <stdint.h>

/* Boolean value. */
#define HAL_DHT11_FALSE                 0
#define HAL_DHT11_TRUE                  1

/* DHT11 Status Code. */
#define HAL_DHT11_SC_ERR                HAL_DHT11_FALSE
#define HAL_DHT11_SC_OK                 HAL_DHT11_TRUE
#define HAL_DHT11_SC_HUMI_OUTOFRANGE    0xF1
#define HAL_DHT11_SC_TEMP_OUTOFRANGE    0xF2
#define HAL_DHT11_SC_HT_OUTOFRANGE      0xF3

/* Delay Functions. */   
#define HAL_DHT11_DELAY_US(x)           halSystemDelayUs(x)
#define HAL_DHT11_DELAY_MS(x)           halSystemDelayUs(x * 1000)

/* Init clock. */
#define HAL_DHT11_PREINIT()             do{ RCC_AHBPeriphClockCmd(HAL_DHT11_CLOCK, ENABLE); }while(0)

/* Set DHT11 GPIO mode: Output. */
#define HAL_DHT11_IO_OUTPUT()           do { \
    GPIO_InitTypeDef dht11GPIO = {           \
        .GPIO_Mode = GPIO_Mode_OUT,          \
        .GPIO_Speed = GPIO_Speed_2MHz,       \
        .GPIO_Pin = HAL_DHT11_PIN,           \
    };                                       \
    GPIO_Init(HAL_DHT11_PORT, &dht11GPIO);   \
} while(0)

/* Set DHT11 GPIO mode: Input. */
#define HAL_DHT11_IO_INPUT()            do { \
    GPIO_InitTypeDef dht11GPIO = {           \
        .GPIO_Mode = GPIO_Mode_IN,           \
        .GPIO_Speed = GPIO_Speed_2MHz,       \
        .GPIO_Pin = HAL_DHT11_PIN,           \
        .GPIO_PuPd = GPIO_PuPd_DOWN          \
    };                                       \
    GPIO_Init(HAL_DHT11_PORT, &dht11GPIO);   \
} while(0)

/* Set DHT11 GPIO Level. */ 
#define HAL_DHT11_IO_SET(port, pin, s) do { \
  if(s) GPIO_SetBits(port, pin);            \
  else GPIO_ResetBits(port, pin);           \
} while(0)

#define HAL_DHT11_IO_SET_LO()           HAL_DHT11_IO_SET(HAL_DHT11_PORT, HAL_DHT11_PIN, 0)
#define HAL_DHT11_IO_SET_HI()           HAL_DHT11_IO_SET(HAL_DHT11_PORT, HAL_DHT11_PIN, 1)

/*  Get DHT11 GPIO Status. */
#define HAL_DHT11_IO_GET(port, pin)     GPIO_ReadInputDataBit(port, pin)
#define HAL_DHT11_IO()                  HAL_DHT11_IO_GET(HAL_DHT11_PORT, HAL_DHT11_PIN)

/* HT11 Measurement range detection. */ 
#define HAL_DHT11_TEMP_OK(t)            ((t) <= 50)
#define HAL_DHT11_HUMI_OK(h)            ((h) >= 20 && (h) <= 95)

static void halDHT11SetIdle(void);
static uint8_t halDHT11ReadByte(void);
static uint8_t halDHT11CheckData(uint8_t TempI, uint8_t HumiI);

void halDHT11Init(void)
{
    HAL_DHT11_PREINIT();

    halDHT11SetIdle();
}

halDHT11Data_t halDHT11GetData(void)
{
    uint8_t HumiI, HumiF, TempI, TempF, CheckSum;
    halDHT11Data_t dht11Dat = { .ok = HAL_DHT11_FALSE };

    /* >18ms, keeping gpio low-level */
    HAL_DHT11_IO_SET_LO();
    HAL_DHT11_DELAY_MS(30);

    HAL_DHT11_IO_SET_HI();

    /* Wait 20~40us then read ACK */
    HAL_DHT11_DELAY_US(32);
    HAL_DHT11_IO_INPUT();
    if (!HAL_DHT11_IO()) {
        uint16_t cnt = 1070; // ~1ms

        /* Wait for the end of ACK */
        while (!HAL_DHT11_IO() && cnt--);
        if(!cnt) goto Exit;

        /* ~80us, DHT11 GPIO will be set after ACK */
        cnt = 1070;  // ~1ms
        HAL_DHT11_DELAY_US(80);
        while (HAL_DHT11_IO() && cnt--);
        if(!cnt) goto Exit;

        /* Read data */
        HumiI = halDHT11ReadByte();
        HumiF = halDHT11ReadByte();
        TempI = halDHT11ReadByte();
        TempF = halDHT11ReadByte();
        CheckSum = halDHT11ReadByte();

        /* Checksum */
        if (CheckSum == (HumiI + HumiF + TempI + TempF) && CheckSum != 0) {
            dht11Dat.temp = TempI;
            dht11Dat.humi = HumiI;

            dht11Dat.ok = halDHT11CheckData(TempI, HumiI);
        }
    }

Exit:
    halDHT11SetIdle();
    return dht11Dat;
}

static void halDHT11SetIdle(void)
{
    HAL_DHT11_IO_OUTPUT();
    HAL_DHT11_IO_SET_HI();
}

static uint8_t halDHT11ReadByte(void)
{
    uint8_t dat = 0;

    for (uint8_t i = 0; i < 8; i++) {
        uint16_t cnt = 5350;  // ~5ms

        /* Busy */
        while (!HAL_DHT11_IO() && cnt--);
        if(!cnt) break;

        /* Read bit based on high-level duration:
         *      26~28us: 0
         *      >70us:   1
         */
        HAL_DHT11_DELAY_US(50);
        if (HAL_DHT11_IO()) {      
            dat <<= 1;
            dat |= 1;
        }
        else {
            dat <<= 1;
            continue;
        }

        /* Waiting end */
        cnt = 1070;   // ~1ms
        while(HAL_DHT11_IO() && cnt--);
        if(!cnt) break;
    }

    return dat;
}

static uint8_t halDHT11CheckData(uint8_t TempI, uint8_t HumiI)
{
    if (HAL_DHT11_HUMI_OK(HumiI)) {
        if(HAL_DHT11_TEMP_OK(TempI)) return HAL_DHT11_SC_OK;
        else return HAL_DHT11_SC_TEMP_OUTOFRANGE;
    }

    if (HAL_DHT11_TEMP_OK(TempI)) return HAL_DHT11_SC_HUMI_OUTOFRANGE;
    else return HAL_DHT11_SC_HT_OUTOFRANGE;
}
