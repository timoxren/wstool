#include <string>
#include "wsclient.h"
#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#define app_msg "messanger2"

QT_USE_NAMESPACE

WSClient::WSClient(QObject *parent) :
    QObject(parent)
    //countOfReconnectAttempts(0)
{


    connect(&m_webSocket, &QWebSocket::connected, this, &WSClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WSClient::stop);

    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &WSClient::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::sslErrors,           this, &WSClient::debugSslErrors);
    connect(&m_webSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(debugError(QAbstractSocket::SocketError)));


    connect(&pingSocketTimer, &QTimer::timeout, this, [=](){        
        //qDebug() << "ping" << endl;
        m_webSocket.ping();
    });
    connect(&connectTimer, &QTimer::timeout, this, [=] () {        
        qDebug() << "connect timeout" << endl;
        stop();
        connectingSocketError("QAbstractSocket::UnconnectedState");
    });
    connect(&m_webSocket, &QWebSocket::pong, [=] (quint64 elapsedTime, const QByteArray &payload) {
        //qDebug() << "pong income" << endl;
    });
    connectTimer.setSingleShot(true);
}

void WSClient::start(QString url)
{
    this->url = url;
    QUrl c_url(url);
    m_webSocket.open(c_url);
    connectTimer.start(CONNECT_TIMEROUT);
}


void WSClient::debugError(QAbstractSocket::SocketError error)
{
    if(error == QAbstractSocket::SslInternalError)
        return;

    qDebug() << "error:" << error << endl;
    connectingSocketError("error: " + error);
}

void WSClient::debugSslErrors(QList<QSslError> errors)
{    
    foreach (QSslError err, errors) {
        qDebug() << err.errorString();
        connectingSocketError("ssl error:" + err.errorString());
    }    
}

void WSClient::connectingSocketError(QString error)
{
    emit sgSocketConnectionError(error);
}

void WSClient::onConnected()
{
    qDebug() << "WebSocket connected, url:" << this->url << endl;
    connectTimer.stop();
    pingSocketTimer.start(PING_INTERVAL);
    emit sgConnectedToServer();
}

void WSClient::stop()
{
    qDebug() << "stoping all timers" << endl;
    pingSocketTimer.stop();    
    connectTimer.stop();
    m_webSocket.close();
    emit sgDisconnectedFromServer();
}

void WSClient::sendText(QString text)
{
    m_webSocket.sendTextMessage(text);
}

void WSClient::onTextMessageReceived(QString message)
{
    QString str(message);
    qDebug() << message << endl;
    emit textMessage(message);
}
