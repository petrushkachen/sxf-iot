#ifndef __HAL_TIMER_H__
#define __HAL_TIMER_H__

/* 
 *  period: how many milliseconds, 1 ~ 65534
 *  onTick: callback
 */
void halTimerInit(unsigned int period, void (*onTimerIRQ)(void));

void halTimerStart(void);
void halTimerStop(void);

#endif /* #ifndef __HAL_TIMER_H__ */
