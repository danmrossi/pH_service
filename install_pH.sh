#!/bin/bash

    echo ""
    echo ""
    echo "This script will install pH monitoring using the Robo-Tank or Atlas-Scientific pH sensors for reef-pi and is provided by Sral."
    echo ""
    echo ""
    echo ""
    echo ""
    echo "Copyright (c) 2022 Sral"
    echo ""
    echo "Licensed under the Apache License, Version 2.0 (the 'License');"
    echo "you may not use this file except in compliance with the License."
    echo "You may obtain a copy of the License at"
    echo ""
    echo "    http://www.apache.org/licenses/LICENSE-2.0"
    echo ""
    echo "Unless required by applicable law or agreed to in writing, software"
    echo "distributed under the License is distributed on an 'AS IS' BASIS,"
    echo "WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied."
    echo "See the License for the specific language governing permissions and"
    echo "limitations under the License."
    echo ""
    echo ""
    echo "press any key to install..."
    echo ""
    echo ""
    read input
    echo ""
    echo ""

    echo "Stopping service and removing old files ..."
    sudo systemctl stop pH.service
    sudo rm -rf /var/lib/reef-pi/pH

    echo "Copying new service and setting execution rights..."
    sudo cp src/pH.service /etc/systemd/system/pH.service
    sudo chmod -R 770 /etc/systemd/system/pH.service
    
    # create directory and copy new files
    echo "Creating Reef-Pi directory and copying new files..."
    sudo mkdir /var/lib/reef-pi/pH
    sudo cp src/pH_sensor.cpp      /var/lib/reef-pi/pH/pH_sensor.cpp
    sudo cp src/pH_fetch_data     /var/lib/reef-pi/pH/pH_fetch_data
    sudo cp src/pH_fetch_data.cpp /var/lib/reef-pi/pH/pH_fetch_data.cpp
    # set rights
    sudo chmod -R 777 /var/lib/reef-pi/pH/
    
    echo "Deleting install files..."
    sudo rm -r src/
	sudo rm -r LICENSE
	sudo rm -r README.md
    sudo rm pH_service_1.0.zip
    sudo rm install_pH.sh

    echo "Establishing and starting service..."
    sudo systemctl enable pH.service
    sudo systemctl start pH.service
    echo ""
    echo ""
    echo "----------------------------------------------------------------------------"
    echo ""
    echo "Installation Complete"
    echo ""
    echo "----------------------------------------------------------------------------"
    echo ""
    echo ""
