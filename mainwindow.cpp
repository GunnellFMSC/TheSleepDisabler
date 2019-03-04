#include "mainwindow.h"
#include "ui_mainwindow.h"

/*****************************************************************************************************************
 *                                                                                                               *
 *            Displays warning pop-op (unless user has specified otherwise), then the primary window.            *
 *                                                                                                               *
 *****************************************************************************************************************/

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    seconds = 0;
    run = true;
    qDebug() << "Run is set to: " << run;
    warningPopup();                                                 // Initial pop-up warning
    durationLaunch();
    qDebug() << "In MainWindow primary function.";
    ui->setupUi(this);
    setFixedSize(size());                                           // Removes window resize
    statusBar()->hide();
    if(run)
    {
        QDir dir;
        NeverSleep = dir.absolutePath();                            // <- finds current directory path
        NeverSleep += "/NeverSleep4.bat";                           // <- adds desired batch file to path
        qDebug() << "Batch file path:" << NeverSleep;
        if (seconds > 1844674407370955159)
        {
            long double holder = seconds / 10.0;
            qDebug() << "the number held in seconds before double alteration is " << seconds << endl;
            seconds = holder;
            qDebug() << "the number held in seconds after double alteration is " << seconds << endl;
        }
        batBuild(NeverSleep);                                       // <- writes file to match user preference
        NS = batPathCon(NeverSleep);
        qDebug() << "Path conversion successful";
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(batRun()));
        qDebug() << "Run is set to: " << run;
        if(seconds!=0)
        {
            batRun();
            timer->start(840000);
        }
        else
            qDebug() << "Seconds = 0";
    }
    else
        qDebug() << "Program execution cancelled.";
}

MainWindow::~MainWindow()                     // Deconstructor
{
    delete ui;
}

MainWindow::durationLaunch()
{
    SelectDuration dialog(this);
    dialog.setWindowTitle("Sleep Disabler (Run Elevated)");
    dialog.move(QApplication::desktop()->screen()->rect().center()-dialog.rect().center());
    /*seconds =*/ dialog.exec();
    qDebug() << "Seconds returned from Duration window: " << seconds;
    return seconds;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "In custom closeEvent fuction.";
    if(run == false){
    event->accept();
    QApplication::quit();}
    else
        event->ignore();
    return;
}

/*****************************************************************************************************************
 *                                                                                                               *
 *        Starts program with a warning message reminding the user to run this with elevated privilages.         *
 *                                                                                                               *
 *****************************************************************************************************************/

void MainWindow::warningPopup()
{
    QDir dir;
    qDebug() << "In warningPopup() function.";
    QString yep = dir.absolutePath();
    yep += "/HideWarning.txt";
    QFile yes(yep);\
    if (!yes.exists())
    {
        qDebug() << "Dialog Warning Form will show using function.";
        warningLaunch();                                                   // <- Launches warning window
    }
    else
        qDebug() << "Warning message not allowed to show.";
}

MainWindow::warningLaunch()
{
    WarningDialog dialog(this);
    dialog.setWindowTitle("            W A R N I N G");
    dialog.move(QApplication::desktop()->screen()->rect().center() - dialog.rect().center());
    dialog.exec();
}

void MainWindow::batRun()
{
    qDebug() << NS;
    system(NS);                           // <- executes batch file
    qDebug() << "Batch Run successful.";
}

/*****************************************************************************************************************
 *                                                                                                               *
 *                      Converts QString to const char *, returns to on_submit_clicked()                         *
 *                                                                                                               *
 *****************************************************************************************************************/

const char* MainWindow::batPathCon(QString path)
{
    std::string holder = path.toLocal8Bit().constData();
    char * charPointer = new char[holder.length()+1];
    std::strcpy (charPointer, path.toLatin1());
    const char* cCPoint = charPointer;
    return cCPoint;
}

/*****************************************************************************************************************
 *                                                                                                               *
 *              Converts batch path to batch file, then reads it, copying file into QStringList line.            *
 *                                                                                                               *
 *****************************************************************************************************************/

