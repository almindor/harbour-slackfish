#include "slackstream.h"

#include <QJsonDocument>
#include <QJsonObject>

SlackStream::SlackStream(QObject *parent) : QObject(parent), isConnected(false), lastMessageId(0) {
    webSocket = new QtWebsocket::QWsSocket(this);
    checkTimer = new QTimer(this);

    connect(webSocket, SIGNAL(connected()), this, SLOT(handleListerStart()));
    connect(webSocket, SIGNAL(disconnected()), this, SLOT(handleListerEnd()));
    connect(webSocket, SIGNAL(frameReceived(QString)), this, SLOT(handleMessage(QString)));
    connect(checkTimer, SIGNAL(timeout()), this, SLOT(checkConnection()));
}

SlackStream::~SlackStream() {
    disconnect(webSocket, SIGNAL(disconnected()), this, SLOT(handleListerEnd()));

    if (!webSocket.isNull()) {
        webSocket->disconnectFromHost();
    }
}

void SlackStream::listen(QUrl url) {
    qDebug() << "Connect socket" << url;
    QString socketUrl = url.scheme() + "://" + url.host();
    webSocket->setResourceName(url.path());
    webSocket->connectToHost(socketUrl);
}

void SlackStream::checkConnection() {
    if (isConnected) {
        QJsonObject values;
        values.insert("id", QJsonValue(++lastMessageId));
        values.insert("type", QJsonValue(QString("ping")));

        qDebug() << "Check connection" << lastMessageId;

        QJsonDocument document(values);
        QByteArray data = document.toJson(QJsonDocument::Compact);
        webSocket->write(QString(data));
    }
}

void SlackStream::handleListerStart() {
    qDebug() << "Socket connected";
    emit connected();
    isConnected = true;
    checkTimer->start(15000);
}

void SlackStream::handleListerEnd() {
    qDebug() << "Socket disconnected";
    checkTimer->stop();
    isConnected = false;
    lastMessageId = 0;
    emit disconnected();
}

void SlackStream::handleMessage(QString message) {
    qDebug() << "Got message" << message;

    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(message.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Failed to parse message" << message;
        return;
    }

    emit messageReceived(document.object());
}
