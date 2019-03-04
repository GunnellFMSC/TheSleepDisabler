#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QDir>

namespace Ui {
class WarningDialog;
bool static hideWarnChecked = false;
}

class WarningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WarningDialog(QWidget *parent = 0);
    ~WarningDialog();

private slots:
    void reject();

    void on_checkBox_clicked(bool checked);

    void on_Confirm_clicked();

private:
    Ui::WarningDialog *ui;
};

#endif // WARNINGDIALOG_H
