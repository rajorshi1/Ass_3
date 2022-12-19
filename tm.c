#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

extern void *sys_call_table[];

static int uid;
module_param(uid, int, 0644);
asmlinkage int (*original_call) (const char *, int, int);
asmlinkage int task_module(pid_t pid) {
    struct task_struct *task;
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        printk(KERN_ERR "Invalid PID\n");
        return -EINVAL;
    }
    printk("PID: %d\n", task->pid);
    printk("Command Path: %s\n", task->comm);
    return original_call(source, destination);
}

static int __init tm_init() {
    original_call = sys_call_table[__NR_kernel_2D_memcpy];
    sys_call_table[__NR_kernel_2D_memcpy] = task_module;
    printk(KERN_INFO "Spying on UID:%d\n", uid);
    return 0;
}

static void __exit tm_exit() {
    if (sys_call_table[__NR_kernel_2D_memcpy] != task_module) {
        printk(KERN_ALERT "Bruh Moment");
    }
    sys_call_table[__NR_kernel_2D_memcpy] = original_call;
}

module_init(tm_init);
module_exit(tm_exit);
MODULE_LICENSE("GPL");
