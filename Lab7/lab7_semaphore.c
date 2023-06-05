#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

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

static sem_t semaphore;
static const int NUM_LEDS = 3;

typedef struct {
	int thread_id;
	int status;
	int count;
} ThreadArg;

void *shine(void *input) {
	ThreadArg* arg = (ThreadArg *)input;

	sem_wait(&semaphore);

	for (int i = 0; i < arg->count * 2; i++) {
		if (arg->thread_id == 0) {
			if (arg->status == 12) {
                arg->status = 3;
			}
            else {
                arg->status = 12;
			}
		}
		else if (arg->thread_id == 1) {
			if (arg->status == 10) {
                arg->status = 0;
			}
            else {
                arg->status = 10;
			}
		}
		else {
			if (arg->status == 6) {
                arg->status = 15;
			}
            else {
                arg->status = 6;
			}
		}
		int arr[4]={255,397,481,396};
		for(int i=0;i<4;i++){
			gpio_export(arr[i]);
			gpio_set_dir(arr[i],"out");
			gpio_set_value(arr[i],(arg->status>>i));
		}
		sleep(1);
		printf("thread id:%d status: %d\n", arg->thread_id, arg->status);
		printf("change to %d%d%d%d\n",(arg->status>>3)&1,(arg->status>>2)&1,(arg->status>>1)&1,(arg->status>>0)&1);

		
	}

	sem_post(&semaphore);
	pthread_exit(NULL);
}

int main(int argc, char **argv) {
	if (argc != 3) {
		perror("Expected 3 arguments.");
		exit(EXIT_FAILURE);
	}

	sem_init(&semaphore, 0, 1);
	pthread_t threads[NUM_LEDS];
	
	int max_count = argv[2][0] - '0';
	int status = 0;

	for (int i = 0; i < NUM_LEDS; i++) {
		status = status * 10 + (argv[1][i] - '0');
	}

	ThreadArg *arg = NULL;

	for (int i = 0; i < NUM_LEDS; i++) {
		arg = (ThreadArg *)malloc(sizeof(ThreadArg));
		arg->thread_id = i;
		arg->status = status;
		arg->count = max_count;
		pthread_create(&threads[i], NULL, shine, arg);
	}

	for (int i = 0; i < NUM_LEDS; i++) {
		pthread_join(threads[i], NULL);
	}

	sem_destroy(&semaphore);
	return EXIT_SUCCESS;
}
