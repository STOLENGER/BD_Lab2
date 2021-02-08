#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("DataDase Connection Master");
    QFile file;
        if(file.exists("myfile.txt"))
        {
            ReadFromFile();
            ui->lineEdit->insert(name);
            ui->lineEdit_3->insert(ip);
            ui->lineEdit_2->insert(user);
            ui->lineEdit_4->insert(pass);
            ui->lineEdit_5->insert(QString::number(port));
        }
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::Getname()
{
    return name;
}

QString Dialog::Getip()
{
    return ip;
}

QString Dialog::Getuser()
{
    return user;
}

int Dialog::Getport()
{
    return port;
}

QString Dialog::Getpass()
{
    return pass;
}

void Dialog::RecordInFile()
{

    QFile file("myfile.txt");
    if(file.exists())
    {
        file.close();
        file.remove();
    }
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Error in File oppening";
    } else
     {
       QTextStream out(&file);
       out<<Getname()<<Qt::endl;
       out<<Getip()<<Qt::endl;
       out<<Getuser()<<Qt::endl;
       out<<Getport()<<Qt::endl;
       out<<Getpass()<<Qt::endl;
    }
    file.close();
}

void Dialog::ReadFromFile()
{
    QFile file("myfile.txt");

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Ошибка при открытии файла";
    } else {

        QTextStream text(&file);
        name = text.readLine();
        ip=text.readLine();
        user=text.readLine();
        port=text.readLine().toInt();
        pass=text.readLine();
    }

}
void Dialog::on_pushButton_clicked()
{
    name = ui->lineEdit->text();
    ip = ui->lineEdit_3->text();
    user = ui->lineEdit_2->text();
    port = ui->lineEdit_5->text().toInt();
    pass = ui->lineEdit_4->text();
    RecordInFile();
    emit Done();
    close();
}
