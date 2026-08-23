#include "lidar/tf_luna.hpp"

TfLuna::TfLuna(
    HardwareSerial& serial,
    int rx_pin,
    int tx_pin,
    uint32_t baudrate)
    : serial_(serial),
      rx_pin_(rx_pin),
      tx_pin_(tx_pin),
      baudrate_(baudrate),
      frame_index_(0)
{
}

void TfLuna::begin()
{
    serial_.begin(
        baudrate_,
        SERIAL_8N1,
        rx_pin_,
        tx_pin_
    );
}

bool TfLuna::update(TfLunaMeasurement& measurement)
{
    while (serial_.available())
    {
        const uint8_t byte = serial_.read();

        if (processByte(byte))
        {
            parseMeasurement(measurement);
            return true;
        }
    }

    return false;
}

bool TfLuna::processByte(uint8_t byte)
{
    // Wait for the first header byte.
    if (frame_index_ == 0)
    {
        if (byte != FRAME_HEADER)
        {
            return false;
        }

        frame_[frame_index_++] = byte;
        return false;
    }

    // Wait for the second header byte.
    if (frame_index_ == 1)
    {
        if (byte != FRAME_HEADER)
        {
            frame_index_ = 0;
            return false;
        }

        frame_[frame_index_++] = byte;
        return false;
    }

    // Store the remaining frame bytes.
    frame_[frame_index_++] = byte;

    if (frame_index_ < FRAME_LENGTH)
    {
        return false;
    }

    const bool valid = validateChecksum();

    frame_index_ = 0;

    return valid;
}

bool TfLuna::validateChecksum() const
{
    uint8_t checksum = 0;

    for (size_t i = 0; i < FRAME_LENGTH - 1; ++i)
    {
        checksum += frame_[i];
    }

    return checksum == frame_[FRAME_LENGTH - 1];
}

void TfLuna::parseMeasurement(
    TfLunaMeasurement& measurement) const
{
    measurement.distance_cm =
        static_cast<uint16_t>(frame_[2]) |
        (static_cast<uint16_t>(frame_[3]) << 8);

    measurement.signal_strength =
        static_cast<uint16_t>(frame_[4]) |
        (static_cast<uint16_t>(frame_[5]) << 8);

    const uint16_t temperature_raw =
        static_cast<uint16_t>(frame_[6]) |
        (static_cast<uint16_t>(frame_[7]) << 8);

    measurement.temperature_c =
        static_cast<float>(temperature_raw) / 8.0f - 256.0f;
}