#include "widget.h"
#include "ui_widget.h"
#include "wsclient.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::connectServer()
{
    QString str = ui->lineEdit->text();
    emit openConnection(str);
}

void Widget::serverOk()
{
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    addLine("Connected to server");
}

void Widget::closeServer()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    emit closeConnection();
}

void Widget::serverError()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

void Widget::sendToServerClick()
{
    QString str = ui->lineEdit_2->text();
    if (str.length() > 0) {
        emit sendToServer(str);
    }
}

void Widget::addLine(QString str)
{
    ui->textBrowser->append(str);
}

void Widget::on_pushButton_clicked()
{
    connectServer();
}

void Widget::on_pushButton_3_clicked()
{
    closeServer();
}

void Widget::on_pushButton_2_clicked()
{
    sendToServerClick();
}

void Widget::on_pushButton_4_clicked()
{
    ui->textBrowser->clear();
}
