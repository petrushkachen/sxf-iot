#ifndef __SVC_LOG_H__
#define __SVC_LOG_H__

#include <stdint.h>

void svcLogInit(void);

void svcLogWriteLcd(int clean,
                    const uint8_t *line1,
                    const uint8_t *line2,
                    const uint8_t *line3,
                    const uint8_t *line4);

#endif /* __SVC_LOG_H__ */
