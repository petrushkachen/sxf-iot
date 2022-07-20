#include "svc_task.h"

/* 标记：标记当前结构体是否存放了任务*/
#define SVC_TASK_OCCUPIED   (1 << 7)

/* 标记：任务是否需要反复执行 */
#define SVC_TASK_REPEAT     (1 << 6)

/* 任务与任务池定义 */
struct {
    uint8_t flag;//标记

    void *args;//任务参数
    void (*callback)(uint8_t, void *);//本任务的回调函数

    uint16_t interval;//如果重复执行，重复执行的时间间隔（ms）
    uint16_t timeout;//多少毫秒（ms）后到期执行此任务
} svcTasks[SVC_TASK_MAX];

/* 
* 任务管理服务初始化
*/
void svcTaskInit()
{
    uint8_t i;

    for (i = 0; i < SVC_TASK_MAX; i++){
			svcTasks[i].flag = 0;
		}
}

/* 
* 新增任务
* 
* @param interval - 多少毫秒（ms）后到期执行此任务
* @param repeat - 是否重复执行此Task：1表示重复执行，0表示不重复
* @callback - 回调函数，到期后自动执行此函数
* @args - 传给回调函数的参数

* @Return: 
* 0xFF : 错误
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
 *删除指定的任务
 *@param tid - 待删除的Task的ID
 */
void svcTaskRemove(uint8_t tid)
{
    if (tid < SVC_TASK_MAX){
			 svcTasks[tid].flag = 0;
		}
}

/*
 *查看有没有需要执行的任务，如有则执行
 *@param tick - 任务等待时间减少值
 */
void svcTaskPoll(uint16_t tick)
{
    uint8_t i;

    for (i = 0; i < SVC_TASK_MAX; i++) {
        if ((svcTasks[i].flag & SVC_TASK_OCCUPIED) == 0){
					continue;
				}

        if (svcTasks[i].timeout > tick) {//如果未到期执行
					svcTasks[i].timeout -= tick;//减少任务等待时间
					continue; 
				}
				else{//如果到期执行

					//执行任务
					svcTasks[i].callback(i, svcTasks[i].args);

					if ((svcTasks[i].flag & SVC_TASK_REPEAT) == 0) {//如果不需要重复执行任务
						svcTasks[i].flag = 0; 
						continue; 
					}
					else{//如果需要重复执行任务
						svcTasks[i].timeout = svcTasks[i].interval;
					}
			  }
    }
}
