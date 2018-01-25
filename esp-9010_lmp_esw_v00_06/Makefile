KERN_MAJ  := 3.16.0
KERN_MIN  := 4-amd64
WORK_DIR  := $(CURDIR)
PACKAGES  := linux-kernel igb-driver sdk-xgs-robo ifupdown memtest86+ lfdk sys-utils fastpath fastpath2

# examine input package keyword
FIND_PKG  = $(if $(findstring $(1),$(wildcard $(WORK_DIR)/src/$(1))),,\
	$(error "$(WORK_DIR)/src/$(1) does not exist"))
$(foreach pkg,$(PACKAGES),$(call FIND_PKG,$(pkg)))

# export global variables
export KERN_VER := $(KERN_MAJ)-$(KERN_MIN)
export KERN_SRC := $(WORK_DIR)/src/linux-kernel/linux-source-$(KERN_MAJ)
export INST_DIR := $(WORK_DIR)/config/includes.chroot
export IMG_LIVE_DIR := $(WORK_DIR)/binary/live
export INST_PKG_DIR := $(WORK_DIR)/config/packages.chroot
export CPU_ARCH := x86_64
export DEB_ARCH := amd64
export DEB_FEAT := none
export DEB_FLAVOURS := amd64

.PHONY: all
all:
	@for PKG in $(PACKAGES); do \
	    echo "******************** build $$PKG ********************"; \
	    make -C $(WORK_DIR)/src/$$PKG; \
	done

.PHONY: image
image:
	mkdir -p $(INST_DIR)/boot
	echo -n "Release Version : " > $(INST_DIR)/boot/version;
	cat version >> $(INST_DIR)/boot/version;
	echo -n "SVN Revsion\t: " >> $(INST_DIR)/boot/version; 
	@svn info 1>/dev/null 2>/dev/null; \
	if [ $$? -eq 0 ]; then \
	    echo -n "r" >> $(INST_DIR)/boot/version; \
	    svn info | grep "Changed Rev" | cut -d ' '  -f 4 >> $(INST_DIR)/boot/version; \
	else \
	    echo "N/A" >> $(INST_DIR)/boot/version; \
	fi
	@for PKG in $(PACKAGES); do \
	    echo "******************** install $$PKG ********************"; \
	    make -C $(WORK_DIR)/src/$$PKG uninstall; \
	    make -C $(WORK_DIR)/src/$$PKG install; \
	done
	@echo -n "Build Date\t: " >> $(INST_DIR)/boot/version
	@date "+%Y-%m-%d %T %z" >> $(INST_DIR)/boot/version
	@echo "******************** build live system ********************"
	@sudo rm -rf cache
	@if [ -e live-cache.tar.bz2 ]; then \
	    sudo tar -jxvf live-cache.tar.bz2; \
	fi
	sudo depmod -b $(INST_DIR) -a
	sudo lb clean
	@if [ -e live-image-amd64 ]; then \
	    sudo rm live-image-amd64; \
	fi
	lb config -b hdd
	sudo time lb build
	@if [ -f live-image-amd64 ]; then \
		mkdir -p mnt; \
		OFFSET=`grep offset build.log | tail -n 1 | rev | cut -d ' ' -f 1 | rev`; \
		sudo mount -o loop,offset=$$OFFSET live-image-amd64 mnt; \
		if [ $$? -eq 0 ]; then \
			sudo rm -f mnt/.dummy; sync; sync; sync; \
			sudo umount mnt; \
		fi; \
		rm -rf mnt; \
	fi
	sudo cp $(INST_DIR)/boot/version $(IMG_LIVE_DIR)

.PHONY: iso
iso:
	mkdir -p $(INST_DIR)/boot
	@svn info 1>/dev/null 2>/dev/null; \
	if [ $$? -eq 0 ]; then \
	    echo -n "SVN Revsion\t: r" > $(INST_DIR)/boot/version; \
	    svn info | grep "Changed Rev" | cut -d ' '  -f 4 >> $(INST_DIR)/boot/version; \
	else \
	    rm -f $(INST_DIR)/boot/version; \
	    touch $(INST_DIR)/boot/version; \
	fi
	@for PKG in $(PACKAGES); do \
	    echo "******************** install $$PKG ********************"; \
	    make -C $(WORK_DIR)/src/$$PKG uninstall; \
	    make -C $(WORK_DIR)/src/$$PKG install; \
	done
	@echo -n "Build Date\t: " >> $(INST_DIR)/boot/version
	@date "+%Y-%m-%d %T %z" >> $(INST_DIR)/boot/version
	@echo "******************** build live system ********************"
	@sudo rm -rf cache
	@if [ -e live-cache.tar.bz2 ]; then \
	    sudo tar -jxvf live-cache.tar.bz2; \
	fi
	sudo depmod -b $(INST_DIR) -a
	sudo lb clean
	lb config -b iso
	sudo time lb build

