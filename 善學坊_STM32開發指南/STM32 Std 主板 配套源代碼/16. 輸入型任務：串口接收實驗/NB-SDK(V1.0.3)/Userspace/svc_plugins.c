#include "svc_plugins.h"

#include "hal_uart.h"
#include "hal_led.h"
#include "hal_oled12864.h"

void svcPluginsInit()
{
}

void svcPluginsToggleLed()
{
    halLedToggle();
}

void svcPluginsLcdWrite(const uint8_t *line1,
                        const uint8_t *line2,
                        const uint8_t *line3,
                        const uint8_t *line4)
{
    halOLED12864ClearScreen();

    halOLED12864ShowX16(0, 0, line1);
    halOLED12864ShowX16(1, 0, line2);
    halOLED12864ShowX16(2, 0, line3);
    halOLED12864ShowX16(3, 0, line4);
}

void svcPluginsSetUartCallback(void (*callback)(uint8_t byte))
{
    halUartSetIRQCallback(callback);
}
