#/*
#**********************************************************************
#*
#* @filename  Makefile
#*
#* @purpose   ifupdown Makefile
#*
#* @create    2014/12/25
#*
#* @author    eric lin <eric.lin@advantech.com.tw>
#*
#* @history   2014/12/25: init version
#*
#**********************************************************************
#*/
#/*
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
PKG_NAME   := ifupdown
PKG_VERN   := 0.7.8
CPU_CORES  := $(shell cat /proc/cpuinfo | grep "core id" | wc -l)
MAKE_JOBS  := $(shell expr $(CPU_CORES) + 1)

.PHONY: all
all: patch
	time make -C $(PKG_NAME)-$(PKG_VERN) \
	    -j $(MAKE_JOBS) 2>&1 | tee $(PKG_NAME).log
	make -C $(PKG_NAME)-$(PKG_VERN) interfaces.5.gz
	make -C $(PKG_NAME)-$(PKG_VERN) ifup.8.gz

.PHONY: conifg
config: patch

.PHONY: patch
patch:
	@if [ ! -d $(PKG_NAME)-$(PKG_VERN) ]; then \
	     tar -zxvf $(PKG_NAME)_$(PKG_VERN).tar.gz; \
	     mv $(PKG_NAME) $(PKG_NAME)-$(PKG_VERN); \
	     cd $(PKG_NAME)-$(PKG_VERN); \
	     patch -p1 < ../patches/0001_daemonize-$(PKG_VERN).patch; \
	fi

.PHONY: install
install:
ifneq ("$(wildcard $(PKG_NAME)-$(PKG_VERN)/ifup)","")
	mkdir -p $(INST_DIR)/usr/share/man/man5
	mkdir -p $(INST_DIR)/usr/share/man/man8
	make -C $(PKG_NAME)-$(PKG_VERN) install \
		BASEDIR=$(INST_DIR)
	install -D -m 644 $(PKG_NAME)-$(PKG_VERN)/interfaces.5.gz $(INST_DIR)/usr/share/man/man5/
	install -D -m 644 $(PKG_NAME)-$(PKG_VERN)/ifup.8.gz $(INST_DIR)/usr/share/man/man8/
	ln -sf ifup.8.gz $(INST_DIR)/usr/share/man/man8/ifdown.8.gz
	ln -sf ifup.8.gz $(INST_DIR)/usr/share/man/man8/ifquery.8.gz
endif

.PHONY: uninstall
uninstall:
	rm -f $(INST_DIR)/sbin/ifup
	rm -f $(INST_DIR)/sbin/ifdown
	rm -f $(INST_DIR)/sbin/ifquery
	rm -f $(INST_DIR)/usr/share/man/man5/interfaces.5*
	rm -f $(INST_DIR)/usr/share/man/man8/ifup.8*
	rm -f $(INST_DIR)/usr/share/man/man8/ifdown.8*
	rm -f $(INST_DIR)/usr/share/man/man8/ifquery.8*

.PHONY: clean
clean:
ifneq ("$(wildcard $(PKG_NAME)-$(PKG_VERN))","")
	make -C $(PKG_NAME)-$(PKG_VERN) clean
	rm -f $(PKG_NAME)-$(PKG_VERN)/interfaces.5.gz
	rm -f $(PKG_NAME)-$(PKG_VERN)/ifup.8.gz
endif

.PHONY: distclean
distclean:
	rm -rf $(PKG_NAME)-$(PKG_VERN)
	rm -f $(PKG_NAME).log

