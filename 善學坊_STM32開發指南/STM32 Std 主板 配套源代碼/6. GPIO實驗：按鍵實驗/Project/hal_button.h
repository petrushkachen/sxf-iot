#ifndef __HAL_BUTTON_H__
#define __HAL_BUTTON_H__

#define HAL_BUTTON_PORT             GPIOA
#define HAL_BUTTON_PIN              GPIO_Pin_0
#define HAL_BUTTON_CLOCK            RCC_AHBPeriph_GPIOA

#define HAL_BUTTON_TRIGGER_LEVEL    0

void halButtonInit(void (*onClick)(void));

void halButtonPoll(void);

#endif /* #ifndef __HAL_BUTTON_H__ */
