#ifndef __SVC_TASK_H__
#define __SVC_TASK_H__

#include <stdint.h>

/* Maximum number of tasks. */
#define SVC_TASK_MAX      (10)

void svcTaskInit();

/*
 *    Add task.
 *
 *    @param interval - how many milliseconds
 *    @param repeat - 0/1
 *    @callback - callback function
 *    @args - the arguments to the callback function
 
 *    @Return:
 *              0xFF : Error
 *              0 ~ (SVC_TASK_MAX - 1) : task id
 */
uint8_t svcTaskAdd(uint16_t interval, uint8_t repeat, void (*callback)(uint8_t, void *), void *args);

void svcTaskRemove(uint8_t tid);

void svcTaskPoll(uint16_t tick);

#endif /* __SVC_TASK_H__ */
