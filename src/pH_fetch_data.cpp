#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sys/ioctl.h> // required for I2C device usage
#include <linux/i2c-dev.h> // required for constant definitions
#include "pH_sensor.cpp"

float previousValue = 0.0; // Initialize the previous value

void saveToFile(float saveValue, std::string filename){
	// std::cout << filename << std::endl;
	if (isnan(saveValue) || saveValue == 0.0){ return; }
	// open file to save value
	std::fstream saveFile;
	saveFile.open(filename,std::ios::out);
	if(saveFile.is_open()){
		saveFile << saveValue;  // save value
		saveFile.close();  // close file
	}
}

//////////
// main //
//////////
int main(int argc, char *argv[]) {
    // init
    pHSensor pH_sensor;
    if (argc > 1) pH_sensor.setAddress(atoi(argv[1]));
    // read and save
    std::string filePath = "/var/lib/reef-pi/pH/";

    float pHValue = pH_sensor.readMeasurement(); // Read the pH measurement

    // Check if the pH value is less than 2
    if (pHValue < 2.0) {
        // If it's less than 2, use the previous value
        saveToFile(previousValue, filePath + "pH.dat");
        std::cout << "pH value less than 2. Using previous value: " << previousValue << std::endl;
    } else {
        // If it's greater than or equal to 2, save the value and update the previous value
        saveToFile(pHValue, filePath + "pH.dat");
        previousValue = pHValue;
        std::cout << "pH value saved: " << pHValue << std::endl;
    }

    return 0;
}
