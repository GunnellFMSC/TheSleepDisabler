// Code by Adam Gunnell

#include "durationselection.h"
#include "ui_durationselection.h"

DurationSelection::DurationSelection(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DurationSelection)
{
//    mw = parent;
    ui->setupUi(this);
    qDebug() << "DurationSelection setup.";
    QPixmap pix(":/resources/img/ImageForNS.png");                      // Consults resources directory to locate image
    int w = ui->image->width();
    int h = ui->image->height();
    ui->image->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    QIntValidator *custom = new QIntValidator(1, 427445734);           // Defines textbox to limit user input to numbers, with customized Lowest and Highest
    ui->lineEdit->setValidator(custom);                                // Impliments custom user input variance allowance
    qDebug() << "Duration Selection set up.";
}

DurationSelection::~DurationSelection()
{
    delete ui;
}

/*****************************************************************************************************************
 *                                                                                                               *
 *      The following functions redefine the "seconds" variable depending on the last selected button click.     *
 *               Setting to only allow one button clicked at a time found in DurationSelection.ui                       *
 *                                                                                                               *
 *****************************************************************************************************************/
void DurationSelection::on_oneHr_clicked()
{
    seconds = 3600;
    qDebug() << seconds;
}

void DurationSelection::on_twoHr_clicked()
{
    seconds = 7200;
    qDebug() << seconds;
}

void DurationSelection::on_fourHr_clicked()
{
    seconds = 14400;
    qDebug() << seconds;
}

void DurationSelection::on_eightHr_clicked()
{
    seconds = 28800;
    qDebug() << seconds;
}

void DurationSelection::on_twelveHr_clicked()
{
    seconds = 43200;
    qDebug() << seconds;
}

void DurationSelection::on_twentyfourHr_clicked()
{
    seconds = 86400;
    qDebug() << seconds;
}

void DurationSelection::on_fourtyeightHr_clicked()
{
    seconds = 172800;
    qDebug() << seconds;
}

void DurationSelection::on_seventytwoHr_clicked()
{
    seconds = 259200;
    qDebug() << seconds;
}

void DurationSelection::on_oneWeek_clicked()
{
    seconds = 604800;
    qDebug() << seconds;
}

void DurationSelection::on_twentyeightDays_clicked()
{
    seconds = 2419200;
    qDebug() << seconds;
}

void DurationSelection::on_oneYear_clicked()
{
    seconds = 31557600;
    qDebug() << seconds;
}

void DurationSelection::on_oneMillennium_clicked()
{
    seconds = 31557600000;
    qDebug() << seconds;
}

void DurationSelection::on_custom_clicked()
{
    QString numHold = ui->lineEdit->text();
    seconds = numHold.toInt();
    qDebug() << seconds;
}

/*****************************************************************************************************************
 *                                                                                                               *
 *      Catches for the Submit button being clicked. durationselection.ui causes the window to disappear but allows     *
 *              the program to continue running, executing the batch file every 14 minutes.                      *
 *                                                                                                               *
 *****************************************************************************************************************/

void DurationSelection::on_submit_clicked()
{
    qDebug() << "Submitted";
    if (seconds == 0)                                           // <- insures minimum selection of 1 hour, defaults
        seconds = 14400;                                        //    ^to 4 hours if set to zero seconds
//    mw->seconds = seconds;
}

