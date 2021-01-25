#ifndef MUSICAPP_H
#define MUSICAPP_H

#include <QMainWindow>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class musicapp; }
QT_END_NAMESPACE

class musicapp : public QMainWindow
{
    Q_OBJECT

public:
    musicapp(QWidget *parent = nullptr);
    void updateCDsTable();
    ~musicapp();

private slots:
    void on_search_button_clicked();
    void on_pushButton_clicked();

private:
    Ui::musicapp *ui;
};
#endif // MUSICAPP_H