.PHONY: reimage
reimage:
	sudo time lb build
	mkdir -p mnt
	OFFSET=`grep offset build.log | tail -n 1 | rev | cut -d ' ' -f 1 | rev`
	sudo mount -o loop,offset=$$OFFSET live-image-amd64 mnt
	if [ $$? -eq 0 ]; then
	   sudo rm -f mnt/.dummy; sync; sync; sync
	   sudo umount mnt
	fi;
	   rm -rf mnt

.PHONY: imgclean
imgclean:
	@for PKG in $(PACKAGES); do \
	    echo "******************** uninstall $$PKG ********************"; \
	    make -C $(WORK_DIR)/src/$$PKG uninstall; \
	done
	rm -rf $(INST_DIR)/boot
	sudo rm -f live-image-amd64.*

.PHONY: install
install:
	@if [ -z $(DEVICE) ]; then \
	    echo "Usage: make install DEVICE=/dev/sdX"; \
	    return 1; \
	fi
	@echo "******************** install live system ********************"
	$(shell sudo umount $(DEVICE) 2>/dev/null)
	$(shell sudo umount $(DEVICE)1 2>/dev/null)
	$(shell sudo umount $(DEVICE)2 2>/dev/null)
	sudo dd if=live-image-amd64 of=$(DEVICE) bs=4096
	@sync; sync; sync; sync; sync
	(echo n;echo p;echo 2;echo '';echo '';echo t;echo 2;echo 83;echo w) | sudo fdisk $(DEVICE)
	sleep 1
	@sync; sync; sync; sync; sync
	(echo y) | sudo mkfs.ext4 -L persistence $(DEVICE)2
	sudo mount -t ext4 $(DEVICE)2 /mnt
	sudo cp persistence.conf /mnt/persistence.conf
	@sync; sync; sync; sync; sync
	sudo umount /mnt

.PHONY: clean
clean:
	@for PKG in $(PACKAGES); do \
	    echo "******************** clean $$PKG ********************"; \
	    make -C $(WORK_DIR)/src/$$PKG clean; \
	done

.PHONY: distclean
distclean:
	@for PKG in $(PACKAGES); do \
	    echo "******************** distclean $$PKG ********************"; \
	    make -C $(WORK_DIR)/src/$$PKG distclean uninstall; \
	done
	sudo lb clean --purge
	rm -rf $(INST_DIR)/boot
	sudo rm -rf .build local
	sudo rm -f binary.contents chroot.packages.install chroot.packages.live

.PHONY: $(PACKAGES)
$(PACKAGES):
	@make $@.all

.PHONY: %.all
%.all:
	$(call FIND_PKG,$*)
	@echo "******************** build $* ********************"
	@make -C $(WORK_DIR)/src/$* all

.PHONY: %.install
%.install:
	$(call FIND_PKG,$*)
	@echo "******************** install $* ********************"
	@make -C $(WORK_DIR)/src/$* install

.PHONY: %.uninstall
%.uninstall:
	$(call FIND_PKG,$*)
	@echo "******************** uninstall $* ********************"
	@make -C $(WORK_DIR)/src/$* uninstall

.PHONY: %.clean
%.clean:
	$(call FIND_PKG,$*)
	@echo "******************** clean $* ********************"
	@make -C $(WORK_DIR)/src/$* clean

.PHONY: %.distclean
%.distclean:
	$(call FIND_PKG,$*)
	@echo "******************** distclean $* ********************"
	@make -C $(WORK_DIR)/src/$* distclean

.PHONY: %.config
%.config:
	$(call FIND_PKG,$*)
	@echo "******************** config $* ********************"
	@make -C $(WORK_DIR)/src/$* config

.PHONY: %.patch
%.patch:
	$(call FIND_PKG,$*)
	@echo "******************** patch $* ********************"
	@make -C $(WORK_DIR)/src/$* patch


.PHONY: %.rebuild
%.rebuild:
	$(call FIND_PKG,$*)
	@echo "******************** rebuild $* ********************"
	@make -C $(WORK_DIR)/src/$* distclean
	@make -C $(WORK_DIR)/src/$* all

