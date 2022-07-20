#include "task_led.h"

#include "svc_plugins.h"
#include "svc_task.h"

static void taskLedRunner(uint8_t, void *);

void taskLedInit()
{
    svcTaskAdd(1000, 1, taskLedRunner, 0);
}

void taskLedRunner(uint8_t id, void *args)
{
    svcPluginsToggleLed();
}
