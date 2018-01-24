#!/bin/bash

if [ -n "`pidof switchdrvr`" ]; then
	return 0
else
	if [ -e /lib/live/mount/persistence/sdc1/factory_mode ]; then
		if [ "`cat /lib/live/mount/persistence/sdc1/factory_mode`" = "1" ]; then
			mount -o remount,rw /dev/sdc1
			cp /lib/live/mount/persistence/sdc1/esp-9010_lmp_test_*.tar.bz2 /opt
			cd /opt
			rm -rf test
			tar jxvf esp-9010_lmp_test_*.tar.bz2
			rm esp-9010_lmp_test_*.tar.bz2
			cd /
			mount -o remount,ro /dev/sdc1
			screen -c /etc/screenrc_factory
		elif [ "`cat /lib/live/mount/persistence/sdc1/factory_mode`" = "2" ]; then
			mount -o remount,rw /dev/sdc1
			cp /lib/live/mount/persistence/sdc1/esp-9010_lmp_test_*.tar.bz2 /opt
			cd /opt
			rm -rf test
			tar jxvf esp-9010_lmp_test_*.tar.bz2
			rm esp-9010_lmp_test_*.tar.bz2
			cd /
			mount -o remount,ro /dev/sdc1
			screen -dm -c /etc/screenrc_factory
			/opt/test/burn_in/main.sh
		else
			/mnt/application2/launcher setup
			/mnt/application/launcher setup
			screen -c /etc/screenrc_login
		fi
	else
		/mnt/application2/launcher setup
		/mnt/application/launcher setup
		screen -c /etc/screenrc_login
	fi
fi
