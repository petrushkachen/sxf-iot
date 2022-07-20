#include "task_input.h"

#include "svc_button.h"
#include "svc_log.h"
#include "svc_task.h"

static void taskInputRunner(uint8_t, void *);

void taskInputInit()
{
    svcTaskAdd(400, 1, taskInputRunner, 0);
}

void taskInputRunner(uint8_t id, void *args)
{
    int times = svcButtonClickTimes();

    svcButtonClickTimesClear();

    if (times == 1) svcLogWrite((uint8_t *)"TASK[INPUT] single click\n");
    else if (times == 2) svcLogWrite((uint8_t *)"TASK[INPUT] double click\n");
}
