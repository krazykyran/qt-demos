#include <QCoreApplication>
#include <QTextStream>
#include <QSet>
#include <QMap>
#include <QMapIterator>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    return a.exec();

    QTextStream qout(stdout);

    qout << "hello mac mapper ..." << endl;
    qout << "i have 3 macs to report:" << endl;

    QMap<QByteArray, int> map;
//    QSet<QByteArray> set;

    map.insert("00:00:00:00:00:01",1);
    map.insert("00:00:00:00:00:02",1);
    map.insert("00:00:00:00:00:03",1);

//    set << "00:00:00:00:00:04";

//    set << "00:00:00:00:00:01";

//    foreach(QByteArray mac, set) {
//        qout << mac << endl;
//    }

    QMapIterator<QByteArray, int> i(map);
    while (i.hasNext()) {
        i.next();
        qout << i.key() << " : " << i.value() << endl;
    }

}
