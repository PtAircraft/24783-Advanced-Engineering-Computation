#include "server.h"

Server::Server(QString port, QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any, port.toUInt()))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started";
    }
}

void Server::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();

    socket->waitForReadyRead(3000);

    QString buffer = socket->readAll();
    QString className;
    bool runMode;
    parseFileInfo(buffer, className, runMode);

    QFile sFile(className + ".java");
    if (sFile.open(QFile::WriteOnly | QFile::Text))
    {
        sFile.write(buffer.toStdString().c_str());
        sFile.flush();
        sFile.close();
    }

    compile(className, socket);
    if (runMode)
    {
        runJava(className, socket);
    }

    socket->close();
}

void Server::parseFileInfo(QString &buffer, QString &className, bool &runMode)
{
    QString suffix = ".java";
    int start = buffer.indexOf(suffix, 0, Qt::CaseInsensitive);
    className = buffer.left(start);
    buffer.remove(0, start + suffix.length());

    runMode = (buffer[0] == QChar('1'));
    buffer.remove(0, 1);
}

void Server::compile(QString className, QTcpSocket *socket)
{
    QProcess *p = new QProcess(this);
    p->start("javac", QStringList() << className + ".java");
    while (false == p->waitForFinished()) ;

    QString compileResult = p->readAllStandardError();
    if (compileResult.length() <= 0)
    {
        compileResult = "Compile Successfully!";
    }

    qDebug() << compileResult;

    socket->write(compileResult.toStdString().c_str());
    socket->flush();
}

void Server::runJava(QString className, QTcpSocket *socket)
{
    QProcess *p = new QProcess(this);
    p->start("java", QStringList() << className);
    while (false == p->waitForFinished()) ;

    QString runResult = p->readAllStandardOutput();
    qDebug() << runResult;

    socket->write(runResult.toStdString().c_str());
    socket->flush();
}
