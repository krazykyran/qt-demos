#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtCore>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statLabel = new QLabel(this);
    statLabel->setText("Hello World!");

    statProgress = new QProgressBar(this);
    statProgress->setTextVisible(false);
    statProgress->setValue(10);

    ui->statusBar->addPermanentWidget(statLabel);
    ui->statusBar->addPermanentWidget(statProgress);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDo_Something_triggered()
{
    ui->statusBar->showMessage("Hello",2000);
    int i;
    i = statProgress->value() + 10;
    if (i >= 100)
        i=0;
    statProgress->setValue(i);
}

void MainWindow::on_pushButton_clicked()
{
    //info
    QMessageBox::information(this,
                             "Title Here",
                             "Text Here");
}

void MainWindow::on_pushButton_2_clicked()
{
    //question
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                          "Title Here",
                          "Do you like cats?",
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        ui->statusBar->showMessage("You LOVE Cats!",5000);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    //warning
    QMessageBox::warning(this,
                         "Title Here",
                         "Text Here");
}

void MainWindow::on_pushButton_4_clicked()
{
    //custom
    QMessageBox::question(this,
                          "My Title",
                          "My Question Here",
                          QMessageBox::YesToAll | QMessageBox::Yes | QMessageBox::No | QMessageBox::NoToAll);
}
