#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void on_SubmitStart_clicked();

public slots:
    void switch_leds();

private slots:
    void on_LedShining_clicked();

    void on_ButtonSwitching_clicked();


    void on_ButtonSwitching_off_clicked();

private:
    int leds_switching_times;
    Ui::MainWindow *ui;
    QTimer *qTimer;
    int count = 0;
};

#endif // MAINWINDOW_H
