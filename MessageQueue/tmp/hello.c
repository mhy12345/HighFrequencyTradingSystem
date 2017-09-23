#include <linux/kernel.h> /*Needed by all modules*/
#include <linux/module.h> /*Needed for KERN_* */
#include <linux/init.h> /* Needed for the macros */

MODULE_LICENSE("GPL");

static int year=2014;

static int hello_init(void)
{
	  printk(KERN_WARNING "Hello kernel, it's %d!\n",year);
	    return 0;
}


static void hello_exit(void)
{
	  printk("Bye, kernel!\n");
}

/* main module function*/
module_init(hello_init);
module_exit(hello_exit);
