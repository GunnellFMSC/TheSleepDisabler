#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QDir>
#include "warningdialog.h"
#include "selectduration.h"
#include <QDesktopWidget>
#include <cstring>
#include <vector>
#include <QMessageBox>
#include <chrono>
#include <QSizeGrip>
#include <QIntValidator>
#include <QTextStream>
#include <QtWidgets>
#include <QTimer>
#include <QCloseEvent>
#include <QApplication>

namespace Ui {
class MainWindow;
}

static QString NeverSleep;

static QStringList line;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void warningPopup();
    warningLaunch();
    durationLaunch();
    unsigned long long int seconds;  // 0 to 18,446,744,073,709,551,615
    const char* NS;
    bool run;
    const char* batPathCon(QString path);  // converts string for .bat location to const char pointer for system use
    void readQFile(QString NSB);
    void writeQFile(QString NSB);
    void batBuild(QString NeverSleep);

public slots:
    void batRun();
    void closeEvent(QCloseEvent *event);
    void on_close_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
