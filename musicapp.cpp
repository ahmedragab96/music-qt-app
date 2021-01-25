#include "musicapp.h"
#include "ui_musicapp.h"
#include "addcdscreen.h"

musicapp::musicapp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::musicapp)
{
    ui->setupUi(this);
    ui->authorSearchText->setPlaceholderText("Author Name...");
    ui->genreSearchText->setPlaceholderText("Music Style...");
    ui->yearSearchText->setPlaceholderText("Production Year...");
    connect(ui->searchButton, &QPushButton::clicked,this, &musicapp::on_search_button_clicked);

    this->updateCDsTable();
}

musicapp::~musicapp()
{
    delete ui;
}


void musicapp::on_search_button_clicked()
{
    QString authorSearchValue = ui->authorSearchText->toPlainText();
    QString genreSearchValue = ui->genreSearchText->toPlainText();
    QString yearSearchValue = ui->yearSearchText->toPlainText();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/ragab/Documents/musicapp.db");

    if (!db.open()) {
        QMessageBox::information(this, "Connection", "Error connecting to database");
    }

    QSqlQuery query(db);
    QString queryString;
    if (authorSearchValue == "" && genreSearchValue == "" && yearSearchValue == "") {
        queryString = "SELECT * FROM musicCDs";
    } else {
        queryString = "SELECT * FROM musicCDs WHERE author_name LIKE '%" + authorSearchValue + "%' AND production_year LIKE '%" + yearSearchValue + "%' AND music_style LIKE '%" + genreSearchValue + "%'";
    }
    if (!query.exec(queryString)) {
        qDebug() << "Failed";
    }

    ui->musicTable->clearContents();
    ui->musicTable->setRowCount(0);

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

void musicapp::on_pushButton_clicked()
{
    AddCDScreen addCDScreen;
    addCDScreen.setModal(true);
    addCDScreen.exec();
}

void musicapp::updateCDsTable() {

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

    ui->musicTable->clearContents();
    ui->musicTable->setRowCount(0);

    qDebug() << "heree";

    ui->musicTable->setColumnCount(5);
    QStringList labels;
    labels << " " << "CD Name" << "Author Name" << "Genre" << "Year";
    ui->musicTable->setHorizontalHeaderLabels(labels);


    int rowCount = 0;
    while(query.next()) {
        qDebug() << query.value(1).toString();
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

    qDebug() << "heree";
}
