# ESP-9010 Debian Live System Building Environment Guide

## Getting Started

These instructions will show you how to build a A1105 live image in Debian 8.1 (jessie) quickly.
Please refer to [ESP-9010 Debian Live System Building Environment Guide v0.1.pdf](https://github.com/danchao-advantech/A1105_live/blob/master/ESP-9010%20Debian%20Live%20System%20Building%20Environment%20Guide%20v0.1.pdf) for other detail.


### Prerequisites

* [ESP-9010 Debian Live System Building Environment Guide v0.1.pdf](https://github.com/danchao-advantech/A1105_live/blob/master/ESP-9010%20Debian%20Live%20System%20Building%20Environment%20Guide%20v0.1.pdf) (Abbreviations: "*9010-live-UG*")
* esp-9010_lmp_esw_v00_06 directory (git clone https://github.com/danchao-advantech/A1105_live)
* [install_D8.sh](https://github.com/danchao-advantech/A1105_live/blob/master/install_D8.sh)


### Installing

Please install Debian 8.1 amd64 standard in server (image: [debian-live-8.1.0-amd64-standard.iso](http://cdimage.debian.org/mirror/cdimage/archive/8.1.0-live/amd64/iso-hybrid/debian-live-8.1.0-amd64-standard.iso)) that is 
a suitable platform for A1105 live build.  Internet network access is necessary too. 


In Debian 8.1
- Login:    root / user
- password: (...)


Login debian 8.1 with root

```
apt-get install sudo
chmod u+w /etc/sudoers
visudo
	> #add "user" to root privilege
	> user	ALL=(root) NOPASSWD:ALL
chmod u-w /etc/sudoers
logout
```


Login debian 8.1 with user

```
chmod 666 .Xauthority
uname -r
	> 3.16.0-4-amd64
cat /etc/*-release
	> PRETTY_NAME="Debian GNU/Linux 8 (jessie)"
```


Update source.list

> 9010-live-UG, page10

Set up the stable repository (jessie)
```
sudo nano /etc/apt/sources.list
	#add two source download list at first two line
	- deb cdrom:[Debian GNU/Linux 8 _Jessie_ - Official Snapshot amd64 LIVE/INSTALL Binary 20150606-14:41]/ jessie main
	+ deb http://http.debian.net/debian jessie main contrib non-free 
	+ deb-src http://http.debian.net/debian jessie main contrib non-free 
	+ deb http://apt.dockerproject.org/repo debian-jessie main
	+ deb http://http.debian.net/debian jessie main contrib non-free
	+ deb http://httpredir.debian.org/debian jessie main
	+ deb-src http://httpredir.debian.org/debian jessie main
	+ deb http://httpredir.debian.org/debian jessie-updates main
	+ deb-src http://httpredir.debian.org/debian jessie-updates main
	+ deb http://security.debian.org/ jessie/updates main
	+ deb-src http://security.debian.org/ jessie/updates main
```	


apt-get update and general packages install

```
sudo apt-get update -y
sudo apt-get install -y debootstrap syslinux isolinux squashfs-tools
sudo apt-get install -y genisoimage memtest86+ rsync nano vim git
```


Get 9010 image source from GitHub, move/rename "*esp-9010_lmp_esw_v00_06*" directory to **$HOME/live-image/esp-9010** and merge linux source files.

```
cd $HOME
git clone https://github.com/danchao-advantech/A1105_live
mkdir -p $HOME/live-image
mv $HOME/A1105_live/esp-9010_lmp_esw_v00_06 $HOME/live-image/esp-9010
cd $HOME/live-image/esp-9010
ls
	> auto    linux-source-3.16.0.tar.bz2.partaa  Makefile          src
	> config  linux-source-3.16.0.tar.bz2.partab  persistence.conf  version
cat linux-source-3.16.0.tar.bz2.part* > linux-source-3.16.0.tar.bz2
mv linux-source-3.16.0.tar.bz2 src/linux-kernel
rm linux-source-3.16.0.tar.bz2.part*
```


Install packages for live build

> 9010-live-UG, page10

```
sudo apt-get install -y build-essential linux-headers-`uname -r`
sudo apt-get build-dep -y linux
sudo apt-get install -y live-build live-boot live-config
sudo apt-get install -y libncurses5-dev
sudo apt-get install -y libc6-dev-i386
sudo apt-get install -y fakeroot kernel-package
sudo apt-get install -y iconx
sudo apt-get install -y noweb 
sudo apt-get install -y nowebm 
sudo apt-get install -y usbutils
sudo apt-get install -y zlib1g-dev libftdi-dev libusb-dev libftdi1 libpci-dev
sudo apt-get install -y ecryptfs-utils
sudo apt-get install -y doxygen 
sudo apt-get install -y autoconf 
sudo apt-get install -y libssl-dev
```


Install packages for gcc4.8 

> 9010-live-UG, page11

```
sudo apt-get install -y gcc-4.8-multilib
sudo apt-get install -y g++-4.8-multilib
	> Change gcc from 4.9 to 4.8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 30
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 40
sudo update-alternatives --config gcc 
	> type selection change to "1"
```


Remove unused/out-of-date packages 

> 9010-live-UG, page11

```
sudo apt-get autoclean
sudo apt-get autoremove 
dpkg --get-selections | grep linux
sudo update-pciids
sudo update-usbids
```


Modify script for live build

> 9010-live-UG, page15

```
sudo nano /usr/lib/live/build/binary_hdd
	#SEARCH "if=chroot/usr/lib"
	- dd if=chroot/usr/lib/${_BOOTLOADER}/mbr.bin of=${FREELO} bs=440 count=1 
	+ dd if=chroot/usr/lib/SYSLINUX/mbr.bin of=${FREELO} bs=440 count=1 
	#SEARCH "umount chroot/binary.tmp"
	+ sync; sync; sync; sync; sync
	  umount chroot/binary.tmp 
```


Navigate all available packages first by executing “apt-cache dumpavail” in the host system. 

> 9010-live-UG, page5

```
apt-cache dumpavail
```


### live-build process

> 9010-live-UG, page6

Build live image

```
cd $HOME/live-image/esp-9010
make disclean
make all
	> ~ 30 min
make imgclean
make image
	> ~ 30 min
```


A new live image "*live-image-amd64*" (934Mb) be generated in **$HOME/live-image/esp-9010** directory.

```
cd $HOME/live-image/esp-9010
ls -al
```


Copy *live-image-amd64* to *A1105_lmp_esw_v00_0X.img*(Home dir)

```
cp live-image-amd64 $HOME/A1105_lmp_esw_v00_0X.img
cd $HOME
ls -al
```


Finally, create a live USB drive (/dev/sdf) by "*A1105_lmp_esw_v00_0X.img*" and [install_D8.sh](https://github.com/danchao-advantech/A1105_live/blob/master/install_D8.sh)!

```
cp $HOME/A1105_live/install_D8.sh $HOME
cd $HOME
chmod 777 ./install_D8.sh
./install_D8.sh -f A1105_lmp_esw_v00_0X.img -d /dev/sdf
```


### done!

*AB.Huang*
ab.huang@advantech.com.tw


