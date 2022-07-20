#ifndef __SVC_MSG_H__
#define __SVC_MSG_H__

#include <stdint.h>

/* 数据接收缓冲区大小 */
#define SVC_MSG_BUF_MAX     128

/*
* 消息通信服务初始化
* 默认使用串口通信
*/
void svcMsgInit(void);

/*
* 读取接收到的数据
* @param buf 读取到数据的存储地址
* @param len 待读取数据的长度
*
* @return 
*/
uint16_t svcMsgRead(uint8_t *buf, uint16_t len);

/*
* 发送消息
* @param data 待发送消息的存储地址
* @param len 待发送消息的大小
*/
int svcMsgWrite(const uint8_t *data, uint8_t len);

/*
* 发送字符串
* @param string 待发送的字符串
*/
int svcMsgWriteString(const char *str);

#endif /* __SVC_MSG_H__ */
