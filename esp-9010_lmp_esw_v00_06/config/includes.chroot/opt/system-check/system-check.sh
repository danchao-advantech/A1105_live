#!/bin/bash
#/*
#**********************************************************************
#*
#* @filename  systme-check.sh
#*
#* @purpose   periodic check both switch if ready and feed watchdog
#*
#* @create    2016/08/18
#*
#* @author    eric lin <eric.lin@advantech.com.tw>
#*
#* @history   2016/08/18: system-check init version
#*
#**********************************************************************
#*/
#*
#* $Copyright: Copyright 1983-2015 Advantech Co., Ltd.
#* This program is the proprietary software of Advantech Corporation
#* and/or its licensors, and may only be used, duplicated, modified
#* or distributed pursuant to the terms and conditions of a separate,
#* written license agreement executed between you and Advantech
#* (an "Authorized License").  Except as set forth in an Authorized
#* License, Advantech grants no license (express or implied), right
#* to use, or waiver of any kind with respect to the Software, and
#* Advantech expressly reserves all rights in and to the Software
#* and all intellectual property rights therein.  IF YOU HAVE
#* NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE
#* IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY ADVANTECH AND DISCONTINUE
#* ALL USE OF THE SOFTWARE.  
#*
#* Except as expressly set forth in the Authorized License,
#*
#* 1.     THIS PROGRAM, INCLUDING ITS STRUCTURE, SEQUENCE AND ORGANIZATION,
#* CONSTITUTES THE VALUABLE TRADE SECRETS OF ADVANTECH, AND YOU SHALL USE
#* ALL REASONABLE EFFORTS TO PROTECT THE CONFIDENTIALITY THEREOF,
#* AND TO USE THIS INFORMATION ONLY IN CONNECTION WITH YOUR USE OF
#* ADVANTECH PRODUCTS.
#*
#* 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS
#* PROVIDED "AS IS" AND WITH ALL FAULTS AND ADVANTECH MAKES NO PROMISES,
#* REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
#* OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  ADVANTECH SPECIFICALLY
#* DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
#* NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
#* ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
#* CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
#* OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
#*
#* 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
#* ADVANTECH OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL,
#* INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER
#* ARISING OUT OF OR IN ANY WAY RELATING TO YOUR USE OF OR INABILITY
#* TO USE THE SOFTWARE EVEN IF ADVANTECH HAS BEEN ADVISED OF THE
#* POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF
#* THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR USD 1.00,
#* WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING
#* ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
#*
#* 4.     REDISTRIBUTIONS IN BINARY FORM MUST REPRODUCE BELOW COPYRIGHT NOTICS
#*/

DPSW_READY_STAMP='/tmp/.SwitchDPReady'
CPSW_READY_STAMP='/tmp/.SwitchCPReady'
SYSTEM_INIT=0

while [ true ]
do
	if [ "$SYSTEM_INIT" -eq "0" ]; then
		if [ -e $DPSW_READY_STAMP ] && [ -e $CPSW_READY_STAMP ]; then
			SYSTEM_INIT=1
			# set SYS LED to Green
			ipmitool raw 0x2e 0xe9 0x39 0x28 0x00 0x01 0x01 2>&1 > /dev/null
			# reset watchdog timer to 60 seconds (60x10=600; 600=0x258)
			ipmitool raw 0x06 0x24 0x04 0x00 0x00 0x00 0x58 0x02 2>&1 > /dev/null
			ipmitool mc watchdog reset 2>&1 > /dev/null
		fi
	else
		if [ ! -e $DPSW_READY_STAMP ] || [ ! -e $CPSW_READY_STAMP ]; then
			# reset watchdog timer to 1 seconds (1x10=10; 600=0x00a)
			ipmitool raw 0x06 0x24 0x04 0x00 0x00 0x00 0x0a 0x00 2>&1 > /dev/null
			ipmitool mc watchdog reset 2>&1 > /dev/null
		else
			# set SYS LED to Green
			ipmitool raw 0x2e 0xe9 0x39 0x28 0x00 0x01 0x01 2>&1 > /dev/null
			# reset watchdog timer to 60 seconds (60x10=600; 600=0x258)
			ipmitool raw 0x06 0x24 0x04 0x00 0x00 0x00 0x58 0x02 2>&1 > /dev/null
			ipmitool mc watchdog reset 2>&1 > /dev/null
		fi
	fi
	sleep 10
done

exit 0
