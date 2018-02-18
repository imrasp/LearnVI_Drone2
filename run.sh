#!/usr/bin/env bash

rm -r record_data
ip -4 -o a | grep wlan0 | cut -d'/' -f 1 | cut -d' ' -f 7 > ipaddress.txt
./build/c_uart_interface_example > log.txt 2>&1