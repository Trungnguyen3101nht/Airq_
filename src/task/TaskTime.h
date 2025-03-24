#ifndef INC_TASKTIME_H_
#define INC_TASKTIME_H_

#include "globals.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void TaskTime(void *pvParameters);

#ifdef __cplusplus
}
#endif

extern String current;
extern String date;
extern bool check_different_time;

#endif /* INC_TASKTIME_H_ */