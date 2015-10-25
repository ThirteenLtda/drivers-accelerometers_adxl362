#include <accelerometers_adxl362/Driver.hpp>
#include <linux/spi/spidev.h>

using namespace accelerometers_adxl362;

void Driver::open(std::string const& device)
{
    SPI::open(device, SPI_MODE_0, 500000, 0);
}

uint8_t Driver::readRegister(uint8_t reg)
{
    uint8_t cmd[3] = { 0x0B, reg, 0 };
    uint8_t reply[3];
    transfer(cmd, reply, 3);
    return reply[0];
}

void Driver::writeRegister(uint8_t reg, uint8_t value)
{
    uint8_t cmd[3] = { 0x0A, reg, value };
    uint8_t reply[3];
    transfer(cmd, reply, 3);
}

Driver::DeviceID Driver::readID()
{
    uint8_t cmd[6] = { 0x0B, 0x00, 0, 0, 0, 0 };
    uint8_t reply[6];
    transfer(cmd, reply, 6);
    DeviceID result;
    result.ad_device_id = reply[2];
    result.mems_device_id = reply[3];
    result.part_id   = reply[4];
    result.rev_id    = reply[5];
    return result;
}

float Driver::getAccelerationScaleFactor() const
{
    // See device spec, value at 2g
    return 0.001;
}

void Driver::measure()
{
    writeRegister(0x2D, 2);
}

void Driver::standby()
{
    writeRegister(0x2D, 0);
}

Driver::RawData Driver::readRawData()
{
    uint8_t cmd[10];
    cmd[0] = 0x0B;
    cmd[1] = 0x0E;
    uint8_t reply[10];
    transfer(cmd, reply, 10);

    RawData result;
    result.x = static_cast<uint16_t>(reply[3]) << 8 | reply[2];
    result.y = static_cast<uint16_t>(reply[5]) << 8 | reply[4];
    result.z = static_cast<uint16_t>(reply[7]) << 8 | reply[6];
    result.temperature = static_cast<uint16_t>(reply[9]) << 8 | reply[8];
    return result;
}

Driver::Data Driver::convertRawData(RawData const& raw) const
{
    float accel_scale = getAccelerationScaleFactor();

    Data result;
    result.x = accel_scale * raw.x;
    result.y = accel_scale * raw.y;
    result.z = accel_scale * raw.z;
    result.temperature = raw.temperature;
    return result;
}

Driver::Data Driver::readData()
{
    return convertRawData(readRawData());
}

