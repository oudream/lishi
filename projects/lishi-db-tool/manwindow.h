#ifndef MANWINDOW_H
#define MANWINDOW_H

#include <QDialog>

namespace Ui {
class ManWindow;
}

class ManWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ManWindow(QWidget *parent = nullptr);
    ~ManWindow();

    bool eventFilter(QObject *watched, QEvent *event);

    int sqlResult;

private slots:
    void on_maBn1_clicked();

    void on_maBn2_clicked();

private:
    Ui::ManWindow *ui;
    QImage _image;
};

#endif // MANWINDOW_H
