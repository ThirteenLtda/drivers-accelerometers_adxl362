#ifndef ACCELEROMETERS_ADXL362_DRIVER_HPP
#define ACCELEROMETERS_ADXL362_DRIVER_HPP

#include <accelerometers_adxl362/SPI.hpp>

namespace accelerometers_adxl362
{
    struct Driver : public SPI
    {
        struct DeviceID
        {
            uint8_t ad_device_id;
            uint8_t mems_device_id;
            uint8_t part_id;
            uint8_t rev_id;
        };

        struct RawData
        {
            int16_t x;
            int16_t y;
            int16_t z;
            int16_t temperature;
        };
        
        struct Data
        {
            float x;
            float y;
            float z;
            float temperature;
        };

        void open(std::string const& device);

        uint8_t readRegister(uint8_t reg);
        void writeRegister(uint8_t reg, uint8_t value);
        DeviceID readID();

        float getAccelerationScaleFactor() const;
        void measure();
        void standby();
        RawData readRawData();
        Data convertRawData(RawData const& raw) const;
        Data readData();
    };
}

#endif
