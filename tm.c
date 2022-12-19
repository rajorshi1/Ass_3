#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

unsigned long **sys_call_table;
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

static unsigned long **aquire_sys_call_table(void)
{
    unsigned long int offset = PAGE_OFFSET;
    unsigned long **sct;
    while (offset < ULLONG_MAX) {
        sct = (unsigned long **)offset;
        if (sct[__NR_close] == (unsigned long *) sys_close)
            return sct;
        offset += sizeof(void *);
    }
    return NULL;
}

static int __init tm_init() {
     if(!(sys_call_table = aquire_sys_call_table()))
        return -1;
    original_call = sys_call_table[__NR_getpgid];
    sys_call_table[__NR_getpgid] = task_module;
    return 0;
}
static void __exit tm_exit() {
    if (sys_call_table[__NR_getpgid] != task_module) {
        printk(KERN_ALERT "Bruh Moment");
    }
    sys_call_table[__NR_getpgid] = original_call;
}
module_init(tm_init);
module_exit(tm_exit);
MODULE_LICENSE("GPL");
