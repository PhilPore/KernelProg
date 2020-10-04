#include <linux/module.h> /*essential for all modules. This are processes the kernel loads up, making the kernel less monolithic.*/
#include <linux/kernel.h>


int init_module(void)
{
    printk(KERN_INFO "Hello world 1.\n");

    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Goodbye World 1.\n");

}