#include "Stepper.hpp"
#include <boost/timer/timer.hpp>
#include <boost/lexical_cast.hpp>
void Stepper::Initialize(std::string pname){
	this->serial.open(pname);
	this->serial.set_option(boost::asio::serial_port_base::baud_rate(9600));
	this->serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
	this->serial.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
	this->serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
	std::cout << "Port "<< pname << " opened. "<<std::endl;
}
void Stepper::Send (std::string text){
	writeString(text);
	//std::cout<<text<<std::endl;
}
void Stepper::Finish()
{
	writeString("0");
	this->serial.close();
}
void Stepper::writeString(std::string s)
{
	boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
	std::cout<< s << std::endl;
}
void Stepper::Step(int steps){
	for (int i=0;i<steps;i++){
	boost::timer::cpu_timer tkrok;
	std::string text="0"+boost::lexical_cast<std::string>((StepNum%4)+1);//.ToString();
	this->Send(text);
	
	while (tkrok.elapsed().wall<100*1e6){
	
	};
	//
	this->StepNum++;
	}
	this->Send("0");
}