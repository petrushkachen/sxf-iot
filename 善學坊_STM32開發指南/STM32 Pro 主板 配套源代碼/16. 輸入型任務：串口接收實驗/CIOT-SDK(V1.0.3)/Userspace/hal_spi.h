#ifndef __HAL_SPI_H__
#define __HAL_SPI_H__

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

void halSpiInit(void);

void halSpiEnable(void);
void halSpiDisable(void);
uint8_t SPI1_Transfer(uint8_t data);
int halSpiTransfer(uint8_t byte, uint8_t *result);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_SPI_H__ */
