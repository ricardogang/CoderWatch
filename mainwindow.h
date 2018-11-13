#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QProcess>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
QProcess *javaProcess;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void processStarted();
    void processRead() ;
    void checkError(QProcess::ProcessError err);
    void processExited(int exitCode, QProcess::ExitStatus status);

private slots:
    void on_actionCompile_triggered();

    void on_actionRun_triggered();

    void on_btnSend_clicked();

    void on_txtConsole_cursorPositionChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
