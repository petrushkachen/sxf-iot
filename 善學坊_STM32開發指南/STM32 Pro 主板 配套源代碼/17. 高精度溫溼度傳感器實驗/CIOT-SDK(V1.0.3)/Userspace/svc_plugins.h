#ifndef __SVC_PLUGINS_H__
#define __SVC_PLUGINS_H__

#include <stdint.h>

void svcPluginsInit(void);

void svcPluginsToggleLed(void);

void svcPluginsLcdWrite(const uint8_t *line1,
                        const uint8_t *line2,
                        const uint8_t *line3,
                        const uint8_t *line4);

void svcPluginsSetUartCallback(void (*callback)(uint8_t byte));

#endif /* #ifndef __SVC_PLUGINS_H__ */
