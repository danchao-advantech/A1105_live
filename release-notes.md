
**ESP-9010 live build release-notes**

[2018/01/25]

1. Re-upload whole image "esp-9010_lmp_esw_v00_06.src.tar.bz2" split by 10 files to *images* directory. It is a better way to avoid of  software version issue that will cause "make image" fail.
2. re-write **README.md**.

[2018/01/24]

1. Remove *live-cache.tar.bz2* from *esp-9010_lmp_esw_v00_06* directory.
2. Split *linux-source-3.16.0.tar.bz2* into two parts and get them back together before make image.

