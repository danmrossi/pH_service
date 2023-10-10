#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sys/ioctl.h> // required for I2C device usage
#include <linux/i2c-dev.h> // required for constant definitions
#include "pH_sensor.cpp"

int saveToFile(float saveValue, std::string filename){
	// std::cout << filename << std::endl;
	if (isnan(saveValue) || saveValue < 2.0){ return 0; }
	// open file to save value
	std::fstream saveFile;
	saveFile.open(filename,std::ios::out);
	if(saveFile.is_open()){
		saveFile << saveValue;  // save value
		saveFile.close();  // close file
	}
	return 1;
}

//////////
// main //
//////////
int main(int argc, char *argv[])
{
	// init
	pHSensor pH_sensor;
	if (argc > 1) pH_sensor.setAddress(atoi(argv[1]));
	// read and save
	std::string filePath = "/var/lib/reef-pi/pH/";
	if (saveToFile(pH_sensor.readMeasurement(),filePath+"pH.dat") == 0){
		pH_sensor.saveDataToFile(filePath+"errorData.dat");
		return 0;
	}
	return 1;
}
