#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDesktopWidget dw ;
    this->resize(dw.width()*0.7,dw.height()*0.7);
    this->move(dw.width()*0.2,dw.height()*0.1);
    ui->btnCompile->setDefaultAction(ui->actionCompile);
    ui->btnRun->setDefaultAction(ui->actionRun);



//    QRect screenSize = desktop.availableGeometry(this);
//    this->setFixedSize(QSize(screenSize.width * 0.7f, screenSize.height * 0.7f));

    Highlighter *highlighter = new Highlighter(ui->txtSourceCode->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}
