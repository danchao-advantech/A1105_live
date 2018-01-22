# ESP-9010 Debian Live System Building Environment Guide

## Getting Started

These instructions will show you how to build a A1105 live image in Debian 8.1 (jessie) quickly.
Please refer to "***ESP-9010 Debian Live System Building Environment Guide v0.1.pdf***" for other detail.

### Prerequisites

* ESP-9010 Debian Live System Building Environment Guide v0.1.pdf (Abbreviations: "*9010-live-UG*")
* esp-9010_lmp_esw_v00_06b.src.tar.bz2
* install_D8.sh

### Installing

Please install Debian 8.1 amd64 standard in server(ref. **debian-live-8.1.0-amd64-standard.iso**) that is 
a suitable platform for A1105 live build.  Internet network access is necessary too. 

In Debian 8.1
- Login:    root / user
- password: (...)

#### Login debian 8.1 with root

```
apt-get install sudo
chmod u+w /etc/sudoers
visudo
	> # add "user" to root privilege
	> user	ALL=(root) NOPASSWD:ALL
chmod u-w /etc/sudoers
```
