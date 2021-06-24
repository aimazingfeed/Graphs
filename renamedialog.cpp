#include <QDebug>
#include <QDir>
#include <QtSql/QSqlError>
#include "renamedialog.h"
#include "ui_renamedialog.h"
renameDialog::renameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::renameDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle("Rename");
    lineText = "";
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = qApp->applicationDirPath();
    db.setDatabaseName(path +
                       "/localDB/DB.db");
    db.setUserName("root");
//    if (!db.open()) {
//        qDebug() << db.lastError().text();
//        return;
//    } else {
//        qDebug() << "Success";
//    }
}
QString renameDialog::getText() {
    return lineText;
}
renameDialog::~renameDialog() {
    delete ui;
}
void renameDialog::setBut(QPushButton *but, int id) {
    button = but;
    this->id = id;
}
void renameDialog::on_confirmButton_clicked() {
    lineText = ui->lineEdit->text();
    button->setText(lineText);
    QSqlQuery query;
    query.prepare("UPDATE buttonsName SET Name = (:Name) WHERE id = (:id)");
    query.bindValue(":Name",lineText);
    query.bindValue(":id", id);
    query.exec();
    ui->lineEdit->clear();
    close();
}

