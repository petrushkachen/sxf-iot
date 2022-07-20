#ifndef __SVC_TASK_H__
#define __SVC_TASK_H__

#include <stdint.h>

/* 最大任务数量 */
#define SVC_TASK_MAX      (10)

/* 
* 任务管理服务初始化
*/
void svcTaskInit();

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
uint8_t svcTaskAdd(uint16_t interval, uint8_t repeat, void (*callback)(uint8_t, void *), void *args);

/*
 *删除指定的任务
 *@param tid - 待删除的Task的ID
 */
void svcTaskRemove(uint8_t tid);

/*
 *查看有没有需要执行的任务，如有则执行
 *@param tick - tick
 */
void svcTaskPoll(uint16_t tick);

#endif /* __SVC_TASK_H__ */
