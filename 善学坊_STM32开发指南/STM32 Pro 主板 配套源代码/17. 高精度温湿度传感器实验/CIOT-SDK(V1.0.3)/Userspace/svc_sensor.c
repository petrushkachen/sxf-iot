#include "svc_sensor.h"

#include "hal_dht20.h"

void svcSensorInit()
{
    
}

int svcSensorGetTemp(float *value)
{
    AHT20Data_t data = halDht20GetData();

    if (!data.ok) return -1;

    *value = data.temp;
    return 0;
}

int svcSensorGetHumi(float *value)
{
    AHT20Data_t data = halDht20GetData();

    if (!data.ok) return -1;

    *value = data.humi;
    return 0;
}
