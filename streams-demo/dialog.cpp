#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->btnStop->setEnabled(false);
    ui->btnStart->setFocus();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setStarted(bool started)
{
    if(started)
    {
        ui->btnStart->setEnabled(false);
        ui->btnStop->setEnabled(true);
        ui->btnStop->setFocus();
    }
    else
    {
        ui->btnStart->setEnabled(true);
        ui->btnStop->setEnabled(false);
        ui->btnStart->setFocus();
    }
}

void Dialog::on_btnStart_clicked()
{
    if (m_server.listen(QHostAddress::AnyIPv4, ui->spinBox->value())) {
        qDebug() << this << "server started";
        setStarted(true);
    }
    else {
        qCritical() << this << m_server.errorString();
        setStarted(false);
    }


}

void Dialog::on_btnStop_clicked()
{
    m_server.close();
    setStarted(false);
}
