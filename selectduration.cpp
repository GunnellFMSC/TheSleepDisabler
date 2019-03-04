#include "selectduration.h"
#include "ui_selectduration.h"

SelectDuration::SelectDuration(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::SelectDuration)
{
    mw = parent;
    ui->setupUi(this);
    setFixedSize(size());                                              // Removes window resize
    qDebug() << "Begin SelectDuration setup.";
    QPixmap pix(":/resources/img/ImageForNS.png");                     // Consults resources directory to locate image
    int w = ui->image->width();
    int h = ui->image->height();
    ui->image->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    QIntValidator *custom = new QIntValidator(3, 427445734);           // Defines textbox to limit user input to numbers, with customized Lowest and Highest
    ui->lineEdit->setValidator(custom);                                // Impliments custom user input variance allowance
    ui->lineEdit->setPlaceholderText("Custom Value");                  // Grayed out text that disappears upon user entry
    qDebug() << "End of Select Duration set up.";
}

SelectDuration::~SelectDuration()
{
    delete ui;
}

void SelectDuration::reject()
{
    qDebug() << "Red \"X\" clicked.";
    mw->run = false;
    QDialog::reject();
}

void SelectDuration::on_oneHr_clicked()
{
    mw->seconds = 3600;
    qDebug() << mw->seconds;
}

void SelectDuration::on_twoHr_clicked()
{
    mw->seconds = 7200;
    qDebug() << mw->seconds;
}

void SelectDuration::on_fourHr_clicked()
{
    mw->seconds = 14400;
    qDebug() << mw->seconds;
}

void SelectDuration::on_eightHr_clicked()
{
    mw->seconds = 28800;
    qDebug() << mw->seconds;
}

void SelectDuration::on_twelveHr_clicked()
{
    mw->seconds = 43200;
    qDebug() << mw->seconds;
}

void SelectDuration::on_twentyFourHr_clicked()
{
    mw->seconds = 86400;
    qDebug() << mw->seconds;
}

void SelectDuration::on_fortyEightHr_clicked()
{
    mw->seconds = 172800;
    qDebug() << mw->seconds;
}

void SelectDuration::on_seventyTwoHr_clicked()
{
    mw->seconds = 259200;
    qDebug() << mw->seconds;
}

void SelectDuration::on_oneWeek_clicked()
{
    mw->seconds = 604800;
    qDebug() << mw->seconds;
}

void SelectDuration::on_twentyEightDays_clicked()
{
    mw->seconds = 2419200;
    qDebug() << mw->seconds;
}

void SelectDuration::on_oneYear_clicked()
{
    mw->seconds = 31557600;
    qDebug() << mw->seconds;
}

void SelectDuration::on_oneMillennium_clicked()
{
    mw->seconds = 31557600000;
    qDebug() << mw->seconds;
}

void SelectDuration::on_custom_clicked()
{
    QString numHold = ui->lineEdit->text();
    mw->seconds = (numHold.toInt() * 60);
    qDebug() << mw->seconds;
}

void SelectDuration::on_submit_clicked()
{
    qDebug() << "Submitted";
    if (mw->seconds == 0)                                           // <- insures minimum selection of 1 hour, defaults
        mw->seconds = 14400;                                        //    ^to 4 hours if set to zero mw->seconds
    qDebug() << "Seconds: " << mw->seconds;
}
