#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <dialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * event) override;

private slots:
    void on_clearButton_clicked();

    void on_runButton_clicked();

    void on_ubmitButton_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_loglist_doubleClicked(const QModelIndex &index);
public slots:
    void getallinfo();
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QStringList* logList;
    Dialog* connection;
    QString nm;
    QString ip;
    QString user;
    int port;
    QString pass;
};
#endif // MAINWINDOW_H
