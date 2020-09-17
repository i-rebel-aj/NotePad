#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QDir>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->Main_Page);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionSave_triggered()
{
    //Error Checking Goes here....
    if(file_path.isEmpty()){
        //Call save as
        MainWindow::on_actionSave_As_triggered();
    }else{
        QFile file(file_path);
        if(!file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::critical(this, "Bhaiwa Text" ,"Something went wrong");
        }else{
            QTextStream out(&file);
            QString text= ui->Main_Page->toPlainText();
            out<<text;
            file.flush();
            file.close();
            QMessageBox::information(this, "Bhaiwa Text", "File Saved Successfully");
        }
    }
}
void MainWindow::on_actionOpen_triggered()
{
    QString filename= QFileDialog::getOpenFileName(this,"Open a file", QDir::homePath());
    if(filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::critical(this, "Bhaiwa Text" ,"Something went wrong");
    }else{
        file_path=filename;
        QTextStream in(&file);
        QString text=in.readAll();
        ui->Main_Page->setText(text);
        file.close();
    }
}
void MainWindow::on_actionSave_As_triggered()
{
    QString filename= QFileDialog::getSaveFileName(this, "Save As","");
    //QMessageBox::information(this, "Debug output", filename);
    QFile file(filename);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::critical(this, "Bhaiwa Text" ,"Something went wrong");
    }else{
        file_path=filename;
        QTextStream out(&file);
        QString text= ui->Main_Page->toPlainText();
        out<<text;
        file.flush();
        file.close();
        QMessageBox::information(this, "Bhaiwa Text", "File Saved Successfully");
    }
}
void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}
void MainWindow::on_actionNew_triggered()
{
    file_path="";
    ui->Main_Page->setText("");
}
