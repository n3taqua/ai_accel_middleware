#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <linux/slab.h>

#define DEVICE_NAME "ai_dummy"
#define CLASS_NAME "ai_class"

static dev_t dev_num;
static struct cdev c_dev;
static struct class *cl;

#define BUF_SIZE 4096
static char *buffer;

static int ai_open(struct inode *i, struct file *f) { return 0; }
static int ai_close(struct inode *i, struct file *f) { return 0; }
static ssize_t ai_read(struct file *f, char __user *buf, size_t len, loff_t *off) { return 0; }
static ssize_t ai_write(struct file *f, const char __user *buf, size_t len, loff_t *off) { return 0; }

static int ai_mmap(struct file *f, struct vm_area_struct *vma) {
    return remap_pfn_range(vma,
        vma->vm_start,
        virt_to_phys(buffer) >> PAGE_SHIFT,
        vma->vm_end - vma->vm_start,
        vma->vm_page_prot);
}

static struct file_operations ai_fops = {
    .owner = THIS_MODULE,
    .open = ai_open,
    .release = ai_close,
    .read = ai_read,
    .write = ai_write,
    .mmap = ai_mmap
};

static int __init ai_init(void) {
    alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    cdev_init(&c_dev, &ai_fops);
    cdev_add(&c_dev, dev_num, 1);
    cl = class_create(THIS_MODULE, CLASS_NAME);
    device_create(cl, NULL, dev_num, NULL, DEVICE_NAME);
    buffer = kzalloc(BUF_SIZE, GFP_KERNEL);
    printk(KERN_INFO "AI Dummy Driver loaded\n");
    return 0;
}

static void __exit ai_exit(void) {
    device_destroy(cl, dev_num);
    class_destroy(cl);
    cdev_del(&c_dev);
    unregister_chrdev_region(dev_num, 1);
    kfree(buffer);
    printk(KERN_INFO "AI Dummy Driver unloaded\n");
}

module_init(ai_init);
module_exit(ai_exit);

MODULE_LICENSE("GPL");
