#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QTimer>

#ifndef WSCLIENT
#define WSCLIENT

class WSClient : public QObject
{
    Q_OBJECT
public:
    explicit WSClient(QObject *parent = Q_NULLPTR);

public slots:
    void onConnected();

    void start(QString url);
    void stop();    

    void debugError(QAbstractSocket::SocketError error);
    void debugSslErrors(QList<QSslError> errors);

    void connectingSocketError(QString error);    
    void onTextMessageReceived(QString message);
    void sendText(QString);

private slots:

signals:
    void textMessage(QString msg);
    void sgSocketConnectionError(QString);
    void sgConnectedToServer();
    void sgDisconnectedFromServer();

private:

    QWebSocket  m_webSocket;    
    QTimer      pingSocketTimer;        
    QTimer      connectTimer;

    QString     url;

    const int   PING_INTERVAL = 5000;
    const int   CONNECT_TIMEROUT = 10000;

};

#endif // WSCLIENT
