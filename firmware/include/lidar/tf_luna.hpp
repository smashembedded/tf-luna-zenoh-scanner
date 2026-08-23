#pragma once

#include <Arduino.h>

struct TfLunaMeasurement
{
    uint16_t distance_cm;
    uint16_t signal_strength;
    float temperature_c;
};

class TfLuna
{
public:
    TfLuna(
        HardwareSerial& serial,
        int rx_pin,
        int tx_pin,
        uint32_t baudrate = 115200
    );

    void begin();

    bool update(TfLunaMeasurement& measurement);

private:
    static constexpr uint8_t FRAME_HEADER = 0x59;
    static constexpr size_t FRAME_LENGTH = 9;

    HardwareSerial& serial_;
    int rx_pin_;
    int tx_pin_;
    uint32_t baudrate_;

    uint8_t frame_[FRAME_LENGTH];
    size_t frame_index_;

    bool processByte(uint8_t byte);
    bool validateChecksum() const;
    void parseMeasurement(TfLunaMeasurement& measurement) const;
};