#include <QApplication>
#include <QtGui>
#include <QtCore>
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget;

    window->setWindowTitle("My App");

    QGridLayout *layout = new QGridLayout;

    QLabel *lblName = new QLabel("Name:");
    QLineEdit *txtName = new QLineEdit;

    QLabel *lblName2 = new QLabel("Name:");
    QLineEdit *txtName2 = new QLineEdit;

    QPushButton *btn = new QPushButton("Ok");

    layout->addWidget(lblName,0,0);
    layout->addWidget(txtName,0,1);

    layout->addWidget(lblName2,1,0);
    layout->addWidget(txtName2,1,1);

    layout->addWidget(btn,3,0,1,2);
    window->setLayout(layout);

    window->show();

    return app.exec();
}
