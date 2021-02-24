//Eduardo Inostroza
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>
//#include <stddef.h>
 
#define BUFFER_SIZE 128
#define PROC_NAME "seconds"
 
unsigned long initial_jiffies;
 
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);
 
static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};
 
int proc_init(void) {
    printk(KERN_INFO "creates the /proc/seconds entry.\n");
    proc_create(PROC_NAME, 0666, NULL, &proc_ops);
    initial_jiffies = jiffies;
 
    return 0;
}
 
void proc_exit(void) {
    printk(KERN_INFO "removes the /proc/seconds entry.\n");
    remove_proc_entry(PROC_NAME, NULL);
}
 
/* This function is called each time /proc/seconds is read */
ssize_t proc_read(struct file *file, char __user *usr_buf,  size_t count, loff_t *pos)  {
    int rv = 0;
    char buffer[BUFFER_SIZE];
    static int completed = 0;
    
    if (completed) {
        completed = 0;
        return 0;
    }
    completed = 1;
    
    rv = sprintf(buffer, "%lu\n", (jiffies - initial_jiffies)/HZ);
    
    /* copies kernel space buffer to user space usr buf */
    copy_to_user(usr_buf, buffer, rv);
    return rv;
}
 
module_init(proc_init);
module_exit(proc_exit);
 
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("Eduardo Inostroza");

