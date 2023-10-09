#!/bin/bash

    echo ""
    echo ""
    echo "This script will UNINSTALL the pH monitoring analog driver using the Robo-Tank or Atlas-Scientific pH sensors for reef-pi"
    echo ""
    echo "Copyright (c) 2023"
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
    echo "Press the ENTER key to UNINSTALL..."
    echo ""
    echo ""
    read input
    echo ""
    echo ""
    echo "Stopping service and removing all files ..."
    sudo systemctl stop pH.service
    sudo systemctl disable pH.service
    sudo rm -rf /var/lib/reef-pi/pH
    sudo rm /etc/systemd/system/pH.service
    sudo rm uninstall_pH.sh
    echo ""
    echo ""
    echo "----------------------------------------------------------------------------"
    echo ""
    echo "Uninstall Complete"
    echo ""
    echo "----------------------------------------------------------------------------"
    echo ""
    echo ""
