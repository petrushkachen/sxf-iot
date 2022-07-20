#ifndef __HAL_UART_H__
#define __HAL_UART_H__

void halUartInit(unsigned long baudrate);

void halUartSetIRQCallback(void (*onIRQ)(unsigned char byte));

void halUartWrite(const unsigned char *buf, unsigned int len);

#endif /* #ifndef __HAL_UART_H__ */
