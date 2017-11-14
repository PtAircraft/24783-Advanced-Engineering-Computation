#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc < 2)
    {
        qDebug() << "Usage: <port>";
        exit(0);
    }

    QString port(argv[1]);
    qDebug() << port;
    Server myServer(port);

    return a.exec();
}
