#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionCompile_triggered();

    void on_actionRun_triggered();

    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
