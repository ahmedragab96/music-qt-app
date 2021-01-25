#ifndef ADDCDSCREEN_H
#define ADDCDSCREEN_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QMainWindow>

namespace Ui {
class AddCDScreen;
}

class AddCDScreen : public QDialog
{
    Q_OBJECT

public:
    explicit AddCDScreen(QWidget *parent = nullptr);
    ~AddCDScreen();

private slots:
    void on_AddCDButton_accepted();

private:
    Ui::AddCDScreen *ui;
};

#endif // ADDCDSCREEN_H
