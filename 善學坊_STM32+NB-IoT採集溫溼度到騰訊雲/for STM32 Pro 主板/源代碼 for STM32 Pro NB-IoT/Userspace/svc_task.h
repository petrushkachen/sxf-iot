#ifndef __SVC_TASK_H__
#define __SVC_TASK_H__

#include <stdint.h>

/* ����������� */
#define SVC_TASK_MAX      (10)

/* 
* �����������ʼ��
*/
void svcTaskInit();

/* 
* ��������
* 
* @param interval - ���ٺ��루ms������ִ�д�����
* @param repeat - �Ƿ��ظ�ִ�д�Task��1��ʾ�ظ�ִ�У�0��ʾ���ظ�
* @callback - �ص����������ں��Զ�ִ�д˺���
* @args - �����ص������Ĳ���

* @Return: 
* 0xFF : ����
* 0 ~ (SVC_TASK_MAX - 1) : Task ID
*/ 
uint8_t svcTaskAdd(uint16_t interval, uint8_t repeat, void (*callback)(uint8_t, void *), void *args);

/*
 *ɾ��ָ��������
 *@param tid - ��ɾ����Task��ID
 */
void svcTaskRemove(uint8_t tid);

/*
 *�鿴��û����Ҫִ�е�����������ִ��
 *@param tick - tick
 */
void svcTaskPoll(uint16_t tick);

#endif /* __SVC_TASK_H__ */
