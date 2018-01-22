#!/bin/bash

display_usage() { 
	printf "Usage: install [-options] values\n" 
	printf "where options include:\n"
	printf "\t-f\t Where the image file locates at. ex. /mnt/ImageFile/binary.img\n"
	printf "\t-d\t Which drive you want to install the image: ex. /dev/sdb\n"  
	printf "Example Usage:\n" 
	printf "\t\t ./install_D7.sh -f /mnt/ImageFile/binary.img -d /dev/sdb\n"
}

while getopts f:d: option
do
        case "${option}"
        in
			f) FILE=${OPTARG} ;;
            d) DEVICE=${OPTARG};;
			*) display_usage; exit 2;;
        	\?) display_usage; exit 2;;
		
        esac
done

shift $((OPTIND-1))

if [ -z ${FILE} ]; then
            display_usage;
            exit 1;
fi


if [ -z ${DEVICE} ]; then 
	    display_usage; 
	    exit 1; 
fi
echo "******************** install live system ********************"
sudo umount ${DEVICE} 2>/dev/null
sudo umount ${DEVICE}1 2>/dev/null
sudo umount ${DEVICE}2 2>/dev/null
sudo dd if=${FILE} of=${DEVICE} bs=10M
num=$(sudo fdisk -l | grep ${DEVICE}1 | awk '{print $4}')
startc=$((num+1))
sudo echo -e "n\np\n2\n${startc}\n\nt\n2\n83\nw\n" | sudo /sbin/fdisk ${DEVICE}
sudo mkfs.ext4 -L "persistence" ${DEVICE}2
sync; sync; sync; sync; sync

sudo mount -t ext4 ${DEVICE}2 /mnt
echo "/ union" | sudo tee -a /mnt/persistence.conf
sync; sync; sync; sync; sync
sudo umount /mnt
