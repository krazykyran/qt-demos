#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget;

    window->setWindowTitle("My App");

    QPushButton *b1 = new QPushButton("One");
    QPushButton *b2 = new QPushButton("Two");
    QPushButton *b3 = new QPushButton("Three");

    QHBoxLayout *hl = new QHBoxLayout;
    QVBoxLayout *vl = new QVBoxLayout;

    vl->addWidget(b1);
    vl->addWidget(b2);
    vl->addWidget(b3);

    window->setLayout(vl);
    window->show();

    //QLabel *label = new QLabel("<h2>Hello <font color=red><i>World</i></font>!</h2>");

    //label->show();

    return app.exec();
}
