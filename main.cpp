/* Code by: Adam Gunnell
 *
 * This program insures the sleep/screensaver functionality is disabled.
 *
 * Features:
 *      Inital warning reminds user to run program elevated. Warning may be permanently removed.
 *      Preset options for ease of use.
 *      Custom option for flexibility of use.
 *      .ui accounts for user pressing return in custom text box, clicks button for user
 *      Program runs in background after user specifies duration to insure implementation by rewriting the configuration every 14 minutes.
 *      Minimized window appears after custom settings are completed to allow user to shot program down.
 *      Button exclusivity in .ui insures only one option is visually selected.
 *      If user closes duration selection window, program will exit with 0.
 *      Resize for all windows has been disabled.
 *
 * TODO:
 *      Add special icon for taskbar
 *      remove red X on MainWindow and WarningDialog
*/

#include "mainwindow.h"
#include <QApplication>             //most important library in Qt
#include <string>
#include <ios>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/img/SleepDisabler.bmp"));
//    qDebug() << QImageReader::supportedImageFormats();
    a.setQuitOnLastWindowClosed(true);
    MainWindow w;
    w.setWindowTitle("Sleep Disabler (Run Elevated)");
    w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
    w.setAttribute(Qt::WA_QuitOnClose, true);
    w.show();
    w.showMinimized();
    (w.run) ? (qDebug() << "Main setup complete.") : (qDebug() << "run == false, exiting program.");
    return (w.run) ? (a.exec()) : (0);  // if run is true, return a.exec(). if false, return 0
}
