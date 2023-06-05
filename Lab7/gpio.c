#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int gpio_export(unsigned int gpio){
	int fd,len;
	char buf[64];
	fd = open("/sys/class/gpio/export",O_WRONLY);
	if(fd<0){
		perror("gpio/export");
		return fd;
	}
	len = snprintf(buf,sizeof(buf),"%d",gpio);
	write(fd,buf,len);
	close(fd);
	return 0;
}

int gpio_unexport(unsigned int gpio){
	int fd,len;
	char buf[64];
	fd = open("/sys/class/gpio/unexport",O_WRONLY);
	if(fd<0){
		perror("gpio/export");
		return fd;
	}
	len = snprintf(buf,sizeof(buf),"%d",gpio);
	write(fd,buf,len);
	close(fd);
	return 0;
}

int gpio_set_dir(unsigned int gpio,char *dirStatus){
	int fd;
	char buf[64];
	snprintf(buf,sizeof(buf),"/sys/class/gpio/gpio%d/direction",gpio);
	fd = open(buf,O_WRONLY);
	if(fd<0){
		perror("gpio/direction");
		return fd;
	}
	if(strncmp(dirStatus,"out", 3) == 0)
		write(fd,"out",4);
	else	
		write(fd,"in",3);
}

int gpio_set_value(unsigned int gpio, int value) {
	int fd;
	char buf[64];
	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-value");
		return fd;
	}
	if(value == 0)
		write(fd,"0",2);
	else	
		write(fd,"1",2);
	close(fd);
	return 0;
}

int main(int argc, char *argv[]) {
	if (strncmp(argv[1],"LED1",4)==0) {
		if (strncmp(argv[2],"on", 4)==0) {
			gpio_export(396);
			gpio_set_dir(396, "out");
			gpio_set_value(396, 1);
		}
		else {
			gpio_set_value(396, 0);
			gpio_unexport(396);
		}
	}
	if (strncmp(argv[1],"LED2",4)==0) {
		if (strncmp(argv[2], "on", 4) == 0) {
			gpio_export(392);
			gpio_set_dir(392, "out");
			gpio_set_value(392, 1);
		}
		else {
			gpio_set_value(392, 0);
			gpio_unexport(392);
		}
	}
	if (strncmp(argv[1],"LED3",4)==0) {
		if (strncmp(argv[2],"on",4)==0) {
			gpio_export(255);
			gpio_set_dir(255, "out");
			gpio_set_value(255, 1);
		}
		else {
			gpio_set_value(255, 0);
			gpio_unexport(255);
		}
	}
	if (strncmp(argv[1],"LED4",4)==0) {
		if (strncmp(argv[2],"on",4)==0) {
			gpio_export(429);
			gpio_set_dir(429, "out");
			gpio_set_value(429, 1);
		}
		else {
			gpio_set_value(429, 0);
			gpio_unexport(429);
		}
	}

	return 0;
}
