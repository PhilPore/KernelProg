#include <linux/module.h> /*essential for all modules. This are processes the kernel loads up, making the kernel less monolithic.*/
#include <linux/kernel.h>
#include <linux/init.h>


static int hewwo __initdata = 2;
static int byee __exitdata = 42;
static int __init hello2_init(void)
{
    printk(KERN_INFO "Hello world 2.\n");
    printk(KERN_INFO "Have a number: %d\n", hewwo);

    return 0;
}

static void __exit hello2_exit(void)
{
    printk(KERN_INFO "Goodbye World 2.\n");
    printk(KERN_INFO "The answer to all questions is %d\n", byee);

}
module_init(hello2_init);
module_exit(hello2_exit);