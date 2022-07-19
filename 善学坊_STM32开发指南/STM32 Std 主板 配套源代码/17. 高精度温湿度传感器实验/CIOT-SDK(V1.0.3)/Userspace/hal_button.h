#ifndef __HAL_BUTTON_H__
#define __HAL_BUTTON_H__

#define HAL_BUTTON_PORT             GPIOA
#define HAL_BUTTON_PIN              GPIO_Pin_0
#define HAL_BUTTON_CLOCK            RCC_AHBPeriph_GPIOA
#define HAL_BUTTON_TRIGGER_LEVEL    1

#ifdef HAL_BUTTON_USE_IRQ
    #define HAL_BUTTON_EXTI_PORT    EXTI_PortSourceGPIOA
    #define HAL_BUTTON_EXTI_PIN     EXTI_PinSource0
#endif /* #ifndef HAL_BUTTON_USE_IRQ */

void halButtonInit(void (*onClick)(void));

void halButtonSetCallback(void (*onClick)(void));

/* Without use interrupt handler*/
#ifndef HAL_BUTTON_USE_IRQ

/*
 *  If interrupts are not enabled, we need to poll the buttons.
 */
void halButtonPoll(void);

#endif /* #ifndef HAL_BUTTON_USE_IRQ */


#endif /* #ifndef __HAL_BUTTON_H__ */
