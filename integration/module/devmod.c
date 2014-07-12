#include <linux/module.h>
#include <linux/sched.h>
#include <linux/version.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include "devmod.h"

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0))
#if defined(MODULE)
int init_module(void)
{
    return devmod_init();
}

int cleanup_module(void)
{
    return devmod_exit();
}
#endif
#endif


int devmod_major = 214;

static int devmod_init(void);
static void devmod_exit(void);
static int devmod_ioctl(struct inode *inode, struct file *flip, unsigned int command, unsigned long arg);
static int devmod_open(struct inode *inode, struct file *filp);
static int devmod_release(struct inode *inode, struct file *filp);

struct timer_list devmod_timer;

struct file_operations devmod_fops = {
// read:  devmod_read,
 open:  devmod_open,
 release: devmod_release,
 ioctl: devmod_ioctl,
};

static int devmod_open(struct inode *inode, struct file *filp)
{
    return 0;
}

static int devmod_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static int memory_dump(unsigned long int *address)
{
    int i = 0;
	int j = 0;
	printk("devmod:: memory_dump\n");
	for(j=0;j<4;j++)
	{	
		printk("\n%p	", address);
		for(i=0; i<9; i++)
		{
			printk("%x ", (unsigned long *)address);
		}
	}
	printk("\n");
}

static int memory_view(unsigned long int *address)
{
    printk("devmod:: memory_view [%p] = %d    (%b)\n", address, (unsigned long int)*address, (unsigned long int)*address);
}

static int devmod_timer_expired()
{
	printk("devmod:: timer expired\n");
	devmod_timer.expires = jiffies + TIMER_DELAY;
	add_timer(&devmod_timer);
	return 0;
}

static int devmod_init(void)
{
	int result = 0;
	printk("devmod:: Init... (pid=%i)\n", current->pid);

    result = register_chrdev(devmod_major, "devmod", &devmod_fops);

    if (result < 0)
    {
		printk(KERN_WARNING "devmod:: can't get major %d\n",devmod_major);
		return result;
    }

	init_timer(&devmod_timer);
	devmod_timer.function = devmod_timer_expired;
	//devmod_timer.data = (unsigned long)&kbledstatus;
	devmod_timer.expires = jiffies + TIMER_DELAY;
	add_timer(&devmod_timer);

	return 0;
}

static void devmod_exit(void)
{
    int result = 0;
	del_timer(&devmod_timer);	
    printk("devmod:: exiting...\n");
    result = unregister_chrdev(devmod_major, "devmod");

}

static int devmod_ioctl(struct inode *inode, struct file *flip, unsigned int command, unsigned long arg)
{
	int result = 0;

    switch (command) 
    {
        case DEVMOD_IOCTL_MEMORY_VIEW:
			{
				printk("This is memory view ioctl\n");
				memory_view(arg);
			}	
			break;
        case DEVMOD_IOCTL_MEMORY_DUMP:
			{
				printk("This is memory dump ioctl\n");
				memory_dump(arg);
			}	
			break;

    }
    return 0;

}

module_init(devmod_init);
module_exit(devmod_exit);

MODULE_DESCRIPTION("devmod v0.1");
MODULE_AUTHOR("codinflu");
MODULE_LICENSE("GPL");

