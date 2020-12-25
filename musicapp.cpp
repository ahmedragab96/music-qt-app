#include "musicapp.h"
#include "ui_musicapp.h"

musicapp::musicapp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::musicapp)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/ragab/Documents/musicapp.db");

    if (!db.open()) {
        QMessageBox::information(this, "Connection", "Error connecting to database");
    }

    QSqlQuery query(db);
    QString queryString = "SELECT * FROM musicCDs";
    if (!query.exec(queryString)) {
        qDebug() << "Failed";
    }

    ui->musicTable->setColumnCount(5);
    QStringList labels;
    labels << " " << "CD Name" << "Author Name" << "Genre" << "Year";
    ui->musicTable->setHorizontalHeaderLabels(labels);

    int rowCount = 0;
    while(query.next()) {
        ui->musicTable->insertRow(rowCount);
        QTableWidgetItem *cd_name = new QTableWidgetItem;
        QTableWidgetItem *author_name = new QTableWidgetItem;
        QTableWidgetItem *genre = new QTableWidgetItem;
        QTableWidgetItem *year = new QTableWidgetItem;

        cd_name->setText(query.value(1).toString());
        author_name->setText(query.value(2).toString());
        genre->setText(query.value(3).toString());
        year->setText(query.value(4).toString());

        ui->musicTable->setItem(rowCount, 1, cd_name);
        ui->musicTable->setItem(rowCount, 2, author_name);
        ui->musicTable->setItem(rowCount, 3, genre);
        ui->musicTable->setItem(rowCount, 4, year);

        rowCount++;
    }
}

musicapp::~musicapp()
{
    delete ui;
}

