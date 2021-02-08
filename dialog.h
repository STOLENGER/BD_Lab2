#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString Getname();
    QString Getip();
    QString Getuser();
    int Getport();
    QString Getpass();
    void RecordInFile();
    void ReadFromFile();

private slots:
    void on_pushButton_clicked();
signals:
    void Done();

private:
    Ui::Dialog *ui;
    QString name;
    QString ip;
    QString user;
    int port;
    QString pass;
};

#endif // DIALOG_H
