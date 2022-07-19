#include "task_lcd.h"

#include "svc_task.h"
#include "svc_plugins.h"

#include <string.h>
#include <stdio.h>

static void taskLcdRunner(uint8_t, void *);

void taskLcdInit()
{
    svcTaskAdd(1000, 1, taskLcdRunner, 0);
}

void taskLcdRunner(uint8_t id, void *args)
{
    static int count = 0;

    char msg[16];

    sprintf(msg, "Count=%d", count++);

    svcPluginsLcdWrite((uint8_t *)"TASK[LCD]",
                       (uint8_t *)msg,
                       0,
                       0);
}
