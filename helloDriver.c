#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "linux/moduleparam.h"
#include "linux/init.h"
#include "linux/kmod.h"
#include "linux/sched.h"
#include "linux/delay.h"
#include <linux/kthread.h>
#include <linux/ioctl.h>
#include "common.h"
#include <linux/semaphore.h>
#include <linux/io.h>
#include <linux/interrupt.h>


/**
 *  1.定义两个内核线程，1）每隔1s打印数字1-100，  2）每隔2s打印数字1-100
 *  2.接受应用程序传递的值，要用信号量控制功能：开始，暂停，继续，停止，全部开始，全部停止，全部暂停，全部重新开始。
 *  3.用Timer计数器来实现间隔时间。
 *
 *  应用程序：
 *  1.实现一个字符设备驱动节点，以ioctl形式实现控制。
 *  2.输入对应功能的数字， 如1实现打印的开始2实现打印的暂停。
 */

typedef struct __status
{
    int current_status;
    int source_1;
    int source_2;
} lsh_status;

lsh_status thStatus;
static struct task_struct *simple_thread1;
static struct task_struct *simple_thread2;
int data = 0, data1 = 0, data2 = 0;

//运行状态:1.正常执行  2.暂停  
int status1 = 1, status2 = 1;
//定义信号量
struct semaphore sem_lsh;

//线程1
int threadfunc1(void *n)
{
    int ret = 0;
    while (1)
    {
        set_current_state(TASK_UNINTERRUPTIBLE);
        if (kthread_should_stop())
            break;
        //获取信号量
        ret = down_interruptible(&sem_lsh);
        if (ret)
            return ret;
        //检测当前控制命令状态
        //判断是否有命令到来
        printk("线程1 线程2");
        if (thStatus.current_status != 0)
        {
            switch (thStatus.current_status)
            {
            case 1://全部开始
                status1 = 1;
                thStatus.source_1--;
                break;
            case 2://全部暂停
                status1 = 2;
                thStatus.source_1--;
                break;
            case 3://全部重新开始
                status1 = 1;
                data1 = 0;
                thStatus.source_1--;
                break;
            case 4://全部停止
                status1 = 2;
                data1 = 0;
                thStatus.source_1--;
                break;
            case 5://1号暂停
                status1 = 2;
                thStatus.source_1--;
                break;
            case 7://1号开始
                status1 = 1;
                thStatus.source_1--;
                break;
            case 9://1号停止
                status1 = 2;
                data1 = 0;
                thStatus.source_1--;
                break;
            case 11://1号重新开始
                status1 = 1;
                data1 = 0;
                thStatus.source_1--;
                break;
            default:
                break;
            }
            if(thStatus.source_1 <= 0 && thStatus.source_2 <= 0)
            {
                memset(&thStatus, 0, sizeof(lsh_status));
            }
        }

        if(status1 != 1)//1.正常执行  2.暂停 
        {
            goto break_run;
        }

        printk("threadfunc1------>%d\n", data1++);
        if (data1 > 100)
            data1 = 0;
break_run:
        //释放信号量
        up(&sem_lsh);
        schedule_timeout(HZ); // HZ宏，每个内核表示的不同
    }
    return 0;
}
//线程2
int threadfunc2(void *n)
{
    int ret = 0;
    while (1)
    {
        set_current_state(TASK_UNINTERRUPTIBLE);
        if (kthread_should_stop())
            break;

        //获取信号量
        ret = down_interruptible(&sem_lsh);
        if (ret)
            return ret;
        //down(&sem_lsh);//使用这个接口就卡死重启了， 不知道为啥。

        //判断是否有命令到来
        if(thStatus.current_status != 0)
        {
            switch (thStatus.current_status)
            {
            case 1://全部开始
                status2 = 1;
                thStatus.source_2--;
                break;
            case 2://全部暂停
                status2 = 2;
                thStatus.source_2--;
                break;
            case 3://全部重新开始
                status2 = 1;
                data2 = 0;
                thStatus.source_2--;
                break;
            case 4://全部停止
                status2 = 2;
                data2 = 0;
                thStatus.source_2--;
                break;
            case 6://2号暂停
                status2 = 2;
                thStatus.source_2--;
                break;
            case 8://2号开始
                status2 = 1;
                thStatus.source_2--;
                break;
            case 10://2号停止
                status2 = 2;
                data2 = 0;
                thStatus.source_2--;
                break;
            case 12://2号重新开始
                status2 = 1;
                data2 = 0;
                thStatus.source_2--;
                break;
            default:
                break;
            }

            if(thStatus.source_1 <= 0 && thStatus.source_2 <= 0)
            {
                memset(&thStatus, 0, sizeof(lsh_status));
            }
        }

        if(status2 != 1)//1.正常执行  2.暂停 
        {
            goto break_run;
        }

        printk("threadfunc2------>%d\n", data2++);
        if (data2 > 100)
            data2 = 0;

break_run:
        //释放信号量
        up(&sem_lsh);
        schedule_timeout(2 * HZ);
    }
    return 0;
}

