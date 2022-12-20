#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/types.h>

int pid = 0; 
module_param(pid, int, 0);

void printDetails(struct task_struct *task) {
    printk(KERN_INFO "PID: %d\n", task->pid);
    printk(KERN_INFO "User ID: %d\n", task->cred->uid.val);
    printk(KERN_INFO "Process Group ID: %d\n", task->group_leader->pid);
    printk(KERN_INFO "Command Path: %s\n", task->comm);
}

static int __init tm_init(void) {
    struct task_struct *task;
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        printk(KERN_ERR "Invalid PID\n");
        return -EINVAL;
    }
    printDetails(task);
    return 0;
}

static void __exit tm_exit(void) {
    printk("Removing Module\n");
}

module_init(tm_init);
module_exit(tm_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rajorshi Mondal");