void MainWindow::readQFile(QString NSB)
{
    QFile NeverSleepBat(NSB);                                           // <- accesses batch file
    QString errMsg;
    if (!NeverSleepBat.open(QIODevice::ReadOnly | QIODevice::Text))     // <- alerts if batch file cannot be found
    {
        errMsg = NeverSleepBat.errorString();
        qDebug() << "NeverSleep4.bat not found!\n" << errMsg;
    }
    else
    {
        qDebug() << "NeverSleep4.bat open Successful!";
        QTextStream qinFile(&NeverSleepBat);
        while (!qinFile.atEnd())                                        // <- reads batch to QStringList line if found
        {
            line.append(qinFile.readLine());
        }
        qDebug() << "NeverSleep4.bat read Successful!";
        NeverSleepBat.close();
    }
}

/*****************************************************************************************************************
 *                                                                                                               *
 *                     Gets batch file from path, overwrites file with QStringList line.                         *
 *                                                                                                               *
 *****************************************************************************************************************/

void MainWindow::writeQFile(QString NSB)
{
    qDebug() << "Batch file path:" << NSB;
    QFile NeverSleepBat(NSB);
    QTextStream qoutFile(&NeverSleepBat);                                       // <- applies qoutFile to batch file
    QString errMsg;
    QFileDevice::FileError err = QFileDevice::NoError;
    if (!NeverSleepBat.open(QIODevice::WriteOnly | QIODevice::Text))            // <- notifies if file not found
    {
        err = NeverSleepBat.error();
        errMsg = NeverSleepBat.errorString();
        qDebug() << "NeverSleep4.bat unable to reopen!\n" << errMsg << err;
    }
    else                                                                        // <- if file found
    {
        for (QStringList::iterator it = line.begin(); it != line.end(); it++)   // <- rewrite file with line content
        {
            qoutFile << *it << "\n";
        }
        qDebug() << "NeverSleep4.bat was sucsessfully rewritten!";
        NeverSleepBat.flush();
        NeverSleepBat.close();
    }
}

/*****************************************************************************************************************
 *                                                                                                               *
 *      Alters first line of batch file to account for user input, reads and writes file if it exists.           *
 *         If NeverSleep4.bat does not exist, creates new file and writes entire batch code to it.               *
 *                                                                                                               *
 *****************************************************************************************************************/

void MainWindow::batBuild(QString SleepNever)
{
    qDebug() << "in batBuild; Batch file path:" << SleepNever;
    QString secVar = "set SECONDS=" + QString::number(seconds);         // <- creates holder for
    qDebug() << "secVar:" << secVar;
    QFile NSB(SleepNever);
    if (NSB.exists())                                                   // <- If file exists, replace first line
    {
        qDebug() << "NeverSleep4.bat exists.";
        readQFile(SleepNever);
        line.removeFirst();
        line.prepend(secVar);
        qDebug() << "First line replaced!";
        writeQFile(SleepNever);
    }
    else                                                                // <- If file does not exist, create
    {                                                                   //    ^and write new NeverSleep4.bat file
        qDebug() << "NeverSleep4.bat does not exist.";
        NSB.open(QIODevice::WriteOnly);                                 // <- Creates new file NeverSleep4.bat
        qDebug() << "NeverSleep4.bat has been created.";
        line.append(secVar);
        line.append("cd C:\\WINDOWS\\system32");
        line.append("powercfg -change -monitor-timeout-ac 0");
        line.append("Reg add \"HKEY_CURRENT_USER\\Control Panel\\Desktop\" /v ScreenSaveActive /t REG_SZ /d 0 /f");
        line.append("Reg add \"HKEY_CURRENT_USER\\Software\\Policies\\Microsoft\\Windows\\Control Panel\\Desktop\" /v ScreenSaveActive /t REG_SZ /d 0 /f");
        line.append("Reg add \"HKEY_CURRENT_USER\\Software\\Policies\\Microsoft\\Windows\\Control Panel\\Desktop\" /v ScreenSaverIsSecure /t REG_SZ /d 0 /f");
        line.append("Reg add \"HKEY_CURRENT_USER\\Software\\Policies\\Microsoft\\Windows\\Control Panel\\Desktop\" /v ScreenSaveTimeOut /t REG_SZ /d %SECONDS% /f");
        line.append("exit");
        NSB.close();
        qDebug() << "NeverSleep4.bat has been closed.";
        writeQFile(SleepNever);
    }
}

void MainWindow::on_close_clicked()
{
    run = false;
    qDebug() << "On close clicked.";
    this->close();
    return;
}
