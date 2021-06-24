#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QSqlTableModel>
#include <QAbstractItemView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    qDebug()<<QDir::currentPath(); //Показываем текущюю папку
//    QDir::setCurrent(qApp->applicationDirPath()); //Меняем текущюю папку на папку приложения
//    qDebug()<<QDir::currentPath(); //Показываем текущюю папку
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = qApp->applicationDirPath() + "/localDB/DB.db";
    qDebug() << path ;
    db.setDatabaseName(path);
    db.setUserName("root");
    if (!db.open()) {
        qDebug() << db.lastError().text();
        return;
    } else {
        qDebug() << "Success";
    }


    QSqlQueryModel* query = new QSqlQueryModel();
    query->setQuery("select * from buttonsName");
    for (int i = 0; i<query->rowCount(); i++) {
        Name.append(query->record(i).value("Name").toString());
    }
    ui->pushButton_1->setText(Name[0]);
    ui->pushButton_2->setText(Name[1]);
    ui->pushButton_3->setText(Name[2]);
    ui->pushButton_4->setText(Name[3]);
    ui->pushButton_5->setText(Name[4]);
    ui->pushButton_6->setText(Name[5]);
    ui->pushButton_7->setText(Name[6]);
    ui->pushButton_8->setText(Name[7]);



}

MainWindow::~MainWindow() {

    delete ui;
}


void MainWindow::on_saveButton_clicked() {
    model->submitAll();
}



void MainWindow::on_loadButton_clicked() {

    if (ui->r_checkBox->isChecked()) {
        pen.setRed(255);
    } else if(!ui->r_checkBox->isChecked()) {
        pen.setRed(0);
    }
    if (ui->g_checkBox->isChecked()) {
        pen.setGreen(255);
    } else if(!ui->g_checkBox->isChecked()) {
        pen.setGreen(0);
    }
    if (ui->b_checkBox->isChecked()) {
        pen.setBlue(255);
    } else if(!ui->b_checkBox->isChecked()) {
        pen.setBlue(0);
    }

    QSqlQueryModel* query = new QSqlQueryModel;
    query->setQuery("select * from set" + QString::number(id));
    QVector<double> X(query->rowCount()),Y(query->rowCount());
    for (int i = 0; i <query->rowCount(); i++) {
        X[i] = query->record(i).value("X").toDouble();

        if (i == 0) {
            Xmax = X[i];
            Xmin = X[i];
        } else if (Xmax < X[i]) {
            Xmax = X[i];
        }else if (Xmin > X[i]) {
            Xmin = X[i];
        }

        Y[i] = query->record(i).value("Y").toDouble();
        if (i == 0) {
            Ymax = Y[i];
            Ymin = Y[i];
        } else if (Ymax < Y[i]) {
            Ymax = Y[i];
        }else if (Ymin > Y[i]) {
            Ymin = Y[i];
        }
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(X, Y);

    ui->widget->graph(0)->setPen(pen);//задаем цвет точки

    //формируем вид точек
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    //Подписываем оси Ox и Oy

    ui->widget->xAxis->setLabel("X");
    ui->widget->yAxis->setLabel("Y");

    //Установим область, которая будет показываться на графике
    ui->widget->xAxis->setRange(Xmin-10, Xmax+10);//Для оси Ox
    ui->widget->yAxis->setRange(Ymin-10, Ymax+10);//Для оси Oy

    //И перерисуем график на нашем widget
    ui->widget->replot();
}



void MainWindow::on_addButton_clicked() {
    model->insertRow(model->rowCount());
}


void MainWindow::on_revertButton_clicked() {
    model->revertAll();
}


void MainWindow::on_deleteButton_clicked() {
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >=0) {
        model->removeRow(selectedRow);
    }
}

void MainWindow::on_renameButton_clicked() {
    if (but != Q_NULLPTR) {
        b.setModal(true);
        b.setFixedSize(310,80);

        b.show();
    }
}

void MainWindow::on_pushButton_1_clicked() {
    id = 1;
    QObject* Obj = const_cast<QObject*>(QObject::sender());
    but = dynamic_cast<QPushButton*>(Obj);
    b.setBut(but, id);

    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("set1");
    model->select();
    model->setHeaderData(1,Qt::Horizontal,tr("X"));
    model->setHeaderData(2, Qt::Horizontal, tr("Y"));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
}


void MainWindow::on_pushButton_2_clicked() {
    id = 2;
    QObject* Obj = const_cast<QObject*>(QObject::sender());
    but = dynamic_cast<QPushButton*>(Obj);
    b.setBut(but, id);

    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("set2");
    model->select();
    model->setHeaderData(1,Qt::Horizontal,tr("X"));
    model->setHeaderData(2, Qt::Horizontal, tr("Y"));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
}


void MainWindow::on_pushButton_3_clicked() {
    id = 3;
    QObject* Obj = const_cast<QObject*>(QObject::sender());
    but = dynamic_cast<QPushButton*>(Obj);
    b.setBut(but, id);

    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("set3");
    model->select();
    model->setHeaderData(1,Qt::Horizontal,tr("X"));
    model->setHeaderData(2, Qt::Horizontal, tr("Y"));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
}


void MainWindow::on_pushButton_4_clicked() {
    id = 4;
    QObject* Obj = const_cast<QObject*>(QObject::sender());
    but = dynamic_cast<QPushButton*>(Obj);
    b.setBut(but, id);

    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("set4");
    model->select();
    model->setHeaderData(1,Qt::Horizontal,tr("X"));
    model->setHeaderData(2, Qt::Horizontal, tr("Y"));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
}


void MainWindow::on_pushButton_5_clicked() {
    id = 5;
    QObject* Obj = const_cast<QObject*>(QObject::sender());
    but = dynamic_cast<QPushButton*>(Obj);
    b.setBut(but, id);

    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("set5");
    model->select();
    model->setHeaderData(1,Qt::Horizontal,tr("X"));
    model->setHeaderData(2, Qt::Horizontal, tr("Y"));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
}


void MainWindow::on_pushButton_6_clicked() {
    id = 6;
    QObject* Obj = const_cast<QObject*>(QObject::sender());
    but = dynamic_cast<QPushButton*>(Obj);
    b.setBut(but, id);

    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("set6");
    model->select();
    model->setHeaderData(1,Qt::Horizontal,tr("X"));
    model->setHeaderData(2, Qt::Horizontal, tr("Y"));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
}


void MainWindow::on_pushButton_7_clicked() {
    id = 7;
    QObject* Obj = const_cast<QObject*>(QObject::sender());
    but = dynamic_cast<QPushButton*>(Obj);
    b.setBut(but, id);

    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("set7");
    model->select();
    model->setHeaderData(1,Qt::Horizontal,tr("X"));
    model->setHeaderData(2, Qt::Horizontal, tr("Y"));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
}


void MainWindow::on_pushButton_8_clicked() {
    id = 8;
    QObject* Obj = const_cast<QObject*>(QObject::sender());
    but = dynamic_cast<QPushButton*>(Obj);
    b.setBut(but, id);

    model = new QSqlTableModel(this, db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("set8");
    model->select();
    model->setHeaderData(1,Qt::Horizontal,tr("X"));
    model->setHeaderData(2, Qt::Horizontal, tr("Y"));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
}

