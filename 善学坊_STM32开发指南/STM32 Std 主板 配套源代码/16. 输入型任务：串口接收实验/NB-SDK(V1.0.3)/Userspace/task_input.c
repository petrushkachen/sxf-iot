#include "task_input.h"

#include "svc_plugins.h"
#include "svc_button.h"
#include "svc_log.h"
#include "svc_task.h"

static uint8_t taskInputMsg[128];
static uint8_t taskInputIndex = 0;

static void taskInputOnUart(uint8_t byte);

static void taskInputRunner(uint8_t, void *);
static void taskInputOnMsgRunner(uint8_t, void *);

void taskInputInit()
{
    svcPluginsSetUartCallback(taskInputOnUart);

    svcTaskAdd(400, 1, taskInputRunner, 0);

    svcTaskAdd(60, 1, taskInputOnMsgRunner, 0);
}

void taskInputOnUart(uint8_t byte)
{
    if (taskInputIndex >= sizeof(taskInputMsg)) return;

    taskInputMsg[taskInputIndex++] = byte;
}

void taskInputRunner(uint8_t id, void *args)
{
    int times = svcButtonClickTimes();

    svcButtonClickTimesClear();

    if (times == 1) svcLogWrite((uint8_t *)"TASK[INPUT] single click\n");
    else if (times == 2) svcLogWrite((uint8_t *)"TASK[INPUT] double click\n");
}

static void taskInputOnMsgRunner(uint8_t id, void *args)
{
    uint8_t buf[sizeof(taskInputMsg)];

    if (taskInputIndex == 0) return;

    for (uint8_t i = 0; i < taskInputIndex; i++) buf[i] = taskInputMsg[i];

    taskInputIndex = 0;

    svcLogWrite(buf);
}
