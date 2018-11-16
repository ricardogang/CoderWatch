#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "highlighter.h"
#include <QDesktopWidget>
#include <QTextStream>
#include <QMessageBox>
#include <QProcess>
#include <iostream>
#include <codeeditor.h>
#include <QAbstractScrollArea>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CodeEditor *txtSourceCode= new CodeEditor(ui->widget) ;
    txtSourceCode->setGeometry(5,5,ui->txtConsole->width(),ui->txtNotes->height()*35);

    data="";

    javaProcess= new QProcess() ;
    connect(javaProcess, &QProcess::started, this, &MainWindow::processStarted);
    connect(javaProcess, &QProcess::readyRead, this, &MainWindow::processRead);

    connect(javaProcess, &QProcess::errorOccurred, this, &MainWindow::checkError);
//    connect(javaProcess, &QProcess::finished,this,&MainWindow::processExited);
    connect(javaProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));

    connect( ui->txtConsole->document(), SIGNAL(contentsChange(int,int,int)), this, SLOT(consoleChanged(int,int,int)));

    QDesktopWidget dw ;
    this->resize(dw.width()*0.7,dw.height()*0.7);
    this->move(dw.width()*0.2,dw.height()*0.1);
    ui->btnCompile->setDefaultAction(ui->actionCompile);
    ui->btnRun->setDefaultAction(ui->actionRun);



    //    QRect screenSize = desktop.availableGeometry(this);
    //    this->setFixedSize(QSize(screenSize.width * 0.7f, screenSize.height * 0.7f));

    Highlighter *highlighter = new Highlighter(txtSourceCode->document());
    ui->txtConsole->installEventFilter(this);
}


bool MainWindow::eventFilter(QObject *watched, QEvent *event){
    if (watched == ui->txtConsole && event->type() == QEvent::KeyPress) {
        QKeyEvent *e = static_cast < QKeyEvent * >(event);
        int i= e->key() ;
        ui->txtNotes->setText(QString(e->key()));
        if (i==16777220) {
            data+=QString("\n\r");
            javaProcess->write(data.toUtf8());
            data="" ;
        }
        if (i>31 && i<255) {
            data+= QString(i) ;
        }
    }
    return QMainWindow::eventFilter(watched, event);
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
            //stream << txtSourceCode->toPlainText();
            file.flush();
            file.close();
        }
        else {
            //QMessageBox::critical(this, tr("Error"), tr("error"));
            return;
        }
    }

    QProcess compilar;
    compilar.start("javac", QStringList() << filename );
    if (compilar.waitForFinished()){ // sets current thread to sleep and waits for pingProcess end
        QString resultado(compilar.readAllStandardError());
        resultado+= compilar.readAllStandardOutput();
        if (resultado.length()==0) {
            ui->txtConsole->setPlainText("COMPILATION SUCCESSFULL\n") ;
        } else {
            ui->txtConsole->setPlainText(resultado);
        }
    } else {
        ui->txtConsole->setPlainText("ERROR: "+compilar.errorString());
    }
}

void MainWindow::processRead() {
    javaProcess->waitForStarted() ;
    ui->txtConsole->appendPlainText(javaProcess->readAll());
}

void MainWindow::processStarted(){
    ui->txtConsole->appendPlainText("PROCESS STARTED...\n") ;
   // javaProcess->waitForFinished();
}

void MainWindow::checkError(QProcess::ProcessError err){
    ui->txtConsole->setPlainText("ERROR: "+javaProcess->errorString()+err);
}

void MainWindow::processExited(int exitCode, QProcess::ExitStatus status){
    ui->txtConsole->appendPlainText("PROCESS ENDED: "+QString(exitCode)+" "+status+"\n") ;
    try {
        javaProcess->close();
    } catch (...) {
    }
}

void MainWindow::on_actionRun_triggered()
{
    QString classname= "Clase";
    javaProcess->start("c.bat", QStringList() << "Clase");
}

void MainWindow::on_btnSend_clicked()
{
    javaProcess->write("@\n\r");
}

void MainWindow::on_txtConsole_cursorPositionChanged()
{
    QTextCursor c(ui->txtConsole->document()) ;
    c.movePosition(QTextCursor::End);
    ui->txtConsole->setTextCursor(c);
}

void MainWindow::consoleChanged(int pos, int removed, int added){
    QTextCursor c(ui->txtConsole->textCursor());
    c.setPosition(pos);
    if(removed > 0){
        ui->txtConsole->undo();
        c.setPosition(pos + removed, QTextCursor::KeepAnchor);
        ui->txtConsole->redo();
    }
    if(added > 0){
        c.setPosition(pos + added, QTextCursor::KeepAnchor);
        //javaProcess->write(c.selectedText().toUtf8()+"\n\r");
    }
    //ui->txtConsole->appendPlainText("hey"+c.selectedText());
}

