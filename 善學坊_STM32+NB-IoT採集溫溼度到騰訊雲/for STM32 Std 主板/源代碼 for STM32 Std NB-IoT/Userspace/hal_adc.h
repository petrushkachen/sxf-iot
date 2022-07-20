#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__

/*
 *初始化ADC
 */
void halAdcInit(void);

/*
 *读取ADC值
 *
 *@return ADC值
 */
unsigned int halAdcRead(void);

#endif /* __HAL_ADC_H__ */
