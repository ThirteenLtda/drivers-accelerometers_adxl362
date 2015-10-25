rock_library(accelerometers_adxl362
    SOURCES SPI.cpp Driver.cpp
    HEADERS SPI.hpp Driver.hpp)

rock_executable(adxl362 Main.cpp
    DEPS accelerometers_adxl362)

