#include "svc_log.h"

#include "hal_oled12864.h"

#include <string.h>

/*
* ��־��ӡ�����ʼ��
*/
void svcLogInit()
{

}

/*
* ��ӡ��־��Ĭ����OLED��Ļ�д�ӡ
*
* @param clean �Ƿ������Ļ�е����ݣ�0��ʾ����գ�1��ʾ���
* @param line1 �ڵ�1������ʾ���ַ�������ֵΪ0������ʾ
* @param line2 �ڵ�2������ʾ���ַ�������ֵΪ0������ʾ
* @param line3 �ڵ�3������ʾ���ַ�������ֵΪ0������ʾ
* @param line4 �ڵ�4������ʾ���ַ�������ֵΪ0������ʾ
*/
void svcLogWriteLcd(int clean, 
                    const uint8_t *line1,
                    const uint8_t *line2,
                    const uint8_t *line3,
                    const uint8_t *line4)
{
    if (clean) halOLED12864ClearScreen();

    if (line1) halOLED12864ShowX16(0, 0, line1);
    if (line2) halOLED12864ShowX16(1, 0, line2);
    if (line3) halOLED12864ShowX16(2, 0, line3);
    if (line4) halOLED12864ShowX16(3, 0, line4);
}