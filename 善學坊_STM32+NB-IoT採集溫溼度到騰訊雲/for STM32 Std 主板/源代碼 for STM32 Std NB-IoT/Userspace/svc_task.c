#include "svc_task.h"

/* ��ǣ���ǵ�ǰ�ṹ���Ƿ���������*/
#define SVC_TASK_OCCUPIED   (1 << 7)

/* ��ǣ������Ƿ���Ҫ����ִ�� */
#define SVC_TASK_REPEAT     (1 << 6)

/* ����������ض��� */
struct {
    uint8_t flag;//���

    void *args;//�������
    void (*callback)(uint8_t, void *);//������Ļص�����

    uint16_t interval;//����ظ�ִ�У��ظ�ִ�е�ʱ������ms��
    uint16_t timeout;//���ٺ��루ms������ִ�д�����
} svcTasks[SVC_TASK_MAX];

/* 
* �����������ʼ��
*/
void svcTaskInit()
{
    uint8_t i;

    for (i = 0; i < SVC_TASK_MAX; i++){
			svcTasks[i].flag = 0;
		}
}

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
uint8_t svcTaskAdd(uint16_t interval, uint8_t repeat, void (*callback)(uint8_t, void *), void *args)
{
    uint8_t i;

    for (i = 0; i < SVC_TASK_MAX; i++) {
        if (svcTasks[i].flag & SVC_TASK_OCCUPIED) continue;

        svcTasks[i].flag = 0;
        svcTasks[i].flag |= SVC_TASK_OCCUPIED;
        svcTasks[i].flag |= repeat ? SVC_TASK_REPEAT : 0;
        svcTasks[i].args = args;
        svcTasks[i].callback = callback;
        svcTasks[i].interval = interval;
        svcTasks[i].timeout = interval;

        return i;
    }

    return 0xFF;
}

/*
 *ɾ��ָ��������
 *@param tid - ��ɾ����Task��ID
 */
void svcTaskRemove(uint8_t tid)
{
    if (tid < SVC_TASK_MAX){
			 svcTasks[tid].flag = 0;
		}
}

/*
 *�鿴��û����Ҫִ�е�����������ִ��
 *@param tick - ����ȴ�ʱ�����ֵ
 */
void svcTaskPoll(uint16_t tick)
{
    uint8_t i;

    for (i = 0; i < SVC_TASK_MAX; i++) {
        if ((svcTasks[i].flag & SVC_TASK_OCCUPIED) == 0){
					continue;
				}

        if (svcTasks[i].timeout > tick) {//���δ����ִ��
					svcTasks[i].timeout -= tick;//��������ȴ�ʱ��
					continue; 
				}
				else{//�������ִ��

					//ִ������
					svcTasks[i].callback(i, svcTasks[i].args);

					if ((svcTasks[i].flag & SVC_TASK_REPEAT) == 0) {//�������Ҫ�ظ�ִ������
						svcTasks[i].flag = 0; 
						continue; 
					}
					else{//�����Ҫ�ظ�ִ������
						svcTasks[i].timeout = svcTasks[i].interval;
					}
			  }
    }
}
