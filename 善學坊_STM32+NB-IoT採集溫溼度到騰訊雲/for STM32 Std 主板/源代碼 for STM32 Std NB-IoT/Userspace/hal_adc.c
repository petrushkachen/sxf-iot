#include "hal_adc.h"

#include "stm32f0xx_adc.h"

/*
* ADC初始化
*/
void halAdcInit()
{
    GPIO_InitTypeDef gpioCfg;
    ADC_InitTypeDef adcCfg;

    /* PA0 */
    gpioCfg.GPIO_Pin  = GPIO_Pin_1;
    gpioCfg.GPIO_Mode = GPIO_Mode_AN;
    gpioCfg.GPIO_PuPd = GPIO_PuPd_NOPULL;

    ADC_StructInit(&adcCfg);
    adcCfg.ADC_Resolution = ADC_Resolution_8b;
    adcCfg.ADC_ContinuousConvMode = DISABLE;
    adcCfg.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    adcCfg.ADC_DataAlign = ADC_DataAlign_Right;
    adcCfg.ADC_ScanDirection = ADC_ScanDirection_Backward;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    RCC_ADCCLKConfig(RCC_ADCCLK_PCLK_Div4);

    ADC_DeInit(ADC1);

    GPIO_Init(GPIOA, &gpioCfg);

    ADC_Init(ADC1, &adcCfg);

    /* Convert the ADC1 Vref  with 55.5 Cycles as sampling time */
    ADC_ChannelConfig(ADC1, ADC_Channel_1, ADC_SampleTime_55_5Cycles);

    ADC_GetCalibrationFactor(ADC1);
    ADC_DMACmd(ADC1, ENABLE);

    ADC_Cmd(ADC1, ENABLE);

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADEN));

    ADC_StartOfConversion(ADC1);
}

/*
 *读取ADC值
 *
 *@return ADC值
 */
unsigned int halAdcRead()
{
    ADC_StartOfConversion(ADC1);

    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);

    return ADC_GetConversionValue(ADC1);
}
