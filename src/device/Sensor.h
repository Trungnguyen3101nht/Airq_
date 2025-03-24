#pragma once
#include "globals.h"
#include "TaskSEN55.h"
#include "TaskSCD40.h"

class Sensor
{
public:
    void sensor_init();
    Sensor() {}
    ~Sensor() {}
    void setSCD40MeasurementResult(uint16_t co2Value, float temperatureValue, float humidityValue);
    void setSEN55MeasurementResult(
        float pm1p0,
        float pm2p5,
        float pm4p0,
        float pm10p0,
        float humidity,
        float temperature,
        float voc,
        float nox);
    void setMOREMeasurementResult(float sound, float vibration, float battery);
    void setTime(const char *timeStr, const char *dateStr);

public:
    struct
    {
        float massConcentrationPm1p0;
        float massConcentrationPm2p5;
        float massConcentrationPm4p0;
        float massConcentrationPm10p0;
        float ambientHumidity;
        float ambientTemperature;
        float vocIndex;
        float noxIndex;
    } sen55;
    struct
    {
        uint16_t co2;
        float temperature;
        float humidity;
    } scd40;
    struct
    {
        float sound;
        float vibration;
        float battery;
    } more_sensor;
    struct
    {
        char time[10];
        char date[17];
    } timeData;

private:
    char _errorMessage[256];
};

extern Sensor sensor;

void SENSOR_init();
