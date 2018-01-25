PKG_NAME     := FastPath-Ent-esw-xgs4-gto-FL14R-CLS-6AIQH_OF
PKG_VERN     := 8.2.0.2
WORK_DIR     := $(CURDIR)/$(PKG_NAME)-$(PKG_VERN)
DEB_BLDIR    := $(KERN_SRC)/debian/build/build_$(DEB_ARCH)_$(DEB_FEAT)_$(DEB_FLAVOURS)
ADV_PLATFORM := ESP_9010
BOARD_NAME   := ESP9010
NUM_CPU      := $(shell cat /proc/cpuinfo | grep processor | wc -l)

.PHONY: all
all: patch
	@if [ ! -d $(KERN_SRC) ]; then \
	    make -C $(shell dirname $(KERN_SRC)); \
	fi
	@if [ -d $(PKG_NAME)-$(PKG_VERN) ]; then \
	time make -C $(WORK_DIR) WORK_DIR=$(WORK_DIR) dmode=v \
	    KERNEL_SRC=$(DEB_BLDIR) UPSTREAMDIR=$(KERN_SRC) ADV_PLATFORM=$(ADV_PLATFORM) BOARD_NAME=$(BOARD_NAME) NUM_CPU=$(NUM_CPU) \
	    ADV_ECRYPTFS_PASSPHASE=hNyRgnGiQZ90bDob \
	    2>&1 | tee fastpath.log; \
	cp $(PKG_NAME)-$(PKG_VERN)/output/$(PKG_NAME)/ipl/fastpath2-xgs4_1.8.2.0.2_amd64.deb .;\
	fi

.PHONY: config
config: patch

.PHONY: patch
patch:

.PHONY: install
install:
	mkdir -p $(INST_DIR)/mnt/application2
	mkdir -p $(INST_DIR)/mnt/fastpath2
	mkdir -p $(INST_DIR)/mnt/fastpath2/crashlogs
	cp -f files/rc.soc.isolate  $(INST_DIR)/mnt/application2
	cp -f files/rc.soc.bridge  $(INST_DIR)/mnt/application2
	cp -f files/init.sh  $(INST_DIR)/mnt/application2
	cp -f files/factory-defaults  $(INST_DIR)/mnt/application2
	cp -f files/mode_isolate  $(INST_DIR)/mnt/fastpath2
	cp -f files/run  $(INST_DIR)/mnt/application2
	cp -f fastpath2-xgs4_1.8.2.0.2_amd64.deb $(INST_PKG_DIR)

.PHONY: uninstall
uninstall:

.PHONY: clean
clean:
	make -C $(WORK_DIR) WORK_DIR=$(WORK_DIR) KERNEL_SRC=$(DEB_BLDIR) UPSTREAMDIR=$(KERN_SRC) ADV_PLATFORM=$(ADV_PLATFORM) ADV_ECRYPTFS_PASSPHASE=hNyRgnGiQZ90bDob clean

.PHONY: distclean
distclean:
	rm -f fastpath.log

