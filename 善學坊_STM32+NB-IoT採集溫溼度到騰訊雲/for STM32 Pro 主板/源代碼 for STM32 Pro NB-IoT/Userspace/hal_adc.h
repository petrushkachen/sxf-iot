#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__

/*
 *��ʼ��ADC
 */
void halAdcInit(void);

/*
 *��ȡADCֵ
 *
 *@return ADCֵ
 */
unsigned int halAdcRead(void);

#endif /* __HAL_ADC_H__ */
