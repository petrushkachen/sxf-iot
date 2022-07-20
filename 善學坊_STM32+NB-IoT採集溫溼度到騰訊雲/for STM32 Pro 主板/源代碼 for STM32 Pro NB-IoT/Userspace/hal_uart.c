#include "hal_uart.h"
#include "stm32f0xx_usart.h"

//接收串口数据的回调函数
static void (*halUartOnIRQ)(unsigned char byte) = 0;

static void halUartGpioInit(void);
static void halUartParamInit(unsigned long baudrate);
static void halUartIRQInit(void);

/*
 * 串口通信初始化
 *
 * @param baudrate - 串口通信波特率
 */
void halUartInit(unsigned long baudrate)
{
    halUartGpioInit();

    halUartParamInit(baudrate);

    halUartIRQInit();
}

/*
 * 注册接收串口数据的回调函数
 *
 * @param onIRQ - 回调函数，接收到串口数据时自动调用此函数
 */
void halUartSetIRQCallback(void (*onIRQ)(unsigned char byte))
{
    halUartOnIRQ = onIRQ;
}

/*
 * 向串口发送信息
 *
 * @param buf - 待发送的信息的存储地址
 * @param len - 待发送的信息的数据长度
 */
void halUartWrite(const unsigned char *buf, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++) {
        USART_SendData(USART1, buf[i]);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

/*
 * 初始化串口通信相关的GPIO
 */
void halUartGpioInit()
{
	  //配置结构体
    GPIO_InitTypeDef uart1Tx;
    GPIO_InitTypeDef uart1Rx;

    /* TX */
    uart1Tx.GPIO_Pin = GPIO_Pin_9,//PA9作为TX
    uart1Tx.GPIO_Speed = GPIO_Speed_10MHz,//通信频率
    uart1Tx.GPIO_Mode = GPIO_Mode_AF,
    uart1Tx.GPIO_PuPd = GPIO_PuPd_NOPULL,

    /* RX */
    uart1Rx.GPIO_Pin = GPIO_Pin_10,//PA10作为RX
    uart1Rx.GPIO_Speed = GPIO_Speed_10MHz,//通信频率
    uart1Rx.GPIO_Mode = GPIO_Mode_AF,
    uart1Rx.GPIO_PuPd = GPIO_PuPd_NOPULL,

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

    GPIO_Init(GPIOA, &uart1Tx);
    GPIO_Init(GPIOA, &uart1Rx);
}

/*
 * 初始化串口通信配置
 * @param baudrate - 串口通信波特率
 */
void halUartParamInit(unsigned long baudrate)
{
    USART_InitTypeDef uartConfig;

    uartConfig.USART_BaudRate = baudrate;
    uartConfig.USART_WordLength = USART_WordLength_8b;
    uartConfig.USART_Parity = USART_Parity_No;
    uartConfig.USART_StopBits = USART_StopBits_1;
    uartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uartConfig.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    USART_Init(USART1, &uartConfig);
    USART_Cmd(USART1, ENABLE);
}

/* 
 * 初始化串口通信的中断请求
 */
void halUartIRQInit()
{
    NVIC_InitTypeDef uartNVIC;

    uartNVIC.NVIC_IRQChannel = USART1_IRQn;
    uartNVIC.NVIC_IRQChannelPriority = 0;
    uartNVIC.NVIC_IRQChannelCmd = ENABLE;

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	  USART_ITConfig(USART1, USART_IT_TC, ENABLE);

    NVIC_Init(&uartNVIC);
}

/*
* 串口通信中断处理函数。当串口接收到数据时，便会自动产生中断并执行此函数
*/
void USART1_IRQHandler(void)
{
	unsigned char byte = 0;

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        byte = USART_ReceiveData(USART1); // Auto to clear RXNE flag when read!

        if (halUartOnIRQ != 0) halUartOnIRQ(byte);
    }
	else USART_ClearFlag(USART1,USART_FLAG_TC);
}
