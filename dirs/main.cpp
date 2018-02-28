#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDir mDir("/home/engineer");

    qDebug() << mDir.exists();

    foreach (QFileInfo mItem, mDir.drives())
    {
        qDebug() << mItem.absoluteFilePath();
    }

    QString mPath = "/home/engineer/qt-test";

    if (!mDir.exists(mPath))
    {
        mDir.mkpath(mPath);
        qDebug() << "Created " << mPath;
    }
    else
    {
        qDebug() << "Already exists";
    }

    foreach (QFileInfo mItem2, mDir.entryInfoList())
    {
        // qDebug() << mItem2.absoluteFilePath();
        if (mItem2.isDir())  qDebug() << "\033[1;32mDir:\033[0m  " << mItem2.fileName();
        if (mItem2.isFile()) qDebug() << "\033[1;34mFile:\033[0m " << mItem2.fileName();
    }

    qCritical() << "Dirs console app sent a critial message ...";

    fprintf(stdout, "Informative message from Dir console app ...\n");

    // return a.exec();
    a.quit();
}
