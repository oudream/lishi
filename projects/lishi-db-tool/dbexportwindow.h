#ifndef DBEXPORTWINDOW_H
#define DBEXPORTWINDOW_H

#include <QDialog>

namespace Ui {
class DbExportWindow;
}

class DbExportWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DbExportWindow(QWidget *parent = nullptr);
    ~DbExportWindow();

private slots:
    void on_epBn1_clicked();

    void on_epBn2_clicked();

private:
    Ui::DbExportWindow *ui;
};

#endif // DBEXPORTWINDOW_H
