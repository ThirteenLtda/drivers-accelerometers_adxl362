rock_library(accelerometers_adxl362
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(accelerometers_adxl362_bin Main.cpp
    DEPS accelerometers_adxl362)

