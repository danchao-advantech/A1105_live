PKG_NAME   := $(shell basename $(KERN_SRC))
KERN_MAJ   := $(shell echo $(KERN_VER) | cut -d "-" -f 1)
CPU_CORES  := $(shell cat /proc/cpuinfo | grep "core id" | wc -l)
MAKE_JOBS  := $(shell expr $(CPU_CORES) + 1)
DEB_PKG    := $(DEB_ARCH)_$(DEB_FEAT)_$(DEB_FLAVOURS)
LOG_FILE   := $(shell basename $(CURDIR))

.PHONY: all
all: patch
	@if [ "$(wildcard $(PKG_NAME)/debian/stamps/build_*)" != "" ]; then \
	    rm -f $(wildcard $(PKG_NAME)/debian/stamps/build_*); \
	fi
	cd $(PKG_NAME); \
	time make -f debian/rules.gen binary-arch_$(DEB_PKG) \
	    MAKEFLAGS="$(MAKEFLAGS) -j$(MAKE_JOBS)" 2>&1 | tee ../$(LOG_FILE).log

config: patch
	make -C $(PKG_NAME)/debian/build/build_$(DEB_PKG) menuconfig
	@if [ -f $(PKG_NAME)/debian/build/build_$(DEB_PKG)/.config.old ]; then \
	    rm -f $(PKG_NAME)/debian/build/build_$(DEB_PKG)/.config.old; \
	    mv $(PKG_NAME)/debian/build/build_$(DEB_PKG)/.config kernel-$(KERN_MAJ)-$(CPU_ARCH).config; \
	    ln -s $(KERN_SRC)/../kernel-$(KERN_MAJ)-$(CPU_ARCH).config $(PKG_NAME)/debian/build/build_$(DEB_PKG)/.config; \
	fi

.PHONY: patch
patch:
	@if [ ! -d $(PKG_NAME) ]; then \
	    tar -jxvf $(PKG_NAME).tar.bz2; \
	    cd $(PKG_NAME); \
	    sed -i 's/python debian\/bin\/buildcheck.py/#python debian\/bin\/buildcheck.py/g' debian/rules.real; \
	    fakeroot make -f debian/rules.gen source_none 2>&1 | tee ../$(LOG_FILE)_deb_source.log; \
	    fakeroot make -f debian/rules.gen setup_$(DEB_PKG) 2>&1 | tee ../$(LOG_FILE)_deb_setup.log; \
	    rm -f debian/build/build_$(DEB_PKG)/.config; \
	    ln -s $(KERN_SRC)/../kernel-$(KERN_MAJ)-$(CPU_ARCH).config debian/build/build_$(DEB_PKG)/.config; \
	    patch -p1 < ../patches/0001_debian_builder-$(KERN_MAJ).patch; \
	    patch -p1 < ../patches/0002_esp9010_i2c_devices-$(KERN_MAJ).patch; \
	    patch -p1 < ../patches/0003_fastpath_routing-$(KERN_MAJ).patch; \
	fi

.PHONY: install
install:
ifneq ("$(wildcard $(KERN_SRC)/debian/build/build_$(DEB_PKG)/arch/$(CPU_ARCH)/boot/bzImage)","")
	@if [ -f $(INST_DIR)/boot/version ]; then \
	    echo "Kernel Version\t: $(KERN_VER)" >> $(INST_DIR)/boot/version; \
	fi
	mkdir -p $(INST_DIR)/boot
	mkdir -p $(INST_DIR)/lib
	install -D -m 644 $(KERN_SRC)/debian/linux-image-$(KERN_VER)/boot/vmlinuz-$(KERN_VER) $(INST_DIR)/boot/
	install -D -m 644  $(KERN_SRC)/debian/linux-image-$(KERN_VER)/boot/System.map-$(KERN_VER) $(INST_DIR)/boot/
	install -D -m 644 $(KERN_SRC)/debian/linux-image-$(KERN_VER)/boot/config-$(KERN_VER) $(INST_DIR)/boot/
	cp -a $(KERN_SRC)/debian/linux-image-$(KERN_VER)/lib/modules $(INST_DIR)/lib/
endif

.PHONY: uninstall
uninstall:
ifneq ("$(wildcard $(INST_DIR)/boot/vmlinuz-$(KERN_VER))","")
	rm -f $(INST_DIR)/boot/vmlinuz-$(KERN_VER)
	rm -f $(INST_DIR)/boot/System.map-$(KERN_VER)
	rm -f $(INST_DIR)/boot/config-$(KERN_VER)
	rm -rf $(INST_DIR)/lib/modules
endif

.PHONY: clean
clean:
ifneq ("$(wildcard $(PKG_NAME))","")
	cd $(PKG_NAME); \
	fakeroot debian/rules clean
endif

.PHONY: distclean
distclean:
	rm -rf $(KERN_SRC)
	rm -f *.log

