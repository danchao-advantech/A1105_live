#!/bin/bash

CP_READY="/tmp/.SwitchCPReady"

# Waiting for Switch Ready
while [ ! -f $CP_READY ]; do
	sleep 1
done

# Reset CP CPLD
ipmitool raw 0x2e 0xef 0x39 0x28 0x00 > /dev/null 2>&1

