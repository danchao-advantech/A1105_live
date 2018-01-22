# ESP-9010 Debian Live System Building Environment Guide

## Getting Started

These instructions will show you how to build a A1105 live image in Debian 8.1 (jessie) quickly.
Please refer to [ESP-9010 Debian Live System Building Environment Guide v0.1.pdf](https://github.com/danchao-advantech/A1105_live/blob/master/ESP-9010%20Debian%20Live%20System%20Building%20Environment%20Guide%20v0.1.pdf) for other detail.

### Prerequisites

* [ESP-9010 Debian Live System Building Environment Guide v0.1.pdf](https://github.com/danchao-advantech/A1105_live/blob/master/ESP-9010%20Debian%20Live%20System%20Building%20Environment%20Guide%20v0.1.pdf) (Abbreviations: "*9010-live-UG*")
* esp-9010_lmp_esw_v00_06b.src.tar.bz2
* [install_D8.sh](https://github.com/danchao-advantech/A1105_live/blob/master/install_D8.sh)

### Installing

Please install Debian 8.1 amd64 standard in server (image:[debian-live-8.1.0-amd64-standard.iso](http://cdimage.debian.org/mirror/cdimage/archive/8.1.0-live/amd64/iso-hybrid/debian-live-8.1.0-amd64-standard.iso)) that is 
a suitable platform for A1105 live build.  Internet network access is necessary too. 

In Debian 8.1
- Login:    root / user
- password: (...)

#### Login debian 8.1 with root

```
apt-get install sudo
chmod u+w /etc/sudoers
visudo
	> #add "user" to root privilege
	> user	ALL=(root) NOPASSWD:ALL
chmod u-w /etc/sudoers
logout
```

#### Login debian 8.1 with user

```
chmod 666 .Xauthority
uname -r
	> 3.16.0-4-amd64
cat /etc/*-release
	> PRETTY_NAME="Debian GNU/Linux 8 (jessie)"
```

#### Prepare for 9010 image

```
mkdir $HOME/live-image
```
Please copy "esp-9010_lmp_esw_v00_06.src.tar.bz2" to $HOME directory by winSCP or USB drive.
```
mv esp-9010_lmp_esw_v00_06.src.tar.bz2 $HOME/live-image
cd $HOME/live-image
tar xf esp-9010_lmp_esw_v00_06.src.tar.bz2
mv  esp-9010_lmp_esw_v00_06  esp-9010
mv esp-9010_lmp_esw_v00_06.src.tar.bz2 $HOME
cd $HOME/live-image/esp-9010
ls
	> auto/  config/  live-cache.tar.bz2  Makefile  persistence.conf  src/  version
```

#### General packages

```
sudo apt-get update -y
sudo apt-get install -y debootstrap syslinux isolinux squashfs-tools
sudo apt-get install -y genisoimage memtest86+ rsync nano vim
```

#### Update source.list

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
sudo apt-get update
```	

#### Install packages for live-build

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

#### Install packages for gcc4.8 

> 9010-live-UG, page11

```
sudo apt-get install -y gcc-4.8-multilib
sudo apt-get install -y g++-4.8-multilib
	> Change gcc from 4.9 to 4.8
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 30
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 40
sudo update-alternatives --config gcc 
```

>  Selection    Path              Priority   Status
------------------------------------------------------------
* 0            /usr/bin/gcc-4.9   40        auto mode
  1            /usr/bin/gcc-4.8   30        manual mode
  2            /usr/bin/gcc-4.9   40        manual mode
==> type selection number: 1

