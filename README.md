# pH_service
Raspbian service to read out the Robo-Tank pH sensor data without communication errors.

## How to INSTALL

 - In SSH command console type:
 - sudo wget -c https://github.com/danmrossi/pH_service/releases/download/1.0/pH_service_1.0.zip
 - sudo unzip pH_service_1.0.zip
 - sudo bash install_pH.sh
 
 - The install script will copy all files, start the necessary service and clean up the install files afterwards.
 - It will leave behind uninstall_pH.sh for you to run when you need to remove the driver completely.
 
 - In reef-pi go to Configuration > Drivers
 - Create 1 file driver in reef-pi:
	- Name appropriately (e.g. "pH_File")
	- Type: "file-analog"
	- Path: (for each filedriver respectively):
		- "/var/lib/reef-pi/pH/pH.dat" (without the "")
		
 - Go to Configuration > Admin and Reload
 - Go to Configuration > Connectors
	- Create 1 Analog-Inputs:
		- Name appropriately (e.g. "pH_File")
		- Driver: the 1 file-drivers you have created before
		- Pin: 0
 - Go to Configuration > Admin and Reload
 - Go to pH
 - Add 1 "pH" values using the analog-inputs you have just created

## How to UNINSTALL

 - Remove your pH Driver and Connectors you created in the steps above
 - Then, In SSH command console type:
 - sudo bash uninstall_pH.sh
 - The uninstall_pH.sh file will also be removed as part of the process
