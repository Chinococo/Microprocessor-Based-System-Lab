
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
using namespace std;

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


void setGPIO(unsigned int gpio, string status)
{
	int io;
 	gpio_export(gpio);
	gpio_set_dir(gpio,"out");
	FILE *fp = fopen("/dev/gpio","w+");
	if (fp ==NULL) {
		perror("gpio error");
		return;
	}
	char buf[1000] = "1234567";
	if (status == "on") {
		sprintf(buf,"%d %s",gpio,"1");
		//strcpy(buf, (to_string(gpio) + "1").c_str());
	}
	else {
		sprintf(buf,"%d %s",gpio,"0");
		//strcpy(buf, (to_string(gpio) + "0").c_str());
	}
	std::cout<<*buf;
	fwrite( buf,sizeof(buf), 1,fp);
	fclose(fp);
	return;
}
int getGPIO(unsigned int gpio)
{
	int io;
 	//gpio_export(gpio);
	//gpio_set_dir(gpio,"out");
	char buf[64];
	char buffer[1024];
	snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);
	int fd = open(buf,O_RDONLY);
	ssize_t bytesRead = read(fd,buffer,sizeof(buffer));
	return buffer[0]-'0';
}

int main(int argc, char *argv[]) {
	if(argc>2){
		cout<<argv[2]<<endl;
		if(std::string(argv[1])=="LED1"){
			setGPIO(255,std::string(argv[2]));
			//cout<<255;
		}
			
		if(std::string(argv[1])=="LED2"){
			setGPIO(397,std::string(argv[2]));
			//cout<<397;	
		}
		if(std::string(argv[1])=="LED3"){
			setGPIO(481,std::string(argv[2]));
			//cout<<397;	
		}
		if(std::string(argv[1])=="LED4"){
			setGPIO(396,std::string(argv[2]));
			//cout<<397;	
		}
	}else{
		
		int state = 0;
		int gpio = 0;
		cout<<"input: ";
		if(std::string(argv[1])=="LED1"){
			state = getGPIO(255);
			gpio = 255;
			cout<<255;
		}
			
		if(std::string(argv[1])=="LED2"){
			state = getGPIO(397);
			gpio = 397;
			cout<<397;	
		}
		if(std::string(argv[1])=="LED3"){
			state = getGPIO(481);
			gpio = 481;
			cout<<481;	
		}
		if(std::string(argv[1])=="LED4"){
			state = getGPIO(396);
			gpio = 396;
			cout<<396;	
		}
		cout<<endl;
		cout<<argv[1]<<":"<<"(GPIO="<<gpio<<") Status: "<<state<<endl;
	}



	
	

		
	
}


