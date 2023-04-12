#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QVariant>
#include <QString>
#include <QStringList>
#include <QKeyEvent>
#include "QSqlQueryModel"
#include "QStringListModel"
#include <QAbstractItemView>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::setOrganizationName("Dream Team");
    QApplication::setApplicationName("lab2");
    setHistory=new QSettings("history.txt");
    settings=new QSettings("file.ini",QSettings::IniFormat);
    loadSettings();
    db=QSqlDatabase::addDatabase("QPSQL");
    load_data_base();
    dialog_window=new Dialog(this);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::slotShortcutENTER()
{
    QString command=ui->commandEdit->toPlainText();
    QSqlQuery query (db);
    if (!query.exec(command))
        ui->ErrorStr->setText(query.lastError().text());
    else
    {
        ui->ErrorStr->setText("Great job!");
        ui->LogList->insertPlainText(command);
        ui->LogList->insertPlainText("\n");
        QSqlQueryModel *model=new QSqlQueryModel(ui->tableView);
        model->setQuery(query);
        ui->tableView->setModel(model);
        QStringListModel*database_table=new QStringListModel(ui->listView);
        database_table->setStringList(db.tables());
        ui->listView->setModel(database_table);
    }
}

void MainWindow::keyPressEvent(QKeyEvent*event)
{
    if (event->key()==Qt::Key_Escape)
        close();
     else
        QMainWindow::keyPressEvent(event);
}

void MainWindow::saveSettings()
{

    settings->setValue("name",name);
    settings->setValue("IP",IP);
    settings->setValue("password",password);
    settings->setValue("login",login);
    settings->setValue("port",port);
    setHistory->setValue("history",ui->LogList->toPlainText());

}

void MainWindow::loadSettings()
{
    name=(settings->value("name",QString("fn1132_2021"))).toString();
    IP=(settings->value("IP",QString(""))).toString();
    password=(settings->value("password",QString(""))).toString();
    login=(settings->value("login",QString("student"))).toString();
    port=(settings->value("port",5432)).toInt();
    ui->LogList->insertPlainText((setHistory->value("history")).toString());

}

void MainWindow::on_GetButton_clicked()
{
    dialog_window->show();
}

void MainWindow::on_submitButton_clicked()
{
    QString command=ui->commandEdit->toPlainText();
    QSqlQuery query (db);
    if (!query.exec(command))
        ui->ErrorStr->setText(query.lastError().text());
    else
    {
        ui->ErrorStr->setText("Great job!");
        ui->LogList->insertPlainText(command);
        ui->LogList->insertPlainText("\n");
        QSqlQueryModel *model=new QSqlQueryModel(ui->tableView);
        model->setQuery(query);
        ui->tableView->setModel(model);
        QStringListModel*database_table=new QStringListModel(ui->listView);
        database_table->setStringList(db.tables());
        ui->listView->setModel(database_table);
    }
}

void MainWindow::on_clearButton_clicked()
{
    ui->commandEdit->clear();
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QString command="SELECT * FROM "+index.data().toString();
    QSqlQuery query (db);
    if (!query.exec(command))
        ui->ErrorStr->setText(query.lastError().text());
    else
    {
        ui->ErrorStr->setText("Great job!");
        QSqlQueryModel *model=new QSqlQueryModel(ui->tableView);
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
}


void MainWindow::on_actioninfo_triggered()
{
    Dialog openDia;
    if (openDia.exec() == QDialog::Accepted)
    {
        qDebug() << "Port is " << openDia.getport();
        qDebug() << "Name is " << openDia.getname();
        qDebug() << "Login is " << openDia.getlogin();
        qDebug() << "Passwort is " << openDia.getpassword();
        qDebug() << "IP is " << openDia.getIP();

        db.setDatabaseName(openDia.getname());
        db.setPort(openDia.getport());
        db.setUserName(openDia.getlogin());
        db.setPassword(openDia.getpassword());
        db.setHostName(openDia.getIP());

        if (!db.open()){
            ui->ErrorStr->setText(db.lastError().text());
        } else {
            ui->ErrorStr->setText("DataBase is opened.");
            settings->setValue("name",openDia.getname());
            settings->setValue("IP",openDia.getIP());
            settings->setValue("password",openDia.getpassword());
            settings->setValue("login",openDia.getlogin());
            settings->setValue("port",openDia.getport());
            openDia.savesettingsD();
        }

        dialog_window->close();
        QStringListModel*database_table=new QStringListModel(ui->listView);
        database_table->setStringList(db.tables());
        ui->listView->setModel(database_table);
    }
}

void MainWindow::load_data_base()
{
    db.setDatabaseName(name);
    db.setPort(port);
    db.setUserName(login);
    db.setPassword(password);
    db.setHostName(IP);

    if (!db.open()){
        ui->ErrorStr->setText(db.lastError().text());
    } else {
        ui->ErrorStr->setText("DataBase is opened.");
    }

    QStringListModel*database_table=new QStringListModel(ui->listView);
    database_table->setStringList(db.tables());
    ui->listView->setModel(database_table);
}

