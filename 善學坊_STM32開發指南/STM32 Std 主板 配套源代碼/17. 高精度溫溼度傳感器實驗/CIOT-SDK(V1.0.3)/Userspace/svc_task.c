#include "svc_task.h"

#define SVC_TASK_OCCUPIED   (1 << 7)
#define SVC_TASK_REPEAT     (1 << 6)

struct {
    uint8_t flag;

    void *args;
    void (*callback)(uint8_t, void *);

    uint16_t interval, timeout;
} svcTasks[SVC_TASK_MAX];

/* Init */
void svcTaskInit()
{
    uint8_t i;

    for (i = 0; i < SVC_TASK_MAX; i++) svcTasks[i].flag = 0;
}

/* Add */
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

/* Remove */
void svcTaskRemove(uint8_t tid)
{
    if (tid < SVC_TASK_MAX) svcTasks[tid].flag = 0;
}

/* Poll */
void svcTaskPoll(uint16_t tick)
{
    uint8_t i;

    for (i = 0; i < SVC_TASK_MAX; i++) {
        if ((svcTasks[i].flag & SVC_TASK_OCCUPIED) == 0) continue;

        if (svcTasks[i].timeout > tick) { svcTasks[i].timeout -= tick; continue; }

        svcTasks[i].callback(i, svcTasks[i].args);

        if ((svcTasks[i].flag & SVC_TASK_REPEAT) == 0) { svcTasks[i].flag = 0; continue; }

        svcTasks[i].timeout = svcTasks[i].interval;
    }
}
