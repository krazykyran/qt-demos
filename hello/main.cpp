#include <QCoreApplication>
#include <QDebug>

class MainClass : public QObject
{
Q_OBJECT
public:
    explicit MainClass(QObject *parent = 0) : QObject(parent) { }
public slots:
    void Run()
    {
        qDebug() << "Hello World!!!" << endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MainClass myMain;

    QMetaObject::invokeMethod(&myMain, "Run", Qt::QueuedConnection );

/*    qDebug() << "Hello World!!!" << endl;
*/
    return a.exec();
}
