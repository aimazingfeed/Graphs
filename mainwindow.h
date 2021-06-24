#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDir>
#include <QWidget>
#include <QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include "renamedialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_addButton_clicked();

    void on_revertButton_clicked();

    void on_deleteButton_clicked();

    void on_renameButton_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    int id;
    Ui::MainWindow *ui;
    QSqlTableModel* model;
    QSqlDatabase db;
    QColor pen = QColor(0,0,0,255);
    QPushButton *but = Q_NULLPTR;
    renameDialog b;
    QVector<QString> Name;
    double Xmax,Xmin,Ymax,Ymin;
};
#endif // MAINWINDOW_H
