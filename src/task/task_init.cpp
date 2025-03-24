#include "task_init.h"

void task_intit()
{
    xTaskCreate(TaskTime, "TaskTime", 2048, NULL, 1, NULL);
}