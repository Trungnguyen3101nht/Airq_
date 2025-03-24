#ifndef INC_TASKSERVER_H_
#define INC_TASKSERVER_H_

#include "globals.h"

extern AsyncWebServer server;
extern AsyncWebSocket ws;

void connnectWSV();
void stopServer();
extern bool isServerRunning;

#endif /* INC_TASKSERVER_H_ */