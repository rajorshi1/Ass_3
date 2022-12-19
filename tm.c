#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>

int pid = 0; 
module_param(pid, int, 0);
static int __init tm_init(void) {
    struct task_struct *task;
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        printk(KERN_ERR "Invalid PID\n");
        return -EINVAL;
    }
    printk("PID: %d\n", task->pid);
    printk("Command Path: %s\n", task->comm);
    return 0;
}

static void __exit tm_exit(void) {
    printk("Konichiwa Nigga sama");
}

module_init(tm_init);
module_exit(tm_exit);
MODULE_LICENSE("GPL");
