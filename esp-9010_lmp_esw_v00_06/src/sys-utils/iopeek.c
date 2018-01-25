 /*
 **********************************************************************
 *
 * @filename  iopeek.c
 *
 * @purpose   add support of MEMIO and PORTIO utilities
 *
 * @create    2014/12/25
 *
 * @author    eric lin <eric.lin@advantech.com.tw>
 *
 * @history   2014/12/25: init version
 *
 **********************************************************************
 */
/*
 * $Copyright: Copyright 1983-2015 Advantech Co., Ltd.
 * This program is the proprietary software of Advantech Corporation
 * and/or its licensors, and may only be used, duplicated, modified
 * or distributed pursuant to the terms and conditions of a separate,
 * written license agreement executed between you and Advantech
 * (an "Authorized License").  Except as set forth in an Authorized
 * License, Advantech grants no license (express or implied), right
 * to use, or waiver of any kind with respect to the Software, and
 * Advantech expressly reserves all rights in and to the Software
 * and all intellectual property rights therein.  IF YOU HAVE
 * NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE
 * IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY ADVANTECH AND DISCONTINUE
 * ALL USE OF THE SOFTWARE.  
 *
 * Except as expressly set forth in the Authorized License,
 *
 * 1.     THIS PROGRAM, INCLUDING ITS STRUCTURE, SEQUENCE AND ORGANIZATION,
 * CONSTITUTES THE VALUABLE TRADE SECRETS OF ADVANTECH, AND YOU SHALL USE
 * ALL REASONABLE EFFORTS TO PROTECT THE CONFIDENTIALITY THEREOF,
 * AND TO USE THIS INFORMATION ONLY IN CONNECTION WITH YOUR USE OF
 * ADVANTECH PRODUCTS.
 *
 * 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS
 * PROVIDED "AS IS" AND WITH ALL FAULTS AND ADVANTECH MAKES NO PROMISES,
 * REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
 * OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  ADVANTECH SPECIFICALLY
 * DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
 * NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
 * ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
 * OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *
 * 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
 * ADVANTECH OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL,
 * INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER
 * ARISING OUT OF OR IN ANY WAY RELATING TO YOUR USE OF OR INABILITY
 * TO USE THE SOFTWARE EVEN IF ADVANTECH HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF
 * THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR USD 1.00,
 * WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING
 * ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.
 *
 * 4.     REDISTRIBUTIONS IN BINARY FORM MUST REPRODUCE BELOW COPYRIGHT NOTICS
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

void usage()
{
        printf("Dump reg values for specific IO address.\n");
        printf("Usage\t: iopeek hex_addr\n");
        printf("Example\t: iopeek 0x500\n");
        return;
}

int main(int argc, char *argv[])
{
	int fd = -1;
	int i, j;
	unsigned char data;
	int addr = 0;

	if (argc == 2 && strncmp(argv[1], "0x", 2) == 0) {
        	addr = strtol(argv[1], NULL, 0);
	} else {
        	usage();
        	return 0;
	}


	fd = open("/dev/port",O_RDWR|O_NDELAY);
	if ( fd < 0 ) {
        	printf("Failed to open /dev/port. Are you root?\n");
	        return fd;
	}


	printf("BASE: 0x%.4X\n", addr);
	lseek(fd, addr, SEEK_SET);
	printf("00  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	for (i = 0; i < 16; i++) {
		printf("%X0  ", i);
		for (j = 0; j < 16; j++) {
			read(fd, &data,1);
			printf("%.2X ", data);
			addr++;
			lseek(fd, addr, SEEK_SET);
		}
		printf("\n");
	}

    	return 0;
}

