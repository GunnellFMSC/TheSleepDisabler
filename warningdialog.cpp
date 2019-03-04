#include "warningdialog.h"
#include "ui_warningdialog.h"
#include <QPixmap>

WarningDialog::WarningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarningDialog)
{
    ui->setupUi(this);
    setFixedSize(size());                               // Removes window resize
    QPixmap pix(":/resources/img/Warning_icon.png");    // Consults directory for image
    int w = ui->warnImage->width();
    int h = ui->warnImage->height();
    ui->warnImage->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

WarningDialog::~WarningDialog()
{
    delete ui;
}

void WarningDialog::reject()
{
    return;
}

void WarningDialog::on_checkBox_clicked(bool checked)
{
    Ui::hideWarnChecked = checked;
}

void WarningDialog::on_Confirm_clicked()
{
    if (Ui::hideWarnChecked)
    {
        QDir dir;
        QString path = dir.absolutePath();
        path += "/HideWarning.txt";
        QFile yes(path);
        yes.open(QIODevice::WriteOnly);
        qDebug() << "\"Do Not Show This Message Again.\" was selected!";
    }
    else
        qDebug() << "\"Do Not Show This Message Again.\" was not selected!";
}
