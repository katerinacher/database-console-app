#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include <QSettings>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    settings=new QSettings("file.ini",QSettings::IniFormat);
    ui->setupUi(this);
    loadsettingsD();
    ui->PasswordEdit->setEchoMode(QLineEdit::Password);

}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getname()
{
    return name;
}

QString Dialog::getIP()
{
    return IP;
}

QString Dialog::getpassword()
{
    return password;
}

QString Dialog::getlogin()
{
    return login;
}

int Dialog::getport()
{
    return port;
}

void Dialog::savesettingsD()
{
    settings->setValue("name",name);
    settings->setValue("IP",IP);
    settings->setValue("password",password);
    settings->setValue("login",login);
    settings->setValue("port",port);

}

void Dialog::loadsettingsD()
{
    name=(settings->value("name",QString(""))).toString();
    IP=(settings->value("IP",QString(""))).toString();
    password=(settings->value("password",QString(""))).toString();
    login=(settings->value("login",QString(""))).toString();
    port=(settings->value("port",0)).toInt();
    ui->NameEdit->setText(name);
    ui->IPEdit->setText(IP);
    ui->LoginEdit->setText(login);
    ui->PasswordEdit->setText(password);
    QString str;
    str.setNum(port);
    ui->PortEdit->setText(str);
}

void Dialog::on_PushButton_clicked()
{
    name=ui->NameEdit->text();
    IP=ui->IPEdit->text();
    login=ui->LoginEdit->text();
    password=ui->PasswordEdit->text();
    port=ui->PortEdit->text().toInt();
    accept();
}


void Dialog::on_cancelButton_clicked()
{
    reject();
}
