#ifndef __SVC_MSG_H__
#define __SVC_MSG_H__

#include <stdint.h>

/* ���ݽ��ջ�������С */
#define SVC_MSG_BUF_MAX     128

/*
* ��Ϣͨ�ŷ����ʼ��
* Ĭ��ʹ�ô���ͨ��
*/
void svcMsgInit(void);

/*
* ��ȡ���յ�������
* @param buf ��ȡ�����ݵĴ洢��ַ
* @param len ����ȡ���ݵĳ���
*
* @return 
*/
uint16_t svcMsgRead(uint8_t *buf, uint16_t len);

/*
* ������Ϣ
* @param data ��������Ϣ�Ĵ洢��ַ
* @param len ��������Ϣ�Ĵ�С
*/
int svcMsgWrite(const uint8_t *data, uint8_t len);

/*
* �����ַ���
* @param string �����͵��ַ���
*/
int svcMsgWriteString(const char *str);

#endif /* __SVC_MSG_H__ */
