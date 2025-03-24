#include "TaskTime.h"
#include "WiFi.h"
#include "esp_timer.h"
#include <time.h>

const long gmtOffset_sec = 7 * 3600; // GMT+7 cho Việt Nam
const int daylightOffset_sec = 0;

unsigned long baseEpochTime = 0;
unsigned long baseMicros = 0;

String current = "";
String check_time = "";
String date = "";
bool check_different_time = false;

extern AsyncWebSocket ws;

void syncTimeOnceWithNTP()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Đang đồng bộ thời gian với NTP...");
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

        struct tm timeinfo;
        if (!getLocalTime(&timeinfo))
        {
            Serial.println("Lỗi: Không thể lấy thời gian từ NTP!");
            return;
        }
        time_t now;
        time(&now);

        baseEpochTime = now;
        baseMicros = esp_timer_get_time();

        Serial.printf("Đồng bộ NTP thành công! Epoch Time: %lu\n", baseEpochTime);
    }
    else
    {
        Serial.println("Chưa có WiFi, không thể đồng bộ NTP.");
    }
}

unsigned long getCurrentEpochTime()
{
    if (baseEpochTime == 0)
    {
        return 0;
    }

    unsigned long elapsedMillis = (esp_timer_get_time() - baseMicros) / 1000;
    return baseEpochTime + (elapsedMillis / 1000);
}

String getDayOfWeek(unsigned long epochTime)
{
    time_t rawTime = epochTime;
    struct tm *timeInfo = localtime(&rawTime);

    String days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days[timeInfo->tm_wday];
}

String formatTime(unsigned long epochTime)
{
    time_t rawTime = epochTime;
    struct tm *timeInfo = localtime(&rawTime);

    char buffer[6];
    sprintf(buffer, "%02d:%02d", timeInfo->tm_hour, timeInfo->tm_min);
    return String(buffer);
}

String getDateString(unsigned long epochTime)
{
    time_t rawTime = epochTime;
    struct tm *timeInfo = localtime(&rawTime);

    char buffer[11];
    sprintf(buffer, "%02d-%02d-%04d",
            timeInfo->tm_mday,
            timeInfo->tm_mon + 1,
            timeInfo->tm_year + 1900);

    return String(buffer);
}

String formatDateTime(unsigned long epochTime)
{
    time_t rawTime = epochTime;
    struct tm *timeInfo = localtime(&rawTime);

    char buffer[20];
    sprintf(buffer, "%02d:%02d %02d-%02d-%04d",
            timeInfo->tm_hour,
            timeInfo->tm_min,
            timeInfo->tm_mday,
            timeInfo->tm_mon + 1,
            timeInfo->tm_year + 1900);

    return String(buffer);
}

void TaskTime(void *pvParameters)
{
    Serial.println("TaskTime đã khởi động!");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Đang chờ WiFi...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    syncTimeOnceWithNTP();

    while (true)
    {
        if (WiFi.status() == WL_CONNECTED && baseEpochTime == 0)
        {
            syncTimeOnceWithNTP();
        }

        unsigned long currentTime = getCurrentEpochTime();
        if (currentTime == 0)
        {
            Serial.println("Chưa có thời gian NTP, đợi đồng bộ...");
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            continue;
        }

        String current_time = formatTime(currentTime);
        String dayOfWeek = getDayOfWeek(currentTime);
        date = formatDateTime(currentTime);

        current = dayOfWeek + " " + current_time;
        check_different_time = (check_time != current_time);
        check_time = current_time;

        String data = "{\"current\":\"" + current + "\"}";

        if (ws.count() > 0)
        {
            ws.textAll(data);
        }
        String date_LCD = getDateString(currentTime);
        sensor.setTime(current_time.c_str(), date_LCD.c_str());

        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}
