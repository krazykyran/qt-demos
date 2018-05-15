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

    map.insert("00:00:00:00:00:01",-63);
    map.insert("00:00:00:00:00:02",-51);
    map.insert("00:00:00:00:00:03",-28);
    map.insert("00:00:00:00:00:04",-50);

    map.insert("00:00:00:00:00:0a",-51);
    map.insert("00:00:00:00:00:0A",-52);
    map.insert("00:00:00:00:00:ee",-53);
    map.insert("00:00:00:00:00:EE",-54);

    map.insert("00:00:00:00:00:01",-60);

//    foreach(QByteArray mac, set) {
//        qout << mac << endl;
//    }

    QMapIterator<QByteArray, int> i(map);
    while (i.hasNext()) {
        i.next();
        qout << i.key() << " : " << i.value() << endl;
    }

}
