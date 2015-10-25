#include <accelerometers_adxl362/SPI.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <linux/spi/spidev.h>
#include <string.h>
#include <errno.h>

#include <stdint.h>

using namespace accelerometers_adxl362;

SPI::SPI()
    : fd(-1) {}

SPI::~SPI()
{
    close();
}

void SPI::open(std::string const& dev, uint32_t mode, uint32_t speed_hz, uint8_t bits_per_word)
{
    close();

    fd = ::open(dev.c_str(), O_RDWR);
    if (fd == -1)
        throw std::runtime_error("cannot open device " + dev);

    if (-1 == ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed_hz))
        throw std::runtime_error("failed to set transfer speed");
    if (-1 == ioctl(fd, SPI_IOC_WR_MODE, &mode))
        throw std::runtime_error("failed to set mode");
    if (-1 == ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word))
        throw std::runtime_error("failed to set bits per word");
}

void SPI::transfer(uint8_t const* cmd, uint8_t* reply, uint8_t size)
{
    struct spi_ioc_transfer xfer;
    memset(&xfer, 0, sizeof xfer);
    xfer.tx_buf = reinterpret_cast<uint64_t>(cmd);
    xfer.rx_buf = reinterpret_cast<uint64_t>(reply);
    xfer.len = size;
    xfer.cs_change = 1;
    int status = ioctl(fd, SPI_IOC_MESSAGE(1), &xfer);
    if (status < 0)
        throw std::runtime_error("failed transfer");
}

void SPI::close()
{
    if (fd != -1)
        ::close(fd);
    fd = -1;
}

