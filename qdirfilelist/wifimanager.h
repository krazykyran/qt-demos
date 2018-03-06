#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <QObject>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QSet>

class WifiManager : public QObject
{
    Q_OBJECT
public:
    explicit WifiManager(QObject *parent = 0);
    ~WifiManager();

    void init();
signals:
    void sendMacAddress(QByteArray mac);
    void finished();

public slots:
    void timerEvent(QTimerEvent *event);
    int readCaptureFile(QString filepath);
    void printMacAddress(QByteArray mac);

private:
    QSet<QByteArray> m_macSet;
    int m_timerID;

    QString m_pathName;
    QString m_fileName;
    QString m_pathFileName;
};

#endif // WIFIMANAGER_H
