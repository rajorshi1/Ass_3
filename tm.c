#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <asm/paravirt.h>

unsigned long **sys_call_table;
unsigned long original_cr0;

asmlinkage long (*ref_sys_getgpid)(pid_t pid);
asmlinkage long new_sys_task_module(pid_t pid)
{
    struct task_struct *task;
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (task == NULL) {
        printk(KERN_ERR "Invalid PID\n");
        return -EINVAL;
    }
    printk("PID: %d\n", task->pid);
    printk("Command Path: %s\n", task->comm);
    return ref_sys_getgpid(pid);
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

static int __init tm_init(void)
{
    if(!(sys_call_table = aquire_sys_call_table()))
        return -1;
    original_cr0 = read_cr0();
    write_cr0(original_cr0 & ~0x00010000);
    ref_sys_getgpid = (void *)sys_call_table[__NR_getgpid];
    sys_call_table[__NR_getgpid] = (unsigned long *)new_sys_task_module;
    write_cr0(original_cr0);
    return 0;
}

static void __exit tm_exit(void)
{
    if(!sys_call_table) {
        return;
    }
    write_cr0(original_cr0 & ~0x00010000);
    sys_call_table[__NR_getgpid] = (unsigned long *)ref_sys_getgpid;
    write_cr0(original_cr0);
    msleep(2000);
}

module_init(tm_init);
module_exit(tm_exit);
MODULE_LICENSE("GPL");


