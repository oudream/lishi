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

private slots:
    void dcBn1ClickedSlot();

    void dcBn2ClickedSlot();

    void dlBn1ClickedSlot();

    void on_dcEd1_textChanged(const QString &arg1);

    void on_dcLw1_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_dcLw2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_buPathBn_clicked();

    void on_buRunBn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
