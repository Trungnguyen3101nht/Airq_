#include "utility_functions.h"

void parseJson(String message, bool server)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, message);
    if (error)
    {
        return;
    }

    if (!server)
    {
        if (doc["email"].as<String>() != EMAIL)
        {
            return;
        }
    }

    String mode = doc["mode"].as<String>();
    if (mode == "Manual")
    {
    }
}