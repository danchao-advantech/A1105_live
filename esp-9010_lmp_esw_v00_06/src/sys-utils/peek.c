 /*
 **********************************************************************
 *
 * @filename  peek.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define  LINE_LENGTH  16

void print_4byte(void* data)
{
  unsigned int*  val = data;
  printf("%08x ", *val);
}

void print_2byte(void* data)
{
  unsigned short*  val = data;
  printf("%04x ", *val);
}

void print_1byte(void* data)
{
  unsigned char*  val = data;
  printf("%02x ", *val);
}

int main(int argc, char** argv)
{
  void                     (*print_data)(void* data) = print_4byte;
  int                      size   = 4;
  int                      len    = 1;
  unsigned int             addr;
  int                      opt;
  unsigned int             block;
  unsigned int             offset;
  int                      page;
  int                      mfd;
  char*                    mem;
  volatile unsigned char*  data;

  if (argc < 2)
  {
    printf("%s [-l|-w|-b] hexaddress [length]\n", argv[0]);
    exit(1);
  }

  while ((opt = getopt(argc, argv, "lwb")) != -1)
  {
    switch (opt)
    {
      case 'l': break;
      case 'w': size = 2;
                print_data = print_2byte; 
                break;
      case 'b': size = 1;
                print_data = print_1byte;
                break;
      default : printf("%s [-l|-w|-b] hexaddress [length]\n", argv[0]);
                exit(1);
    }
  }

  if (strncmp(argv[optind], "0x", 2)) opt = 0;
  else opt = 2;
  sscanf(argv[optind++] + opt, "%08x", &addr);

  if (optind < argc) 
  {
    if (strncmp(argv[optind], "0x", 2)) sscanf(argv[optind], "%d", &len);
    else sscanf(argv[optind] + 2, "%x", &len);
  }
 
  block  = addr / getpagesize() * getpagesize();
  offset = addr - block; 
  page   = size * len / getpagesize() + 1;

  if ((mfd = open("/dev/mem", O_RDWR)) < 0)
  if (mfd < 0)
  {
    perror("Failed to open /dev/mem");
    exit(1);
  }
  mem = mmap(0, getpagesize() * page, PROT_READ|PROT_WRITE, MAP_SHARED,
             mfd, block);
  data = mem + offset;

  block = LINE_LENGTH / size;
  for (offset = 0; offset < len; offset++)
  {
    if (offset % block == 0) printf("\n%08x:  ", addr + offset * size);
    print_data((void*)data);
    data = data + size;
  } 
  printf("\n");

  close(mfd);

  return 0;
}

