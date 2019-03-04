#ifndef DURATIONSELECTION_H
#define DURATIONSELECTION_H

#include <QDialog>
#include <QDebug>
#include <QObject>
#include "mainwindow.h"

namespace Ui {
class DurationSelection;
}

class DurationSelection : public QDialog
{
    Q_OBJECT
//    friend class MainWindow;
public:
    explicit DurationSelection(MainWindow *parent = 0);
    ~DurationSelection();
protected:
    unsigned long long int seconds;

    bool run;

private:
    Ui::DurationSelection *ui;

    void on_oneHr_clicked();

    void on_submit_clicked();

    void on_twoHr_clicked();

    void on_fourHr_clicked();

    void on_eightHr_clicked();

    void on_twelveHr_clicked();

    void on_twentyfourHr_clicked();

    void on_fourtyeightHr_clicked();

    void on_seventytwoHr_clicked();

    void on_oneWeek_clicked();

    void on_twentyeightDays_clicked();

    void on_oneYear_clicked();

    void on_oneMillennium_clicked();

    void on_custom_clicked();
};

#endif // DURATIONSELECTION_H
