/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCheckBox *led1;
    QCheckBox *led2;
    QCheckBox *led3;
    QCheckBox *led4;
    QLabel *LabelTimes;
    QPushButton *ButtonSwitching;
    QLineEdit *EditTextTimes;
    QLabel *ImgLed4;
    QLabel *ImgLed3;
    QLabel *ImgLed2;
    QLabel *ImgLed1;
    QPushButton *LedShining;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        led1 = new QCheckBox(centralWidget);
        led1->setObjectName(QStringLiteral("led1"));
        led1->setGeometry(QRect(110, 50, 97, 22));
        led2 = new QCheckBox(centralWidget);
        led2->setObjectName(QStringLiteral("led2"));
        led2->setGeometry(QRect(110, 80, 97, 22));
        led3 = new QCheckBox(centralWidget);
        led3->setObjectName(QStringLiteral("led3"));
        led3->setGeometry(QRect(110, 110, 97, 22));
        led4 = new QCheckBox(centralWidget);
        led4->setObjectName(QStringLiteral("led4"));
        led4->setGeometry(QRect(110, 140, 97, 22));
        LabelTimes = new QLabel(centralWidget);
        LabelTimes->setObjectName(QStringLiteral("LabelTimes"));
        LabelTimes->setGeometry(QRect(230, 30, 67, 17));
        ButtonSwitching = new QPushButton(centralWidget);
        ButtonSwitching->setObjectName(QStringLiteral("ButtonSwitching"));
        ButtonSwitching->setGeometry(QRect(230, 80, 99, 27));
        EditTextTimes = new QLineEdit(centralWidget);
        EditTextTimes->setObjectName(QStringLiteral("EditTextTimes"));
        EditTextTimes->setGeometry(QRect(230, 50, 113, 27));
        ImgLed4 = new QLabel(centralWidget);
        ImgLed4->setObjectName(QStringLiteral("ImgLed4"));
        ImgLed4->setGeometry(QRect(60, 130, 51, 31));
        ImgLed4->setPixmap(QPixmap(QString::fromUtf8("bulb_dark.png")));
        ImgLed4->setScaledContents(true);
        ImgLed3 = new QLabel(centralWidget);
        ImgLed3->setObjectName(QStringLiteral("ImgLed3"));
        ImgLed3->setGeometry(QRect(60, 100, 51, 31));
        ImgLed3->setPixmap(QPixmap(QString::fromUtf8("bulb_dark.png")));
        ImgLed3->setScaledContents(true);
        ImgLed2 = new QLabel(centralWidget);
        ImgLed2->setObjectName(QStringLiteral("ImgLed2"));
        ImgLed2->setGeometry(QRect(60, 70, 51, 31));
        ImgLed2->setPixmap(QPixmap(QString::fromUtf8("bulb_dark.png")));
        ImgLed2->setScaledContents(true);
        ImgLed1 = new QLabel(centralWidget);
        ImgLed1->setObjectName(QStringLiteral("ImgLed1"));
        ImgLed1->setGeometry(QRect(60, 40, 51, 31));
        ImgLed1->setPixmap(QPixmap(QString::fromUtf8("bulb_dark.png")));
        ImgLed1->setScaledContents(true);
        LedShining = new QPushButton(centralWidget);
        LedShining->setObjectName(QStringLiteral("LedShining"));
        LedShining->setGeometry(QRect(70, 180, 99, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        led1->setText(QApplication::translate("MainWindow", "Led1", Q_NULLPTR));
        led2->setText(QApplication::translate("MainWindow", "Led2", Q_NULLPTR));
        led3->setText(QApplication::translate("MainWindow", "Led3", Q_NULLPTR));
        led4->setText(QApplication::translate("MainWindow", "Led4", Q_NULLPTR));
        LabelTimes->setText(QApplication::translate("MainWindow", "Times", Q_NULLPTR));
        ButtonSwitching->setText(QApplication::translate("MainWindow", "LED Switching", Q_NULLPTR));
        ImgLed4->setText(QString());
        ImgLed3->setText(QString());
        ImgLed2->setText(QString());
        ImgLed1->setText(QString());
        LedShining->setText(QApplication::translate("MainWindow", "LED shining", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
