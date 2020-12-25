#include "musicapp.h"
#include "ui_musicapp.h"

musicapp::musicapp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::musicapp)
{
    ui->setupUi(this);

    QStringList drivers = QSqlDatabase::drivers();
   foreach(QString driver, drivers)
   qDebug()<<driver;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/ragab/Documents/musicapp.db");

    if (db.open()) {
        qDebug() << "Database is connected";
        QSqlQuery qry;
        qry.prepare("SELECT * FROM musicCDs");
        if (qry.exec()) {
            qDebug() << "exec qry";
            while(qry.next()) {
                qDebug() << qry.value(1).toString();
            }
        }
    } else {
        QMessageBox::information(this, "Connection", "Database is not connected");
    }

}

musicapp::~musicapp()
{
    delete ui;
}

