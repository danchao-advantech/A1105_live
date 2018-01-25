PKG_NAME   := sdk-xgs-robo
PKG_VERN   := 6.4.6
WORK_DIR   := $(CURDIR)/$(PKG_NAME)-$(PKG_VERN)/systems/linux/user/x86-smp_debian_64-3_16
MAKE_JOBS  := 2
DEB_BLDIR  := $(KERN_SRC)/debian/build/build_$(DEB_ARCH)_$(DEB_FEAT)_$(DEB_FLAVOURS)

.PHONY: all
all: patch
	@if [ ! -d $(KERN_SRC) ]; then \
	    make -C $(shell dirname $(KERN_SRC)); \
	fi
	@if [ -d $(PKG_NAME)-$(PKG_VERN) ]; then \
	time make -C $(WORK_DIR) ARCH=$(CPU_ARCH) \
	    KERNDIR=$(DEB_BLDIR) UPSTREAMDIR=$(KERN_SRC) \
	    DEBUG_CFLAGS="-DSDK_COMMAND_IO_VER=1" SDK_COMMAND_IO_VER=1 \
	    ADJ_PHY_SERDES=1 \
	    MAKE_PAR="$(MAKE) -j $(MAKE_JOBS)" \
	    2>&1 | tee $(PKG_NAME).log; \
	cp $(WORK_DIR)/*.ko .;\
	cp $(WORK_DIR)/bcm.user .;\
	fi

.PHONY: config
config: patch

.PHONY: patch
patch:
ifeq ("$(PKG_VERN)","6.4.6")
	echo "$(PKG_VERN)"
	@if [ ! -d $(PKG_NAME)-$(PKG_VERN) ] && [ -f $(PKG_NAME)-$(PKG_VERN).tar.gz ] ; then \
	    tar -zxvf $(PKG_NAME)-$(PKG_VERN).tar.gz; \
	    ./make.local.sh $(PKG_NAME)-$(PKG_VERN); \
	    cd $(PKG_NAME)-$(PKG_VERN); \
	    patch -p1 < ../patches/0001_debian_linux_3_16-$(PKG_VERN).patch; \
	    patch -p1 < ../patches/0002_feat_dep_fixup-$(PKG_VERN).patch; \
	    patch -p1 < ../patches/0003_cmdio-$(PKG_VERN).patch; \
	    patch -p1 < ../patches/0004_serdes_tuner-$(PKG_VERN).patch; \
	    patch -p1 < ../patches/0005_phy_raw_modify_cmd-$(PKG_VERN).patch; \
	    patch -p1 < ../patches/0006_stamp_sdk_ready-$(PKG_VERN).patch; \
	    patch -p1 < ../patches/0007_cmd_tx_fixup-$(PKG_VERN).patch; \
	    patch -p1 < ../patches/0008_led_cp_program-$(PKG_VERN).patch; \
	    patch -p1 < ../patches/0009_led_dp_program-$(PKG_VERN).patch; \
	fi
endif

.PHONY: install
install:
ifneq ("$(wildcard $(WORK_DIR)/bcm.user)","")
	@echo "SDK Version\t: $(PKG_NAME) $(PKG_VERN)" >> $(INST_DIR)/boot/version
	mkdir -p $(INST_DIR)/opt/$(PKG_NAME)
	cp -f *.ko $(INST_DIR)/opt/$(PKG_NAME)/
	cp -f bcm.user $(INST_DIR)/opt/$(PKG_NAME)/
	cp $(CURDIR)/$(PKG_NAME)-$(PKG_VERN)/tools/bcmsh/bcmsh $(INST_DIR)/opt/$(PKG_NAME)/
	cp $(CURDIR)/$(PKG_NAME)-$(PKG_VERN)/tools/phy/adj_trident $(INST_DIR)/opt/$(PKG_NAME)/
	cp $(CURDIR)/$(PKG_NAME)-$(PKG_VERN)/tools/phy/adj_trident2 $(INST_DIR)/opt/$(PKG_NAME)/
	cd rc; tar --exclude=.svn -f - -c * | tar -C $(INST_DIR)/opt/$(PKG_NAME) -f - -x
	cd $(INST_DIR)/opt/$(PKG_NAME); ln -sf rc.soc-$(PKG_VERN) rc.soc
endif

.PHONY: uninstall
uninstall:
ifneq ("$(wildcard $(INST_DIR)/opt/$(PKG_NAME)/bcm.user)","")
	rm -rf $(INST_DIR)/opt/$(PKG_NAME)
endif

.PHONY: clean
clean:
	rm $(CURDIR)/$(PKG_NAME)-$(PKG_VERN)/tools/bcmsh/bcmsh
	rm $(CURDIR)/$(PKG_NAME)-$(PKG_VERN)/tools/phy/adj_trident
	rm $(CURDIR)/$(PKG_NAME)-$(PKG_VERN)/tools/phy/adj_trident2
	rm -rf $(PKG_NAME)-$(PKG_VERN)/build
	rm -f $(filter %Makefile,$(wildcard $(WORK_DIR)/*))

.PHONY: distclean
distclean:
	rm -rf $(PKG_NAME)-$(PKG_VERN)
	rm -f $(PKG_NAME).log

