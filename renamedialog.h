#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H
#include <QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QDialog>
#include <QtSql/QSqlDatabase>
namespace Ui {
class renameDialog;
}

class renameDialog : public QDialog {
    Q_OBJECT

public:
    explicit renameDialog(QWidget *parent = nullptr);
    ~renameDialog();
    QString getText();
    void setBut(QPushButton* but, int id);

private slots:
    void on_confirmButton_clicked();
private:
    QSqlDatabase db;
    Ui::renameDialog *ui;
    QString lineText;
    QPushButton* button;
    int id;
};

#endif // RENAMEDIALOG_H
