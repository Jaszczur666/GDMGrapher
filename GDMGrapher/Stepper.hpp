#ifndef STEPPER_H
#define STEPPER_H
#include <string>
#include <boost/asio/serial_port.hpp> 
#include <boost/asio.hpp> 
#include <iostream>
class Stepper{
public:

	Stepper(std::string port)
		: io(), serial(io)
	{
	}

	void writeString(std::string s);
	void Finish();
	void Send (std::string text);
	void Initialize(std::string pname);
	int StepNum;
	void Step(int steps);
private:
	boost::asio::io_service io;
	boost::asio::serial_port serial;

};
#endif