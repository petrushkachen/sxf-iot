#include "hal_system.h"

#include "stm32f0xx_syscfg.h"

void halSystemInit()
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

void halSystemDelayUs(unsigned long n)
{
    uint32_t value;

    SysTick->LOAD = n * (SystemCoreClock / 8000000);

    SysTick->VAL = 0x00;

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    do { value = SysTick->CTRL; } while ((value & 0x01) && !(value & (1<<16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}
