#ifndef __HAL_UART_H__
#define __HAL_UART_H__

/*
* ���ڳ�ʼ��
* @param baudrate ������
*/
void halUartInit(unsigned long baudrate);

/*
 * ע����մ������ݵĻص�����
 *
 * @param onIRQ - �ص����������յ���������ʱ�Զ����ô˺���
 */
void halUartSetIRQCallback(void (*onIRQ)(unsigned char byte));

/*
 * �򴮿ڷ�����Ϣ
 *
 * @param buf - �����͵���Ϣ�Ĵ洢��ַ
 * @param len - �����͵���Ϣ�����ݳ���
 */
void halUartWrite(const unsigned char *buf, unsigned int len);

#endif /* #ifndef __HAL_UART_H__ */
