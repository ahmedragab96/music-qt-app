#include "addcdscreen.h"
#include "ui_addcdscreen.h"
#include "ui_musicapp.h"
#include "musicapp.h"

AddCDScreen::AddCDScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCDScreen)
{
    ui->setupUi(this);
}

AddCDScreen::~AddCDScreen()
{
    delete ui;
}

void AddCDScreen::on_AddCDButton_accepted()
{
    QString cdName = ui->cdNameField->text();
    QString authorName = ui->authorNameField->text();
    QString genre = ui->genreField->text();
    int year = ui->yearField->text().toInt();

    qDebug() << cdName << authorName << genre << year;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/ragab/Documents/musicapp.db");

    if (!db.open()) {
        QMessageBox::information(this, "Connection", "Error connecting to database");
    }

    QSqlQuery query(db);
    QString queryString;
    if (cdName == "" || authorName == "" || genre == "" || year == 0) {
         QMessageBox::information(this, "Error", "Plese fill all fields !!");
    } else {
        queryString = "INSERT INTO musicCDs (cd_name, author_name, music_style, production_year) VALUES ('"+ cdName +"', '"+ authorName +"', '"+ genre +"', '"+ year +"')";
        qDebug() << queryString;
        if (!query.exec(queryString)) {
            qDebug() << "Failed";
        }
    }

    musicapp* mu = new musicapp();

    mu->updateCDsTable();
}
