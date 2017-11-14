#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QFile>
#include <QTextEdit>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = 0);
    void StartConnection(QTextEdit *browserErrMsg, QTextEdit *browserOutput);

    void SetServerAddress(QString sAddress, QString sPort);
    void SetFileName(QString fName);

signals:

public slots:

private:
    QTcpSocket *socket;
    QString fileName;
    QString serverAddress;
    QString serverPort;
};

#endif // CONNECTION_H
