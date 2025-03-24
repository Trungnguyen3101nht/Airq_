#include "Sensor.h"

Sensor sensor;

void Sensor::setSCD40MeasurementResult(uint16_t co2Value, float temperatureValue, float humidityValue)
{
    scd40.co2 = co2Value;
    scd40.temperature = temperatureValue;
    scd40.humidity = humidityValue;
}

void Sensor::setSEN55MeasurementResult(
    float pm1p0,
    float pm2p5,
    float pm4p0,
    float pm10p0,
    float temperature,
    float humidity,
    float voc,
    float nox)
{
    sen55.massConcentrationPm1p0 = pm1p0;
    sen55.massConcentrationPm2p5 = pm2p5;
    sen55.massConcentrationPm4p0 = pm4p0;
    sen55.massConcentrationPm10p0 = pm10p0;
    sen55.ambientTemperature = temperature;
    sen55.ambientHumidity = humidity;
    sen55.vocIndex = voc;
    sen55.noxIndex = nox;
}

void Sensor::setMOREMeasurementResult(float sound, float vibration, float battery)
{
    more_sensor.sound = sound;
    more_sensor.vibration = vibration;
    more_sensor.battery = battery;
}

void Sensor::sensor_init()
{
    more_sensor.sound = 0;
    more_sensor.vibration = 0;
    more_sensor.battery = 0;
    scd40.co2 = 0;
    scd40.temperature = 0.0f;
    scd40.humidity = 0.0f;
    sen55.massConcentrationPm1p0 = 0.0f;
    sen55.massConcentrationPm2p5 = 0.0f;
    sen55.massConcentrationPm4p0 = 0.0f;
    sen55.massConcentrationPm10p0 = 0.0f;
    sen55.ambientHumidity = 0.0f;
    sen55.ambientTemperature = 0.0f;
    sen55.vocIndex = 0.0f;
    sen55.noxIndex = 0.0f;
    memset(timeData.time, 0, sizeof(timeData.time));
    memset(timeData.date, 0, sizeof(timeData.date));
    memset(_errorMessage, 0, sizeof(_errorMessage));
    log_i("Sensor initialized.");
}

void Sensor::setTime(const char *timeStr, const char *dateStr)
{
    strncpy(timeData.time, timeStr, sizeof(timeData.time) - 1);
    timeData.time[sizeof(timeData.time) - 1] = '\0';

    strncpy(timeData.date, dateStr, sizeof(timeData.date) - 1);
    timeData.date[sizeof(timeData.date) - 1] = '\0';
}

void updateView()
{
#ifdef M5_CORE2
    statusView.updateSCD40(
        sensor.scd40.co2,
        sensor.scd40.temperature,
        sensor.scd40.humidity);
    statusView.updateSEN55(
        sensor.sen55.massConcentrationPm1p0,
        sensor.sen55.massConcentrationPm2p5,
        sensor.sen55.massConcentrationPm4p0,
        sensor.sen55.massConcentrationPm10p0,
        sensor.sen55.ambientHumidity,
        sensor.sen55.ambientTemperature,
        sensor.sen55.vocIndex,
        sensor.sen55.noxIndex);
    if (WiFi.status() == WL_CONNECTED)
    {
        if (tb.connected())
        {
            statusView.updateNetworkStatus("WIFI", WiFi.localIP().toString().c_str());
        }
        else
        {
            statusView.updateNetworkStatus("ERROR", "Connect MQTT");
        }
    }
    else
    {
        statusView.updateNetworkStatus("ERROR", "No Internet");
    }
    statusView.updateTime(sensor.timeData.time, sensor.timeData.date);
    statusView.updateMORE(sensor.more_sensor.sound, sensor.more_sensor.vibration, sensor.more_sensor.battery);
    statusView.load();
#endif
}

void TaskSENSOR(void *pvParameters)
{
    sensor.sensor_init();
    while (true)
    {
        updateView();
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void SENSOR_init()
{
    SEN55_init();
    SCD40_init();
    More_init();
    xTaskCreate(TaskSENSOR, "TaskSENSOR", 4096, NULL, 1, NULL);
}