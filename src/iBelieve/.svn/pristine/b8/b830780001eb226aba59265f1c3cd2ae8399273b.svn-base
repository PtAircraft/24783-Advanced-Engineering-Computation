#include "connection.h"

Connection::Connection(QObject *parent) : QObject(parent)
{

}

void Connection::SetServerAddress(QString sAddress, QString sPort)
{
    serverAddress = sAddress;
    serverPort = sPort;
}

void Connection::SetFileName(QString fName)
{
    fileName = fName;
}

void Connection::StartConnection(QTextEdit *browserErrMsg, QTextEdit *browserOutput)
{
    QFile sFile(fileName);
    QString text;

    QStringList paths = fileName.split("/");
    QString actualName = paths.at(paths.size()-1);

    QString runMode = browserOutput == nullptr ? "0" : "1";

    if (sFile.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&sFile);
        text = in.readAll();
        qDebug() << text;
        sFile.close();
    }


    socket = new QTcpSocket(this);

    qDebug() << "connecting...";

    socket->connectToHost(QHostAddress(serverAddress), serverPort.toUShort(nullptr, 10));

    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Error: " << socket->errorString();
        return;
    }


    qDebug() << "connected";

    QString buffer = actualName + runMode + text;
    socket->write(buffer.toStdString().c_str());

    // receive compile result
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(3000);
    qDebug() << "Reading: " << socket->bytesAvailable();

    QString compileResult = socket->readAll();
    qDebug() << compileResult;

    browserErrMsg->setPlainText(compileResult);


    // receive output
    if (browserOutput != nullptr && QString::compare(compileResult, "Compile Successfully!", Qt::CaseSensitive) == 0)
    {
        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();

        QString outputResult = socket->readAll();
        qDebug() << outputResult;

        browserOutput->setPlainText(outputResult);
    }

    socket->close();
}