static int first_drv_open(struct inode *inodep, struct file *filep)
{
    printk("open\n");

    return 0;
}

static ssize_t first_drv_write(struct file *filep, const char __user *buf, size_t len, loff_t *ppos)
{
    printk("write\n");
    return 0;
}


/*
 1.全部开始   2.全部暂停   3.全部重新开始 4.全部停止
 5. 1号暂停  6. 2号暂停  7. 1号开始  8. 1号开始  9. 1号停止 10. 2号停止
 11. 1号重新开始   12. 2号重新开始
 */
static long first_drv_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int data = 0;

    if(thStatus.current_status != 0)
    {
        printk("Last command not completed\n");
        return -1;
    }

    switch (cmd)
    {
    case IOC_START:
        printk("IOCSTART\n");
        thStatus.current_status = 1;
        thStatus.source_1 = 1;
        thStatus.source_2 = 1;
        break;
    case IOC_PAUSE:
        printk("IOC_PAUSE\n");
        thStatus.current_status = 2;
        thStatus.source_1 = 1;
        thStatus.source_2 = 1;
        break;
    case IOC_RESTART:
        printk("IOC_RESTART\n");
        thStatus.current_status = 3;
        thStatus.source_1 = 1;
        thStatus.source_2 = 1;
        break;
    case IOC_STOP:
        printk("IOC_STOP\n");
        thStatus.current_status = 4;
        thStatus.source_1 = 1;
        thStatus.source_2 = 1;
        break;
    case IOC_PAUSE_1:
        printk("IOC_PAUSE_1\n");
        thStatus.current_status = 5;
        thStatus.source_1 = 1;        
        break;
    case IOC_PAUSE_2:
        printk("IOC_PAUSE_2\n");
        thStatus.current_status = 6;
        thStatus.source_2 = 1;
        break;
    case IOC_START_1:
        printk("IOC_START_1\n");
        thStatus.current_status = 7;
        thStatus.source_1 = 1;  
        break;
    case IOC_START_2:
        printk("IOC_START_2\n");
        thStatus.current_status = 8;
        thStatus.source_2 = 1;
        break;
    case IOC_STOP_1:
        printk("IOC_STOP_1\n");
        thStatus.current_status = 9;
        thStatus.source_1 = 1;  
        break;
    case IOC_STOP_2:
        printk("IOC_STOP_2\n");
        thStatus.current_status = 10;
        thStatus.source_2 = 1;
        break;
    case IOC_RESTART_1:
        printk("IOC_RESTART_1\n");
        thStatus.current_status = 11;
        thStatus.source_1 = 1;
        break;
    case IOC_RESTART_2:
        printk("IOC_RESTART_2\n");
        thStatus.current_status = 12;
        thStatus.source_2 = 1;
        break;
    default:
        printk("cmd error \n");

        return -1;
    }

    return 0;
}

static const struct file_operations first_drv_file_operation = {
    .owner = THIS_MODULE,
    .open = first_drv_open,
    .write = first_drv_write,
    .unlocked_ioctl = first_drv_ioctl,
};

static int __init first_drv_init(void)
{
    int err = -1;

    register_chrdev(111, "first_drv", &first_drv_file_operation);
    printk("first_drv_init\n");

    //初始化信号量
    sema_init(&sem_lsh, 1);
    memset(&thStatus, 0, sizeof(lsh_status));

    //创建线程
    simple_thread1 = kthread_run(threadfunc1, NULL, "simple_thread1");
    if (IS_ERR(simple_thread1))
    {
        printk("kthread_create failed\n");
        err = PTR_ERR(simple_thread1);
        simple_thread1 = NULL;
        return err;
    }

    simple_thread2 = kthread_run(threadfunc2, NULL, "simple_thread2");
    if (IS_ERR(simple_thread2))
    {
        printk("kthread_create failed\n");
        err = PTR_ERR(simple_thread2);
        simple_thread2 = NULL;
        return err;
    }

    
    return 0;
}

static void __exit first_drv_exit(void)
{
    //注册字符设备 主设备号是111.从设备号因为我们驱动程序没指定所以，默认是0.
    unregister_chrdev(111, "first_drv_exit");
    printk("first_drv_exit\n");

    //删除线程
    if (simple_thread1)
    {
        kthread_stop(simple_thread1);
        simple_thread1 = NULL;
    }

    if (simple_thread2)
    {
        kthread_stop(simple_thread2);
        simple_thread2 = NULL;
    }
}

module_init(first_drv_init);
module_exit(first_drv_exit);
MODULE_LICENSE("GPL");
