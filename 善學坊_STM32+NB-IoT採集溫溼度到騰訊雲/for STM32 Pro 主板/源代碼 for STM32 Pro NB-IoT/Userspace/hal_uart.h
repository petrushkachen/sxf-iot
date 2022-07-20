#ifndef __HAL_UART_H__
#define __HAL_UART_H__

/*
* 串口初始化
* @param baudrate 波特率
*/
void halUartInit(unsigned long baudrate);

/*
 * 注册接收串口数据的回调函数
 *
 * @param onIRQ - 回调函数，接收到串口数据时自动调用此函数
 */
void halUartSetIRQCallback(void (*onIRQ)(unsigned char byte));

/*
 * 向串口发送信息
 *
 * @param buf - 待发送的信息的存储地址
 * @param len - 待发送的信息的数据长度
 */
void halUartWrite(const unsigned char *buf, unsigned int len);

#endif /* #ifndef __HAL_UART_H__ */
