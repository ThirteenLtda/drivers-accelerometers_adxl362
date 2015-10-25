#include <boost/test/unit_test.hpp>
#include <accelerometers_adxl362/Dummy.hpp>

using namespace accelerometers_adxl362;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    accelerometers_adxl362::DummyClass dummy;
    dummy.welcome();
}
