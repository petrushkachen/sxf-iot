#ifndef __SVC_PLUGINS_H__
#define __SVC_PLUGINS_H__

#include <stdint.h>

void svcPluginsInit(void);

void svcPluginsToggleLed(void);

void svcPluginsLcdWrite(const uint8_t *line1,
                        const uint8_t *line2,
                        const uint8_t *line3,
                        const uint8_t *line4);

#endif /* #ifndef __SVC_PLUGINS_H__ */
