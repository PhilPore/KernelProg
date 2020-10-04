#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#define DRIVER_AUTH "Philip Poretsky <pporetsky@gmail.com/ptp24@njit.edu>"
#define DRIVER_DESC "Some testing!"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTH);

static char *name = "Bo Derrick";
static char *street = "1111";
static char *city = "This city";
static int zip = 1;
module_param(name, charp, 0000);
module_param(street, charp, 0000);
module_param(city,charp,0000);
module_param(zip,int,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
/*Note when passing a string parameter with  '' before the "" this is for the kernel to translate it as a string with spaces. What the hell*/
static int __init start_innit(void){
    printk(KERN_INFO "Hello World 3\n=================\n");
    printk(KERN_INFO "Name: %s\nStreet: %s\nCity: %s\nZIP: %d\n",name,street,city,zip);
    return 0;
}

static void __exit die_start(void){
    printk(KERN_INFO "Take care!\n");
}

module_init(start_innit);
module_exit(die_start);



MODULE_DESCRIPTION(DRIVER_DESC);

MODULE_SUPPORTED_DEVICE("testdevice");