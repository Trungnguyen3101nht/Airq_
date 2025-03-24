#ifndef GLOBALS_H
#define GLOBALS_H

// include libraries
#include <Wire.h>
#include <WiFi.h>
#include <time.h>
#include <DHT20.h>
#include <stdint.h>
#include "LittleFS.h"
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ThingsBoard.h>
#include <Arduino_MQTT_Client.h>
#include "SensirionI2CSen5x.h"
#include <SensirionI2CScd4x.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// include common files
#include "../src/common/defines.h"
#include "../src/common/info.h"

// include connect
#include "../src/connect/connect_init.h"

// include task
#include "../src/task/task_init.h"

// include device
#include "../src/device/device_intit.h"

// include utils
#include "./utils/utility_functions.h"

// include app view
#ifdef M5_CORE2
#include "../src/app/MainAppView.hpp"
#endif

#ifdef M5_CORE2
// include libraries of M5
#include <M5Unified.h>
#include <lgfx/v1/panel/Panel_GDEW0154D67.hpp>
#include <esp_adc_cal.h>

// include M5 init
#include "../src/common/M5_init.h"
#include "../src/task/WakeupDevice.h"
#endif

#endif