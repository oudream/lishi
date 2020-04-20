#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>

class Man {
public:
    int ManID;
    std::string ManName;
    std::string ManPy;
    int LanID;
    int IsNative;
    std::vector<char> ManLogo;

    Man &init()
    {
        ManID = -1;
        ManName = std::string();
        ManPy = std::string();
        LanID = -1;
        IsNative = 0;
        ManLogo.clear();
    }

};

class Vehicle {
public:
    int ManID;
    std::string ManName, ManPy;
    int VehID;
    std::string ModelName, ModelPy;
    std::string BeginDT, EndDT;
    double Wheelbase, TrackDia;
    double FTreadWidth, RTreadWidth;

    double FToeMin, FToe, FToeMax;
    double FCamberMin, FCamber, FCamberMax;
    double KpiCasterMin, KpiCaster, KpiCasterMax;
    double KpiCamberMin, KpiCamber, KpiCamberMax;

    double RToeMin, RToe, RToeMax;
    double RCamberMin, RCamber, RCamberMax;
    double RThrustMin, RThrust, RThrustMax;

    Vehicle &init()
    {
        ManID = -1;
        ManName = "";
        ManPy = "";
        VehID = -1;
        ModelName = "";
        ModelPy = "";
        BeginDT = "";
        EndDT = "";
        Wheelbase = 0;
        TrackDia = 0;
        FTreadWidth = 0;
        RTreadWidth = 0;

        FToeMin = 0;
        FToe = 0;
        FToeMax = 0;
        FCamberMin = 0;
        FCamber = 0;
        FCamberMax = 0;
        KpiCasterMin = 0;
        KpiCaster = 0;
        KpiCasterMax = 0;
        KpiCamberMin = 0;
        KpiCamber = 0;
        KpiCamberMax = 0;

        RToeMin = 0;
        RToe = 0;
        RToeMax = 0;
        RCamberMin = 0;
        RCamber = 0;
        RCamberMax = 0;
        RThrustMin = 0;
        RThrust = 0;
        RThrustMax = 0;

        return *this;
    }

    bool isValid()
    {
        return ModelName.size() > 0 && ModelPy.size() > 0;
    }
};

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void outInfo(const QString &s);

    void outInfo(const std::string &s);

    bool eventFilter(QObject *watched, QEvent *event);

private slots:
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

    int initMan();

    void initUi();

    void initMenu();

    void initContent();

    void refreshDcMan(const std::string &sFilter);

    int initVeh(const std::string &sMan);

    void refreshDcVeh(const std::string &sFilter);

    int insertVeh(int VehID, const Vehicle &veh);

    int updateVeh(int VehID, const Vehicle &veh);

    int insertUpdateVehImage(int VehID);

    void viewOutDcVeh(int index);

    void viewOutDcVeh(const Vehicle &veh);

    Vehicle viewInDcVeh();

    void loadImage(int i, std::string &fn);

    void selectImage(int i);

private:
    Ui::MainWindow *ui;
    std::string _qssFilePath;

};

#endif // MAINWINDOW_H
