#include "TaskMore.h"

#define SOUND_PIN 15
#define VIBRATION_PIN 13

bool arrange = true;

float sound_value = 0;
float vibration_value = 0;
float battery_value = 0;

void Sound_sensor()
{
    const int numSamples = 50;
    int count = 0;
    long total = 0;

    int rawValue = analogRead(SOUND_PIN);

    for (int i = 0; i < numSamples; i++)
    {

        if (rawValue > 0)
        {
            total += rawValue;
            count += 1;
        }
    }

    if (count > 0)
    {
        sound_value = 20.0 * log10(float(rawValue / count));
    }
    else
    {
        Serial.println("No valid data for SOUND sensor");
    }
}

void Vibration_sensor()
{
    const int numSamples = 50;
    int count = 0;
    long total = 0;

    int rawValue = analogRead(VIBRATION_PIN);

    // for (int i = 0; i < numSamples; i++)
    // {

    //     if (rawValue > 0)
    //     {
    //         total += rawValue;
    //         count += 1;
    //     }
    // }

    // if (count > 0)
    // {
    //     vibration_value = float(rawValue / count) * 5 / 4095;
    // }
    // else
    // {
    //     Serial.println("No valid data for VIBRATION sensor");
    // }
    vibration_value = float(rawValue) * 5 / 4095;
}

void getBattery()
{
    esp_adc_cal_characteristics_t adc_chars;
    esp_adc_cal_characterize(
        ADC_UNIT_1,
        ADC_ATTEN_DB_11,
        ADC_WIDTH_BIT_12,
        1100,
        &adc_chars);

    uint32_t batteryVoltage = esp_adc_cal_raw_to_voltage(analogRead(BAT_ADC_PIN), &adc_chars);
    battery_value = (batteryVoltage - BATTERY_EMPTY_VOLTAGE) * 100.0 /
                    (BATTERY_FULL_VOLTAGE - BATTERY_EMPTY_VOLTAGE);

    if (battery_value > 100.0)
        battery_value = 100.0;
    if (battery_value < 0.0)
        battery_value = 0.0;
}

void send_Value()
{
    if (ws.count() > 0)
    {
        DynamicJsonDocument doc(512);
        doc["gauge_sound"] = String(sound_value);
        doc["gauge_vibration"] = String(vibration_value);
        doc["gauge_battery"] = String(battery_value);
        String jsonData;
        serializeJson(doc, jsonData);
        ws.textAll(jsonData);
    }

    if (tb.connected())
    {
        publishData("telemetry", "sound", String(sound_value));
        publishData("telemetry", "vibration", String(vibration_value));
        publishData("telemetry", "battery", String(battery_value));
    }
    sensor.setMOREMeasurementResult(sound_value, vibration_value, battery_value);
}

void TaskMore(void *pvParameters)
{
    while (true)
    {

        arrange ? Sound_sensor() : Vibration_sensor();
        getBattery();
        send_Value();
        arrange = !arrange;
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}

void More_init()
{
    xTaskCreate(TaskMore, "TaskMore", 8192, NULL, 1, NULL);
}
