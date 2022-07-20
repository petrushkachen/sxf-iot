#include "svc_msg.h"

#include "hal_uart.h"

#include <string.h>

/* 数据接收缓冲区 */
uint8_t svcMsgBuf[SVC_MSG_BUF_MAX];

/*当前缓冲区已存放的字节数量*/
volatile uint16_t svcMsgCounter = 0;

static void svcMsgOnUart(unsigned char byte);

/*
* 消息通信服务初始化
* 默认使用串口通信
*/
void svcMsgInit()
{
	  //设定接收到数据时回调函数
    halUartSetIRQCallback(svcMsgOnUart);
}

/*
* 读取接收到的数据
* @param buf 读取到数据的存储地址
* @param len 待读取数据的长度
*
* @return 
*/
uint16_t svcMsgRead(uint8_t *buf, uint16_t len)
{
	  //实际读取的数据长度
    uint16_t size;

	  //如果缓冲区中没有数据，那么结束本函数
    if (svcMsgCounter == 0){
			return 0;
		}

		//计算实际读取的数据长度
    if (len > svcMsgCounter){
			size = svcMsgCounter;
		}
    else{
			size = len;
		}
    
		//从缓冲区中取出数据
    memcpy(buf, svcMsgBuf, size);

     //svcMsgCounter = 0;
		
    if(svcMsgCounter>size){
        uint16_t i,j;
        for(i=0,j=size;j<svcMsgCounter;i++,j++){
            svcMsgBuf[i]=svcMsgBuf[j];
        }
    }
    
    svcMsgCounter=svcMsgCounter-size;

    return size;
}

/*
* 发送消息
* @param data 待发送消息的存储地址
* @param len 待发送消息的大小
*/
int svcMsgWrite(const uint8_t *data, uint8_t len)
{
    halUartWrite(data, len);

    return 0;
}

/*
* 发送字符串
* @param string 待发送的字符串
*/
int svcMsgWriteString(const char *string)
{
    halUartWrite((uint8_t *)string, strlen(string));

    return 0;
}

/*
* 数据接收回调函数
* @param byte 接收到的1个字节数据
*/
void svcMsgOnUart(unsigned char byte)
{
    if (svcMsgCounter < SVC_MSG_BUF_MAX){//如果数据接收缓冲区未满
			//接收1个字节
			svcMsgBuf[svcMsgCounter++] = byte;
		}
}
