#ifndef __SVC_SENSOR_H__
#define __SVC_SENSOR_H__

void svcSensorInit(void);

int svcSensorGetTemp(float *value);
int svcSensorGetHumi(float *value);

#endif /* __SVC_SENSOR_H__ */
