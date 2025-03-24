#include "WakeupDevice.h"
#include "driver/rtc_io.h"

typedef enum WakeupType_t
{
    E_WAKEUP_TYPE_UNKNOWN = 0,
    E_WAKEUP_TYPE_USER,
    E_WAKEUP_TYPE_USB,
} WakeupType_t;

WakeupType_t wakeupType = E_WAKEUP_TYPE_UNKNOWN;

unsigned long buttonPressStartTime = 0;
bool isDeviceOn = true;

void wakeup()
{
    // Khi thiết bị được đánh thức từ deep sleep
    // log_i("Device is waking up from deep sleep.");
    // isDeviceOn = true; // Đánh dấu trạng thái thiết bị là bật
    lcd.clear(TFT_BLACK);
    lcd.waitDisplay();
    lcd.clear(TFT_WHITE);
    lcd.waitDisplay();
    ESP.restart();
}

void wakeup_stub()
{
    wakeup();
}

void shutdown()
{
    // Tắt thiết bị
    lcd.clear(TFT_BLACK);
    lcd.waitDisplay();
    lcd.clear(TFT_WHITE);
    lcd.waitDisplay();
    lcd.drawJpgFile(FILESYSTEM, "/wakeup.jpg", 0, 0);
    lcd.drawString("5", 86, 173, &fonts::FreeSansBold12pt7b);
    lcd.sleep();
    lcd.waitDisplay();
    delay(10);
    digitalWrite(POWER_HOLD, LOW);

    lcd.wakeup();
    lcd.waitDisplay();
    gpio_hold_en((gpio_num_t)SEN55_POWER_EN);

    // Đưa ESP32 vào chế độ ngủ sâu (deep sleep)
    wakeupType = E_WAKEUP_TYPE_USB;
    digitalWrite(POWER_HOLD, HIGH);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_42, 0);
    rtc_gpio_pullup_dis(GPIO_NUM_42);
    rtc_gpio_pulldown_en(GPIO_NUM_42);
    esp_set_deep_sleep_wake_stub(wakeup_stub);
    gpio_deep_sleep_hold_en();
    esp_deep_sleep_start();
}

void TaskWakeupDevice(void *pvParameters)
{
    while (true)
    {
        if (digitalRead(USER_BUTTON_POWER) == 0)
        {
            if (buttonPressStartTime == 0)
            {
                buttonPressStartTime = millis();
            }
            else if (millis() - buttonPressStartTime >= 5000)
            {
                log_i("Button held for 5 seconds, toggling device state");
                shutdown();
                buttonPressStartTime = 0;
            }
            wakeupType = E_WAKEUP_TYPE_USER;
        }
        else
        {
            buttonPressStartTime = 0;
            wakeupType = E_WAKEUP_TYPE_USB;
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void WakeupDevice()
{
    pinMode(POWER_HOLD, OUTPUT);
    pinMode(USER_BUTTON_POWER, INPUT);
    digitalWrite(POWER_HOLD, HIGH);
    xTaskCreate(TaskWakeupDevice, "TaskWakeupDevice", 4096, NULL, 1, NULL);
}
