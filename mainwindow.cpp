#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"
#include <QDesktopWidget>
#include <QTextStream>
#include <QMessageBox>
#include <QProcess>
#include <iostream>


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

void MainWindow::on_actionCompile_triggered()
{
    //QString filename = QFileDialog::getSaveFileName(this, tr("Guardar"), "","" );
        QString filename= "Clase.java";
        if (filename != "") {
            QFile file(filename);


            if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
                QTextStream stream(&file);
                stream << ui->txtSourceCode->toPlainText();
                file.flush();
                file.close();
            }
            else {
                QMessageBox::critical(this, tr("Error"), tr("error"));
                return;
            }
        }

        QProcess compilar;
        QString exec = "javac";
        QStringList parametros;
        parametros << filename ;
        compilar.start(exec, parametros);
        if (compilar.waitForFinished()){ // sets current thread to sleep and waits for pingProcess end
            QString resultado(compilar.readAllStandardError());
            resultado+= compilar.readAllStandardOutput();
            if (resultado.length()==0) {
                ui->txtConsole->setPlainText("COMPILATION SUCCESSFULL") ;
            } else {
                ui->txtConsole->setPlainText(resultado);
            }
        } else {
            ui->txtConsole->setPlainText("ERROR: "+compilar.errorString());
        }
}

void MainWindow::on_actionRun_triggered()
{
    QString classname= "Clase";

    QProcess correr;
    QString exec = "c.bat";
    QStringList parametros2;
    parametros2 << classname ;
    parametros2 << "Clase";

    correr.start(exec, parametros2);
    if (correr.waitForStarted()){
        QString resultado(correr.readAllStandardError());
        resultado+= correr.readAllStandardOutput();
        ui->txtConsole->setPlainText(resultado);
    } else {
        ui->txtConsole->setPlainText(correr.errorString());
    }
    //correr.write("2\n\r");
//    std::cout << "2" << endl ;
}

void MainWindow::on_btnSend_clicked()
{
   /* QProcess correr;
    correr.open();
    QString exec = "cls";
    QStringList parametros;
    parametros << "Hey" ;
    correr.write("hey",3) ;

    correr.start(exec, parametros);
    if (correr.waitForFinished()){
        QString resultado(correr.readAllStandardError());
        resultado+= correr.readAllStandardOutput();
        ui->txtConsole->setPlainText(resultado);
    } else {
        ui->txtConsole->setPlainText(correr.errorString());
    }*/

    std::cout << "hey";
}
