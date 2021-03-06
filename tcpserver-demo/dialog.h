#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "streamsserver.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    void setStarted(bool started);

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

private:
    Ui::Dialog *ui;
    StreamsServer m_server;
};

#endif // DIALOG_H
