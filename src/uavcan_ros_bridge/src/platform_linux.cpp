#include <uavcan_linux/uavcan_linux.hpp>

uavcan::ISystemClock& getSystemClock()
{
	static uavcan_linux::SystemClock systemclock;
	return systemclock;
}

uavcan::ICanDriver& getCanDriver()
{
	static uavcan_linux::SocketCanDriver driver(dynamic_cast<uavcan_linux::SystemClock&>(getSystemClock()));
	if(driver.getNumIfaces()==0)
	{
		if(driver.addIface("can0") < 0)
			std::cerr << "Failed to add interface can0\n";
	}
	
	return driver;
}
