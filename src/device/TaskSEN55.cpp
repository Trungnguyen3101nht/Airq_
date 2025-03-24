#include "TaskSEN55.h"

SensirionI2CSen5x sen5x;

void SEN55_sensor()
{
    float pm1p0 = 0.0;
    float pm2p5 = 0.0;
    float pm4p0 = 0.0;
    float pm10p0 = 0.0;
    float humidity = 0.0;
    float temperature = 0.0;
    float vocIndex = 0.0;
    float noxIndex = 0.0;
    uint16_t error;

    error = sen5x.readMeasuredValues(pm1p0, pm2p5, pm4p0, pm10p0,
                                     humidity, temperature, vocIndex, noxIndex);

    if (error)
    {
        Serial.printf("[SEN55] readMeasuredValues error: %u\n", error);
        return;
    }

    if (ws.count() > 0)
    {
        DynamicJsonDocument doc(512);
        doc["gauge_pm1"] = String(pm1p0, 2);
        doc["gauge_pm25"] = String(pm2p5, 2);
        doc["gauge_pm4"] = String(pm4p0, 2);
        doc["gauge_pm10"] = String(pm10p0, 2);
        doc["gauge_voc"] = String(vocIndex, 2);
        doc["gauge_nox"] = String(noxIndex, 2);
        doc["gauge_temp"] = String(temperature, 2);
        doc["gauge_humi"] = String(humidity, 2);

        String jsonData;
        serializeJson(doc, jsonData);
        ws.textAll(jsonData);
    }
    if (tb.connected())
    {
        publishData("telemetry", "pm1.0", String(pm1p0, 2));
        publishData("telemetry", "pm2.5", String(pm2p5, 2));
        publishData("telemetry", "pm4.0", String(pm4p0, 2));
        publishData("telemetry", "pm10", String(pm10p0, 2));
        publishData("telemetry", "voc", String(vocIndex, 2));
        publishData("telemetry", "nox", String(noxIndex, 2));
    }
    sensor.setSEN55MeasurementResult(pm1p0, pm2p5, pm4p0, pm10p0, temperature, humidity, vocIndex, noxIndex);
}

void TaskSEN55(void *pvParameters)
{
    pinMode(SEN55_POWER_EN, OUTPUT);
    digitalWrite(SEN55_POWER_EN, LOW);
    uint16_t error;

    sen5x.begin(Wire);
    error = sen5x.deviceReset();

    error = sen5x.startMeasurement();
    if (error)
    {
        Serial.printf("[SEN55] startMeasurement() failed: %u\n", error);
        vTaskDelete(NULL);
    }

    Serial.println("[SEN55] Sensor started successfully!");

    while (true)
    {
        SEN55_sensor();
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void SEN55_init()
{
    xTaskCreate(TaskSEN55, "SEN55", 4096, NULL, 1, NULL);
}
