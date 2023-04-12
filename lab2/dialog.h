#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSettings>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString getname();
    QString getIP();
    QString getpassword();
    QString getlogin();
    int getport();
    void savesettingsD();
    void loadsettingsD();
    QSettings *settings;


private slots:
    void on_PushButton_clicked();
    void on_cancelButton_clicked();


private:
    Ui::Dialog *ui;
    QString name;
    QString IP;
    QString login;
    QString password;
    int port;
};

#endif // DIALOG_H
