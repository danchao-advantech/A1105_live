#!/bin/bash

DP_READY="/tmp/.SwitchDPReady"

# Waiting for Switch Ready
while [ ! -f $DP_READY ]; do
	sleep 1
done

# Reset DP CPLD
ipmitool raw 0x2e 0xee 0x39 0x28 0x00 > /dev/null 2>&1

