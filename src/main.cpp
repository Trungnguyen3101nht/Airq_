
#include "globals.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting...");

  if (!LittleFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting LittleFS");
  }

#ifdef M5_CORE2
  M5_init();
  WakeupDevice();
#endif

  // FreeRTOS tasks
  if (check_info())
  {
    device_intit();
    task_intit();
  }
}

void loop()
{
  if (!Wifi_reconnect())
  {
    stopServer();
    return;
  }
  MQTT_reconnect();
  if (!isServerRunning)
  {
    connnectWSV();
  }
}