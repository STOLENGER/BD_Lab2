#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <iostream>
#include <iostream>
#include <QVariant>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QKeyEvent>
#include <QPixmap>
#include <QPalette>
#include <QSplitter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap backgrnd(QCoreApplication::applicationDirPath() + "/imageformats/fonfordb2.jpg");
    backgrnd = backgrnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, backgrnd);
    this->setPalette(palette);
    ui->label_4->setStyleSheet("color: white");
    ui->label->setStyleSheet("color: white");
    ui->label_2->setStyleSheet("color: white");
    ui->label_3->setStyleSheet("color: white");
    ui->errorlist->setStyleSheet("color: white");
    connection = new Dialog(this);
    connect(connection, &Dialog::Done, this, &MainWindow::getallinfo);
    logList = new QStringList;
    this->setWindowTitle("DataBase Helper");
    db = QSqlDatabase::addDatabase("QPSQL");
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->loglist->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    QSplitter* splitter = new QSplitter(Qt::Orientation::Horizontal, this);
//    splitter->addWidget(ui->listView);
//    splitter->addWidget(ui->tableView);
//    splitter->addWidget(ui->loglist);
//    splitter->setStretchFactor(0,1);
//    splitter->setStretchFactor(1,1);
//    splitter->setStretchFactor(2,1);
//    QSplitter* splitter2 = new QSplitter(Qt::Orientation::Vertical, this);
//    splitter2->addWidget(splitter);
//    splitter2->addWidget(ui->tableView);
//    splitter2->addWidget(ui->label_4);
//    splitter2->addWidget(ui->queryexecs);
//    splitter2->setStretchFactor(0,1);
//    splitter2->setStretchFactor(1,1);
//    splitter2->setStretchFactor(2,1);
//    splitter2->setStretchFactor(3,1);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete logList;
    delete connection;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape)
        close();
    else
        QMainWindow::keyPressEvent(event);
}

void MainWindow::on_clearButton_clicked()
{
    ui->queryexecs->clear();
}

void MainWindow::on_runButton_clicked()
{
   connection->show();
}

void MainWindow::on_ubmitButton_clicked()
{
    db.setDatabaseName(nm);
    db.setHostName(ip);
    db.setUserName(user);
    db.setPort(port);
    db.setPassword(pass);
    if(!db.open())
        ui->errorlist->setText(db.lastError().text());
    QString cmd = ui->queryexecs->toPlainText();
    QSqlQuery query(db);
    if(!query.exec(cmd))
        ui->errorlist->setText(query.lastError().text());
    else
    {
        ui->errorlist->setText("Done!");
        logList->push_back(cmd);
        QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
        model->setQuery(query);
        ui->tableView->setModel(model);
        QStringListModel* logmodel = new QStringListModel(ui->loglist);
        logmodel->setStringList(*logList);
        ui->loglist->setModel(logmodel);
        QStringListModel* models = new QStringListModel(ui->listView);
        models->setStringList(db.tables());
        ui->listView->setModel(models);
        ui->errorlist->setText("All existing tables are shown!");
    }
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QSqlQuery query(db);
    if(!query.exec("SELECT * FROM " + index.data().toString()))
        ui->errorlist->setText(query.lastError().text());
    else
    {
        QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
        model->setQuery(query);
        ui->tableView->setModel(model);
    }
}

void MainWindow::on_loglist_doubleClicked(const QModelIndex &index)
{
    ui->queryexecs->clear();
    ui->queryexecs->insertPlainText(index.data().toString());
}

void MainWindow::getallinfo()
{
    nm = connection->Getname();
    ip = connection->Getip();
    user = connection->Getuser();
    port = connection->Getport();
    pass = connection->Getpass();
    db.setDatabaseName(nm);
    db.setHostName(ip);
    db.setUserName(user);
    db.setPort(port);
    db.setPassword(pass);
    if(!db.open())
        ui->errorlist->setText(db.lastError().text());
    else
    {
        ui->errorlist->setText("DataBase opened!");
        QStringListModel* model = new QStringListModel(ui->listView);
        model->setStringList(db.tables());
        ui->listView->setModel(model);
        ui->errorlist->setText("All existing tables are shown!");
    }
}
