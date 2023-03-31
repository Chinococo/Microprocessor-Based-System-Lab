#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <QTimer>

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
    return 0;
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    qTimer(new QTimer(this))
{
    ui->setupUi(this);
    QImage image;
    ui->progressBar->setValue(ui->horizontalSlider->value());
    image.load("/home/nvidia/Desktop/Lab3/bulb_dark.png");
    //ui->ImgLed1->setPixmap(QPixmap::fromImage(image));
    //ui->ImgLed2->setPixmap(QPixmap::fromImage(image));
    //ui->ImgLed3->setPixmap(QPixmap::fromImage(image));;
    //ui->ImgLed4->setPixmap(QPixmap::fromImage(image));
    connect(qTimer, SIGNAL(timeout()), this, SLOT(switch_leds()));
    ui->statusBar->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LedShining_clicked()
{
    QImage image1,image2;
    image1.load("/home/nvidia/Desktop/lab3/Lab3/bulb_dark.png");
    image2.load("/home/nvidia/Desktop/lab3/Lab3/bulb_light.png");

    ui->ImgLed1->setVisible(true);
    ui->ImgLed2->setVisible(true);
    ui->ImgLed3->setVisible(true);
    ui->ImgLed4->setVisible(true);

    if(ui->led1->checkState())
        ui->ImgLed1->setPixmap(QPixmap::fromImage(image2));
    else
        ui->ImgLed1->setPixmap(QPixmap::fromImage(image1));

    if(ui->led2->checkState())
        ui->ImgLed2->setPixmap(QPixmap::fromImage(image2));
    else
        ui->ImgLed2->setPixmap(QPixmap::fromImage(image1));

    if(ui->led3->checkState())
        ui->ImgLed3->setPixmap(QPixmap::fromImage(image2));
    else
        ui->ImgLed3->setPixmap(QPixmap::fromImage(image1));

    if(ui->led4->checkState())
        ui->ImgLed4->setPixmap(QPixmap::fromImage(image2));
    else
        ui->ImgLed4->setPixmap(QPixmap::fromImage(image1));
}

void MainWindow::on_ButtonSwitching_clicked()
{
    //ui->LabelTimes->setText(QString::number((1/float(ui->progressBar->value()))));
    count = 0;
    qTimer->start(1000*(1/float(ui->progressBar->value())));
    leds_switching_times = ui->spinBox->value();

}
void MainWindow::switch_leds()
{

    gpio_set_value(396, 0);
    gpio_unexport(396);
    gpio_set_value(392, 0);
    gpio_unexport(392);
    gpio_set_value(255, 0);
    gpio_unexport(255);
    gpio_set_value(429, 0);
    gpio_unexport(429);
    //ui->LabelTimes->setText(QString::number(count));
    static bool flag = false;
    if (count == leds_switching_times * 2) {
        qTimer->stop();
        count = 0;
        flag = false;
        return;
    }
    //set_bulb_power(ui->label_bulb_1, flag);
    //set_bulb_power(ui->label_bulb_2, flag);
    //set_bulb_power(ui->label_bulb_3, !flag);
    //set_bulb_power(ui->label_bulb_4, !flag);
    QImage image1,image2;
    image1.load("/home/nvidia/Desktop/lab3/Lab3/bulb_dark.png");
    image2.load("/home/nvidia/Desktop/lab3/Lab3/bulb_light.png");

    ui->ImgLed1->setVisible(true);
    ui->ImgLed2->setVisible(true);
    ui->ImgLed3->setVisible(true);
    ui->ImgLed4->setVisible(true);
    ui->led1->setChecked(flag);
    ui->led2->setChecked(flag);
    ui->led3->setChecked(!flag);
    ui->led4->setChecked(!flag);
    if(ui->led1->checkState()){
        ui->ImgLed1->setPixmap(QPixmap::fromImage(image2));
        gpio_export(396);
        gpio_set_dir(396, "out");
        gpio_set_value(396, 1);
    }
    else
        ui->ImgLed1->setPixmap(QPixmap::fromImage(image1));

    if(ui->led1->checkState()){
        ui->ImgLed1->setPixmap(QPixmap::fromImage(image2));
        gpio_export(392);
        gpio_set_dir(392, "out");
        gpio_set_value(393, 1);
    }
    else
        ui->ImgLed2->setPixmap(QPixmap::fromImage(image1));

    if(ui->led1->checkState()){
        ui->ImgLed1->setPixmap(QPixmap::fromImage(image2));
        gpio_export(255);
        gpio_set_dir(255, "out");
        gpio_set_value(255, 1);
    }
    else
        ui->ImgLed3->setPixmap(QPixmap::fromImage(image1));

    if(ui->led1->checkState()){
        ui->ImgLed1->setPixmap(QPixmap::fromImage(image2));
        gpio_export(429);
        gpio_set_dir(429, "out");
        gpio_set_value(429, 1);
    }
    else
        ui->ImgLed4->setPixmap(QPixmap::fromImage(image1));
    count++;
    flag = !flag;
}



void MainWindow::on_ButtonSwitching_off_clicked()
{
    QImage image1,image2;
    image1.load("/home/nvidia/Desktop/lab3/Lab3/bulb_dark.png");
    image2.load("/home/nvidia/Desktop/lab3/Lab3/bulb_light.png");

    ui->ImgLed1->setVisible(false);
    ui->ImgLed2->setVisible(false);
    ui->ImgLed3->setVisible(false);
    ui->ImgLed4->setVisible(false);
    qTimer->stop();
    count = 0;

}
