#ifndef __HAL_LED_H__
#define __HAL_LED_H__

#define HAL_LED_PORT    GPIOB
#define HAL_LED_PIN     GPIO_Pin_1
#define HAL_LED_CLOCK   RCC_AHBPeriph_GPIOB

void halLedInit(void);

void halLedSetOn(void);
void halLedSetOff(void);
void halLedToggle(void);

#endif /* #ifndef __HAL_LED_H__ */
