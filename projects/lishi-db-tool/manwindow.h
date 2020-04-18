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

    int ManID;
    std::string ManName;
    std::string ManPy;
    int LanID;
    int IsNative;
    std::vector<char> ManLogo;

    QImage ManLogoImage;
    int sqlResult;

private slots:
    void on_maBn1_clicked();

    void on_maBn2_clicked();

private:
    Ui::ManWindow *ui;

};

#endif // MANWINDOW_H
