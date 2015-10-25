#include <iostream>
#include <unistd.h>
#include <accelerometers_adxl362/Driver.hpp>

using namespace std;
using namespace accelerometers_adxl362;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cerr << "usage: adxl362 DEV" << std::endl;
        return 1;
    }

    Driver spi;
    spi.open(argv[1]);

    Driver::DeviceID device_id = spi.readID();
    cout << "connected to Analog Device device " << hex
        << (int)device_id.ad_device_id << ":" << (int)device_id.mems_device_id << " "
        << "part " << (int)device_id.part_id << " rev " << (int)device_id.rev_id << endl;

    spi.standby();
    spi.measure();
    while (true)
    {
        Driver::RawData raw = spi.readRawData();
        cout << hex << raw.x << " " << raw.y << " " << raw.z << " " << raw.temperature << std::endl;
        Driver::Data data = spi.convertRawData(raw);
        cout << data.x << " " << data.y << " " << data.z << " " << data.temperature << std::endl;
        sleep(1);
    }
}

