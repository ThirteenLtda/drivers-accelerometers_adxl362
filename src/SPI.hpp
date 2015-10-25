#ifndef ADXL362_SPI_HPP
#define ADXL362_SPI_HPP

#include <string>
#include <stdint.h>

namespace accelerometers_adxl362
{
    class SPI
    {
        int fd;
    public:

        SPI();
        ~SPI();

        void open(std::string const& dev, uint32_t mode, uint32_t speed_hz, uint8_t bits_per_word);
        void transfer(uint8_t const* cmd, uint8_t* reply, uint8_t size);
        void close();
    };
}

#endif

