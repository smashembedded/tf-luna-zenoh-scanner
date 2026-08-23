#include <Arduino.h>

#include "lidar/tf_luna.hpp"

HardwareSerial tfLunaSerial(2);

TfLuna lidar(
    tfLunaSerial,
    16,
    17
);

void setup()
{
    Serial.begin(115200);

    delay(500);

    lidar.begin();

    Serial.println();
    Serial.println("TF-Luna driver test");
    Serial.println("===================");
}

void loop()
{
    TfLunaMeasurement measurement;

    if (lidar.update(measurement))
    {
        Serial.printf(
            "Distance: %u cm | Signal: %u | Temperature: %.1f C\n",
            measurement.distance_cm,
            measurement.signal_strength,
            measurement.temperature_c
        );
    }
}