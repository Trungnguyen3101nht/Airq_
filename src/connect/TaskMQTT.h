#ifndef INC_TASKMQTT_H_
#define INC_TASKMQTT_H_

#include "globals.h"

extern ThingsBoard tb;

void MQTT_reconnect();
void publishData(String mode, String feed, String data);

#endif /* INC_TASKMQTT_H_ */