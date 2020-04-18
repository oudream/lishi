#ifndef DBBACKUPWINOW_H
#define DBBACKUPWINOW_H

#include <QDialog>

namespace Ui {
class DbBackupWindow;
}

class DbBackupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DbBackupWindow(QWidget *parent = nullptr);
    ~DbBackupWindow();

private slots:
    void on_buBackupBn_clicked();

    void on_buRestoreBn_clicked();

private:
    Ui::DbBackupWindow *ui;
    std::string _backupPath;

};

#endif // DBBACKUPWINOW_H
