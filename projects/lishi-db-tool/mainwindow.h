#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void outInfo(const QString & s);

    void outInfo(const std::string & s);

    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void dcBn1ClickedSlot();

    void dcBn2ClickedSlot();

    void dlBn1ClickedSlot();

    void on_dcLw1_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_dcLw2_currentRowChanged(int currentRow);

    void on_dcEd11_textChanged(const QString &arg1);

    void on_dcEd21_textChanged(const QString &arg1);

    void on_dcBn1_clicked();

    void on_dcBn61_clicked();

    void on_dcBn62_clicked();

    void on_dcBn63_clicked();

    void on_muDbExport_clicked();

    void on_muDbBackup_clicked();

private:
    void initData();

    void initUi();

    void initMenu();

    void setQss(const std::string& fn);

    void refreshDcMan(const std::string& sFilter);

    void refreshDcVeh(const std::string& sMan, const std::string& sFilter);

    void viewDcVeh(int index);

    void loadImage(int i, std::string& fn);

    void selectImage(int i);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
