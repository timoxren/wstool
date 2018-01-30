#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void openConnection(QString);
    void closeConnection();
    void sendToServer(QString);

public slots:
    void connectServer();
    void closeServer();
    void serverError();
    void sendToServerClick();
    void serverOk();
    void addLine(QString str);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
