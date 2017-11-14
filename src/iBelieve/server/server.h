#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QProcess>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QString port, QObject *parent = 0);

signals:

public slots:
    void newConnection();

private:
    QTcpServer *server;

    void parseFileInfo(QString &buffer, QString &fileName, bool &runMode);
    void compile(QString className, QTcpSocket *socket);
    void runJava(QString className, QTcpSocket *socket);
};

#endif // SERVER_H
