#include "wifimanager.h"

extern QTextStream qout;
extern QTextStream qerr;

WifiManager::WifiManager(QObject *parent) : QObject(parent)
{
    qout << "WifiManager: constructor ..." << endl;
}

WifiManager::~WifiManager()
{
    qout << "WifiManager: destructor ..." << endl;
}

void WifiManager::init()
{
    m_macSet.clear();

    connect(this, SIGNAL(sendMacAddress(QByteArray)),
            this, SLOT(printMacAddress(QByteArray)));


    m_pathName = "/run/addinsight/";
    qout << "WifiManager: setting path name to: " << m_pathName << endl;

    m_timerID = startTimer(100);
}

void WifiManager::timerEvent(QTimerEvent *event)
{
    static int count = 0;

    if (count > 1) {
        QDir dir = QDir(m_pathName);

        QStringList fileList = dir.entryList(QDir::Files, QDir::Time);
        if (fileList.empty()) {
            qout << "no files exist in path " << dir.absolutePath() << endl;
            return;
        }

        foreach (QString fileName, fileList) {
            m_fileName = fileName;
            QString pathFileName = m_pathName + fileName;

            readCaptureFile(pathFileName);
//            QDir.remove(pathFileName);
        }
    }

    if (count == 10)
        emit finished();
    count++;
}

int WifiManager::readCaptureFile(QString filepath)
{
    qout << "WifiManager: reading capture filename: " << filepath << endl;

    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qerr << "cannot open file for reading!" << endl;
        return EXIT_FAILURE;
    }

    bool stationMacReached = false;
    QByteArray mac;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (stationMacReached) {
            QStringList parts = line.split(",");
            if (parts.count() > 0) {
                mac = parts.first().toLocal8Bit();
                if (mac.length() == 17) {
                    if (!m_macSet.contains(mac)) {
                        emit sendMacAddress(mac);
                        m_macSet.insert(mac);
                    }
                }
            }
        } else {
            if (line.startsWith("Station MAC"))
                stationMacReached = true;
        }
    }

    file.close();
    stationMacReached = false;
    return EXIT_SUCCESS;
}

void WifiManager::printMacAddress(QByteArray mac)
{
    qout << "WF:" << mac << endl;
}
