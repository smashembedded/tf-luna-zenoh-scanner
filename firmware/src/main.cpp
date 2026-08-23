#include <Arduino.h>

HardwareSerial tfLunaSerial(2);

constexpr uint32_t TF_LUNA_BAUDRATE = 115200;
constexpr int TF_LUNA_RX_PIN = 16;
constexpr int TF_LUNA_TX_PIN = 17;

void setup()
{
    Serial.begin(115200);

    tfLunaSerial.begin(
        TF_LUNA_BAUDRATE,
        SERIAL_8N1,
        TF_LUNA_RX_PIN,
        TF_LUNA_TX_PIN
    );

    Serial.println();
    Serial.println("TF-Luna UART test");
    Serial.println("------------------");
}

void loop()
{
    while (tfLunaSerial.available())
    {
        const uint8_t byte = tfLunaSerial.read();

        Serial.printf("%02X ", byte);
    }

    delay(10);
}
