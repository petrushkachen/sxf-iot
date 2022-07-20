#ifndef HAL_LCD_SPI_H
#define HAL_LCD_SPI_H

void halLcdSpiInit(void);

void halLcdSpiTxCmd(unsigned char cmd);
void halLcdSpiTxData(unsigned char dat);

#endif /* #ifndef HAL_LCD_SPI_H */
