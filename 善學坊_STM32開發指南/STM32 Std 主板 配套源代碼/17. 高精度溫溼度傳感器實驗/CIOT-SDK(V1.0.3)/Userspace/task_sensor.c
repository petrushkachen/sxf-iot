#include "task_sensor.h"

#include "svc_plugins.h"
#include "svc_sensor.h"
#include "svc_task.h"
#include "svc_log.h"

#include <stdio.h>

static void taskSensorRunner(uint8_t, void *);

void taskSensorInit()
{
    svcTaskAdd(1500, 1, taskSensorRunner, 0);
}

void taskSensorRunner(uint8_t id, void *args)
{
    char str[32];

    float temp, humi;

    if (svcSensorGetTemp(&temp) == 0) {
        sprintf(str, "temp: %.1f C", temp);
        svcPluginsLcdWrite(0, 0, (uint8_t *)str, 0);
    }

    if (svcSensorGetHumi(&humi) == 0) {
        sprintf(str, "humi: %.1f %%", humi);
        svcPluginsLcdWrite(0, 0, 0, (uint8_t *)str);
    }
}
