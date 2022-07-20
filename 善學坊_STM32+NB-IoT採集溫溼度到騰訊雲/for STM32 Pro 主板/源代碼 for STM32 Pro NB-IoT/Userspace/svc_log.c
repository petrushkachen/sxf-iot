#include "svc_log.h"

#include "hal_oled12864.h"

#include <string.h>

/*
* 日志打印服务初始化
*/
void svcLogInit()
{

}

/*
* 打印日志，默认在OLED屏幕中打印
*
* @param clean 是否清空屏幕中的内容，0表示不清空，1表示清空
* @param line1 在第1行中显示该字符串，如值为0，则不显示
* @param line2 在第2行中显示该字符串，如值为0，则不显示
* @param line3 在第3行中显示该字符串，如值为0，则不显示
* @param line4 在第4行中显示该字符串，如值为0，则不显示
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