#/*
#**********************************************************************
#*
#* @filename  Makefile
#*
#* @purpose   This Makefile is used for system utility
#*
#* @create    2015/05/25
#*
#* @author    Terry Huang <terry.huang@advantech.com.tw>
#*
#* @history   2015/05/25: init version
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

TARGETS    := peek poke iopeek iopoke 
TARGETS_SUBDIRS :=  

.PHONY: all
all: $(TARGETS)
ifneq ("$(wildcard $(TARGETS_SUBDIRS))","")
	make -C $(TARGETS_SUBDIRS) $@
endif

.PHONY: config
config:

.PHONY: patch
patch:

.PHONY: install
install:
	mkdir -p $(INST_DIR)/sbin
ifneq ("$(wildcard $(TARGETS))","")
	cp $(TARGETS) $(INST_DIR)/sbin/
endif
ifneq ("$(wildcard $(TARGETS_SUBDIRS))","")
	make -C $(TARGETS_SUBDIRS) $@
endif
	mkdir -p $(INST_DIR)/lib/modules/$(KERN_VER)/kernel/drivers/net/
	cp iqvlinux.ko $(INST_DIR)/lib/modules/$(KERN_VER)/kernel/drivers/net/

.PHONY: uninstall
uninstall:
ifneq ("$(wildcard $(addprefix $(INST_DIR)/sbin/,$(TARGETS)))","")
	rm -f $(addprefix $(INST_DIR)/sbin/,$(TARGETS))
endif
ifneq ("$(wildcard $(TARGETS_SUBDIRS))","")
	make -C $(TARGETS_SUBDIRS) $@
endif
	rm -f $(INST_DIR)/lib/modules/$(KERN_VER)/kernel/drivers/net/iqvlinux.ko

.PHONY: clean
clean:
	rm -rf $(TARGETS) iqvlinux iqvlinux.ko
ifneq ("$(wildcard $(TARGETS_SUBDIRS))","")
	make -C $(TARGETS_SUBDIRS) $@
endif

.PHONY: distclean
distclean: clean

$(TARGETS):
	$(CC) -o $@ $(@:=.c)
	./iqv-build.sh

