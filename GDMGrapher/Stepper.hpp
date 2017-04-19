#ifndef STEPPER_H
#define STEPPER_H
#include <string>
#include <boost/asio/serial_port.hpp> 
#include <boost/asio.hpp> 
class Stepper{
public:
	void SetPort(std::string PortName);
	void Initialize();
private:
	std::string _PortName;

};
#endif