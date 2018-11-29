#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QProcess>
#include <codeeditor.h>

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QProcess *javaProcess;
    QString data;
    CodeEditor *txtSourceCode;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void processStarted();
    void processRead() ;
    void checkError(QProcess::ProcessError err);
    void processExited(int exitCode, QProcess::ExitStatus status);

    void on_actionCompile_triggered();

    void on_actionRun_triggered();

    void on_txtConsole_cursorPositionChanged();

    void consoleChanged(int pos, int removed, int added);
    bool eventFilter(QObject *watched, QEvent *event);

    void on_cmbFontSize_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
