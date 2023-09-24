
//#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <sys/ioctl.h> // required for I2C device usage
#include <linux/i2c-dev.h> // required for constant definitions

//Constants
#define PH_ADDRESS 0x63
#define PH_VERSION 10

//Available commands
// measurement commands
#define CMD_GET_MEAS 0x5200

class pHSensor
{
	public:
		bool debug = false;
		
		pHSensor(void){
			char *filename = (char*)"/dev/i2c-1";  // Define the i2c file path
			i2cAddress = PH_ADDRESS;
			probeI2Cfile = open(filename, O_RDWR);  // open file for read and write
		}
		
		// System commands
		void setAddress (uint8_t address){
			i2cAddress = address;
		}
		
		uint8_t getAddress (void){
			return i2cAddress;
		}
		
		uint16_t getSoftwareVersion(void){
			return PH_VERSION;
		}
		
		// Measurement commands
		float readMeasurement(){
			if (openConnection() == 0) return __null;
			//int clock = std::clock();
			// send Read Command
			sendCommand(CMD_GET_MEAS);
			// Read
			return readFloatValue();
		}
	
	private:
		uint8_t i2cAddress;
		int probeI2Cfile;  // used when reading and writing to I2C bus
		char inData[10];  // incoming data
		
		uint8_t openConnection(void){
			// open connection to pH circuit
			if (ioctl(probeI2Cfile, I2C_SLAVE, getAddress()) < 0)
			{
				std::cout << "Failed to acquire bus access" << std::endl;
				return 0;
			}
			return 1;
		}
		
		void sendCommand(uint16_t command, uint16_t argument, bool arg){
			//init
			uint8_t length;
			if (arg) length = 4;
			else length = 2;
			uint8_t commandArr[length], argArr[2];
			
			// parse command
			commandArr[0] = command >> 8;	// MSB of command
			commandArr[1] = command & 0xFF;	// LSB of command
			
			//parse argument
			if (arg){
				argArr[0] = argument >> 8;		// MSB of argument
				argArr[1] = argument & 0xFF;	// LSB of argument
				// transfer data to commandArr
				commandArr[2] = argArr[0];
				commandArr[3] = argArr[1];
			}
			// send
			write(probeI2Cfile, commandArr, length);
		}
		
		void sendCommand(uint16_t command, uint16_t argument){
			sendCommand(command,argument,true);
		}
		
		void sendCommand(uint16_t command){
			sendCommand(command,0,false);
		}
		
		float readFloatValue(){
			uint8_t length = 10;  // Number of bytes to read
			if (read(probeI2Cfile, inData, 10) != length) {
				std::cout << "Failed to read from circuit." << std::endl;
				return __null;
			}
			else{
				float value;
				// remove first character of data
				for(short b=0; b < 10; b++) {inData[b] = inData[b+1];}
				
				value = std::stof(inData);  // try to extract ph from data
				return value;
			}
		}
};