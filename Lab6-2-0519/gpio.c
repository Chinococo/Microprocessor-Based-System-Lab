#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUM 60
#define MODULE_NAME "gpio"

static int iCount = 0;
static char userChar[100];

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
{
	printk("device read\n");
	return count;
}

static ssize_t drv_write(struct file *flip, const char *buf, size_t count, loff_t *ppos)
{
	printk("device write\n");
	printk("%d\n", iCount);
	printk("W_buf_size: %d\n", (int)count);
	copy_from_user(userChar, buf, count);
	userChar[count-1] = 0;
	int i=0;
	char gpio[10] = {0}; 
	char on_off[10]={0};
	for(i=0;i<sizeof(userChar);i++){
		if(userChar[i]==' ')
			break;
		gpio[i]=userChar[i];
	}
	
		
	int j=i+1;
	for(j=i+1;j<sizeof(userChar);j++){
		if(userChar[j]=='\0')
			break;
		on_off[j-i-1]=userChar[j];
	}
	printk("\nuserChar:%s",gpio);
	printk("\nuserChar:%s",on_off);
	printk("\nuserChar: %s\n", userChar);
	printk("\nuserChar: %d\n", (int)sizeof(userChar));
	struct file *fp;
	loff_t pos = 0;
	mm_segment_t old_fs;
	old_fs=get_fs();
	set_fs(get_ds());
	// export gpio number
	fp = filp_open("/sys/class/gpio/export",O_WRONLY,0);
	vfs_write(fp,gpio,strlen(gpio),&pos);
	filp_close(fp,NULL);
	// write led out/input
	char cmd[1000]={0};
	snprintf(cmd,sizeof(cmd),"/sys/class/gpio/gpio%s/direction",gpio);
	fp = filp_open(cmd,O_WRONLY,0);
	vfs_write(fp,"out",4,&pos);
	filp_close(fp,NULL);
	// write led status
	snprintf(cmd,sizeof(cmd),"/sys/class/gpio/gpio%s/value",gpio);
	fp = filp_open(cmd,O_WRONLY,0);
	if(on_off[0]=='1')
		vfs_write(fp,"1",2,&pos);
	else
		vfs_write(fp,"0",2,&pos);
	filp_close(fp,NULL);
	//restore envirnment
	set_fs(old_fs);
	iCount++;
	return count;
}

long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk("device ioctl\n");
	return 0;
}

static int drv_open(struct inode *inode, struct file *filp)
{
	printk("device open\n");
	return 0;
}

static int drv_release(struct inode *inode, struct file *filp)
{
	printk("device close\n");
	return 0;
}

struct file_operations drv_fops =
{
	read: drv_read,
	write: drv_write,
	unlocked_ioctl: drv_ioctl,
	open: drv_open,
	release: drv_release,
};

static int demo_init(void)
{
	if (register_chrdev(MAJOR_NUM, MODULE_NAME, &drv_fops) < 0)
	{
		printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
		return (-EBUSY);
	}
	printk("<1>%s: started\n", MODULE_NAME);
	return 0;
}

static void demo_exit(void)
{
	unregister_chrdev(MAJOR_NUM, "gpio");
	printk("<1>%s: removed\n", MODULE_NAME);
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");

