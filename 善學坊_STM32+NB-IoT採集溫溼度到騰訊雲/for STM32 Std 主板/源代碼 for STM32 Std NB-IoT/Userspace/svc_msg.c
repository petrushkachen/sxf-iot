#include "svc_msg.h"

#include "hal_uart.h"

#include <string.h>

/* ���ݽ��ջ����� */
uint8_t svcMsgBuf[SVC_MSG_BUF_MAX];

/*��ǰ�������Ѵ�ŵ��ֽ�����*/
volatile uint16_t svcMsgCounter = 0;

static void svcMsgOnUart(unsigned char byte);

/*
* ��Ϣͨ�ŷ����ʼ��
* Ĭ��ʹ�ô���ͨ��
*/
void svcMsgInit()
{
	  //�趨���յ�����ʱ�ص�����
    halUartSetIRQCallback(svcMsgOnUart);
}

/*
* ��ȡ���յ�������
* @param buf ��ȡ�����ݵĴ洢��ַ
* @param len ����ȡ���ݵĳ���
*
* @return 
*/
uint16_t svcMsgRead(uint8_t *buf, uint16_t len)
{
	  //ʵ�ʶ�ȡ�����ݳ���
    uint16_t size;

	  //�����������û�����ݣ���ô����������
    if (svcMsgCounter == 0){
			return 0;
		}

		//����ʵ�ʶ�ȡ�����ݳ���
    if (len > svcMsgCounter){
			size = svcMsgCounter;
		}
    else{
			size = len;
		}
    
		//�ӻ�������ȡ������
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
* ������Ϣ
* @param data ��������Ϣ�Ĵ洢��ַ
* @param len ��������Ϣ�Ĵ�С
*/
int svcMsgWrite(const uint8_t *data, uint8_t len)
{
    halUartWrite(data, len);

    return 0;
}

/*
* �����ַ���
* @param string �����͵��ַ���
*/
int svcMsgWriteString(const char *string)
{
    halUartWrite((uint8_t *)string, strlen(string));

    return 0;
}

/*
* ���ݽ��ջص�����
* @param byte ���յ���1���ֽ�����
*/
void svcMsgOnUart(unsigned char byte)
{
    if (svcMsgCounter < SVC_MSG_BUF_MAX){//������ݽ��ջ�����δ��
			//����1���ֽ�
			svcMsgBuf[svcMsgCounter++] = byte;
		}
}
