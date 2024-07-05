#include "mainwindow.h"
#include"global.h"
#include <QApplication>
#include<QString>

void checkAndCreateFile(const QString &filePath) {
    QFile file(filePath);

    if (file.exists()) {
        qDebug() << "File" << filePath << "exists.";
    } else {
        qDebug() << "File" << filePath << "does not exist. Creating...";

        // Create file
        if (file.open(QIODevice::WriteOnly)) {
            qDebug() << "File created successfully.";
            file.close();
        } else {
            qDebug() << "Failed to create file!";
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString runPath = QCoreApplication::applicationDirPath() + filename;
    runPath.replace(QString("/"),QString("\\"));
    checkAndCreateFile(runPath);

    MainWindow w;
    w.show();
    return a.exec();
}

