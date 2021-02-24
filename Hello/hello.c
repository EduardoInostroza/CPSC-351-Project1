//Eduardo Inostroza
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>
 
#define PROC_NAME "hello"
 
//creating hello entry
int proc_init(void)
{
       printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
       printk(KERN_INFO "GOLDEN_RATIO_PRIME: %lu\n", GOLDEN_RATIO_PRIME);
       return 0;
}
 
//removing hello entry
void proc_exit(void) {
       printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
       printk(KERN_INFO "gcd(3300, 24): %lu\n", gcd(3300, 24));
}
 
module_init( proc_init );
module_exit( proc_exit );
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Module");
MODULE_AUTHOR("Eduardo Inostroza");

