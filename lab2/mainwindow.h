#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QSettings> //для того ,чтобы реальзовать открытие базы данных по умолчанию и сохранение валидных данных
#include <QMainWindow>
#include <QShortcut>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent*event) override;
    void saveSettings();//для сохранения
    void loadSettings ();//для загрузки

private slots:
    void on_GetButton_clicked();

    void on_submitButton_clicked();

    void on_clearButton_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_actioninfo_triggered();

    void load_data_base();

    void slotShortcutENTER();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QDialog*dialog_window;
    QString name;
    QString IP;
    QString login;
    QString password;
    int port;
    QSettings *settings;
    QSettings *setHistory;
    QShortcut *keyENTER;
};
#endif // MAINWINDOW_H
