#ifndef SELECTDURATION_H
#define SELECTDURATION_H

#include <QDialog>
#include <QDebug>
#include <QObject>
#include "mainwindow.h"

class MainWindow;
namespace Ui {
class SelectDuration;
}
MainWindow static *mw;
class SelectDuration : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDuration(MainWindow *parent = 0);
    ~SelectDuration();

private slots:
    void reject();

    void on_oneHr_clicked();

    void on_twoHr_clicked();

    void on_fourHr_clicked();

    void on_eightHr_clicked();

    void on_twelveHr_clicked();

    void on_twentyFourHr_clicked();

    void on_fortyEightHr_clicked();

    void on_seventyTwoHr_clicked();

    void on_oneWeek_clicked();

    void on_twentyEightDays_clicked();

    void on_oneYear_clicked();

    void on_oneMillennium_clicked();

    void on_custom_clicked();

    void on_submit_clicked();

private:
    Ui::SelectDuration *ui;
};

#endif // SELECTDURATION_H
