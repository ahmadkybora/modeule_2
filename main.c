#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>

struct fake_device {
    char data[100];
    struct semaphore sem;
} Virtual_device;

struct cdev *mcdev;
int major_number;
int ret;

dev_t dev_num;

#define DEVICE_NAME "solidusdevice"

static int driver_entry(void) {
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if(ret < 0){
        printk(KERN_ALERT "soliduscode: failed to allocate a major number");
        return ret;
    }
    major_number = MAJOR(dev_num);
    printk(KERN_INFO "soliduscode: major number is %d", major_number);
    printk(KERN_INFO "\tuse \"mknod /dev/%s c %d 0\" for device file", DEVICE_NAME, major_number);

    mcdev = cdev_alloc();
    mcdev->ops = &fops;
    mcdev->owner = THIS_MODULE;

    ret = cdev_add(mcdev, dev_num, 1;)
    if(ret < 0){
        printk(KERN_ALERT "soliduscode: unable to add cdev to kernel");
        return ret;
    }

    return 0;
}