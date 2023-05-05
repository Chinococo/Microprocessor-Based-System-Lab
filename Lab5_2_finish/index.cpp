#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

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

int gpio_set_dir(unsigned int gpio,std::string dirStatus){
	int fd;
	char buf[64];
	snprintf(buf,sizeof(buf),"/sys/class/gpio/gpio%d/direction",gpio);
	fd = open(buf,O_WRONLY);
	if(fd<0){
		perror("gpio/direction");
		return fd;
	}
	if(dirStatus == "out")
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
	std::cout<<std::string(argv[1])<<std::endl;
	if (std::string(argv[1]) == "LED1") {
		if (std::string(argv[2]) == "on") {
			gpio_export(255);
			gpio_set_dir(255, "out");
			gpio_set_value(255, 1);
		}
		else {
			gpio_set_value(255, 0);
			gpio_unexport(255);
		}
	}
	if (std::string(argv[1]) == "LED2") {
		if (std::string(argv[2]) == "on") {
			gpio_export(389);
			gpio_set_dir(389, "out");
			gpio_set_value(389, 1);
		}
		else {
			gpio_set_value(389, 0);
			gpio_unexport(389);
		}
	}
	

	return 0;
}
