#!/bin/bash

SDK_READY_STAMP='/tmp/.BcmSdkReady'
SDK_CMDIO_IN_PIPE='/tmp/.BcmSdkShellIn'
SDK_CMDIO_OUT_PIPE='/tmp/.BcmSdkShellOut'

# Waiting for SDK Ready
while [ ! -e $SDK_READY_STAMP ] || [ ! -e $SDK_CMDIO_IN_PIPE ] || [ ! -e $SDK_CMDIO_OUT_PIPE ]; do
	sleep 1
done

# Reset DP/CP CPLD
ipmitool raw 0x2e 0xee 0x39 0x28 0x00
ipmitool raw 0x2e 0xef 0x39 0x28 0x00

