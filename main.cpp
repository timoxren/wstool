#include "widget.h"
#include "wsclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget* w = new Widget();
    WSClient* ws = new WSClient();

    QObject::connect(w, SIGNAL(openConnection(QString)), ws, SLOT(start(QString)));
    QObject::connect(w, SIGNAL(closeConnection()), ws, SLOT(stop()));
    QObject::connect(ws, SIGNAL(sgDisconnectedFromServer()), w, SLOT(serverError()));
    QObject::connect(ws, SIGNAL(sgConnectedToServer()), w, SLOT(serverOk()));

    QObject::connect(w, SIGNAL(sendToServer(QString)), ws, SLOT(sendText(QString)));
    QObject::connect(ws,SIGNAL(textMessage(QString)), w, SLOT(addLine(QString)));

    QObject::connect(ws, &WSClient::sgSocketConnectionError, [=] (QString err) {
        w->addLine("Error: " + err);
    });

    w->show();
    return a.exec();
}
