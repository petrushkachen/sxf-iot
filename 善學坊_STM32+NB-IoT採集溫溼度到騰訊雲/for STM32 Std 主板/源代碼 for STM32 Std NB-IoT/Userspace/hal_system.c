#include "hal_system.h"

#include "stm32f0xx_syscfg.h"

/*
 * 系统初始化函数，这里暂时仅初始化SysTick
 */
void halSystemInit()
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

/*
 * 系统延时
 * 
 * @param   time - 延时时间，以微秒（us）为单位
 */
void halSystemDelayUs(unsigned long time)
{
    uint32_t value;

    SysTick->LOAD = time * (SystemCoreClock / 8000000);

    SysTick->VAL = 0x00;

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    do { value = SysTick->CTRL; } while ((value & 0x01) && !(value & (1<<16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0x00;
}
