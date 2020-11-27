This kernel module recreates buddyinfo. Do note, most of this (line 11-113) is directly taken from mmzone.c in the linux kernel. While I tried to grab it from the kernel via an include, the compiler wanted none of that. Anywho, enjoy! Look at dmesg for added colour.

Run that make file, then do a

sudo insmod budinf.ko

to remove it:

sudo rmmod budinf
