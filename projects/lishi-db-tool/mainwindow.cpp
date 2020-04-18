#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "dbbackupwindow.h"
#include "dbexportwindow.h"
#include "manwindow.h"

#include <QFileDialog>
#include <QListView>
#include <QListWidgetItem>
#include <QScreen>

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QStringList>
#include <QUrl>
#include <QDesktopWidget>

#include <tuple>
#include <exception>
#include <cstdint>

#include <ccxx/cxapplication.h>
#include <ccxx/cxdatabase.h>
#include <ccxx/cxinterinfo.h>
#include <ccxx/cxqtutil.h>

#include "sqlite3template.hpp"
#include "config.h"

class Vehicle {
public:
    int VehID; std::string ModelName, ModelPy;
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


//    Vehicle(int aVehID, string aModelName, string aModelPy,
//            string aBeginDT, string aEndDT,
//            double aWheelbase, double aTrackDia,
//            double aFTreadWidth, double aRTreadWidth,
//            double aFToeMin, double aFToe, double aFToeMax,
//            double aFCamberMin, double aFCamber, double aFCamberMax,
//            double aKpiCasterMin, double aKpiCaster, double aKpiCasterMax,
//            double aKpiCamberMin, double aKpiCamber, double aKpiCamberMax,
//            double aRToeMin, double aRToe, double aRToeMax,
//            double aRCamberMin, double aRCamber, double aRCamberMax,
//            double aRThrustMin, double aRThrust, double aRThrustMax)
//    {
//
//    }

};

using namespace std;

vector<Vehicle> f_vehicles;

int fn_helloDb1()
{
    const string CREATE_T1 = "CREATE TABLE \"t1\" (\n"
                             "  \"f1\" integer,\n"
                             "  \"f2\" real,\n"
                             "  \"f3\" text,\n"
                             "  \"f4\" blob,\n"
                             "  \"f5\" integer\n"
                             ");";

    string sCount;
    sCount = Config::mainDb()->queryValue("select count(*) from sqlite_master where type='table' and name='t1';");
    if (CxString::toInt32(sCount) <= 0)
    {
        cxPromptCheck(Config::mainDb()->execSql(CREATE_T1), return false);
    }

    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());

    auto a = db.bindnquery<int, double, string, string, int>("SELECT f1, f2, f3, f4, f4 from t1  ;");
//    a.push_back(db.bindnquery<double, std::string>("Select 3.33333333, 3.3;")[0]);
    std::cout << "erg :" << std::endl;
    for (auto x:a)
    {
        int i = std::get<0>(x);
        double d = std::get<1>(x);
        string s = std::get<2>(x);
        std::cout << i << " " << d << " " << s << " " << std::get<4>(x) << " " << std::endl;
    }

//    std::cout << std::endl <<  "query mit binds: " << std::endl;
//    for (auto row: db.bindnquery<int, double>("SELECT a,c from a where b like ?1;", {"%fira"}))
//    {
//        std::cout << std::get<0>(row) << " " << std::get<1>(row) << " " << std::endl;
//    }
//
//    std::cout << std::endl << "now updating :" << std::endl;
//
//    db.query_nothing("UPDATE a set c ='0.6' where a like ?1;", {"6"});

    {
        string sSql = "INSERT INTO t1(f1, f2, f3, f4, f5) VALUES (?, ?, ?, ?, ?);";
        sqlite3 *db = (sqlite3 *) Config::mainDb()->getDb();

        int iTotalChange = sqlite3_total_changes(db);
        int iChange = sqlite3_changes(db);
        cout << iChange << endl;
        cout << iTotalChange << endl;

        sqlite3_stmt* stmt;
        const char* tail;
        int rc = sqlite3_prepare(db, sSql.c_str(), sSql.size(), &stmt, &tail);
        if (rc != SQLITE_OK)
        {
            return -1;
        }
        for (int i = 0; i < 10; ++i)
        {
            rc = sqlite3_reset(stmt);
            if (rc != SQLITE_OK)
            {
                continue;
            }
            sqlite3_bind_int(stmt, 1, i * i);
            sqlite3_bind_double(stmt, 2, i * i * 123.456);
            char buffer [50];
            sprintf (buffer, "i = %d, i * i is %d", i, i * i);
            sqlite3_bind_text(stmt, 3, buffer, strlen(buffer), 0);
            sqlite3_bind_blob(stmt, 4, buffer, 50, 0);
            sqlite3_bind_int64(stmt, 1, (sqlite3_int64)i * i + i);
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_OK && rc != SQLITE_DONE)
            {
                return i;
            }
        }
        sqlite3_finalize(stmt);

        iChange = sqlite3_changes(db);
        iTotalChange = sqlite3_total_changes(db);
        cout << iChange << endl;
        cout << iTotalChange << endl;
    }

    {
        string sSql = "INSERT INTO t1(f1, f2, f3, f4, f5) VALUES (?, ?, ?, ?, ?);";
        vector<tuple<int, double, string, vector<char>, int>> rows;
        for (int i = 0; i < 10; ++i)
        {
            char buffer [50];
            sprintf (buffer, "i = %d, i * i is %d", i, i * i);
            vector<char> image{static_cast<char>(1*i), static_cast<char>(2*i), static_cast<char>(3*i), static_cast<char>(4*i), static_cast<char>(5*i)};
            rows.push_back(std::tuple<int, double, string, vector<char>, int> (i, i * i * 123.456, string(buffer), image, i * i * i));
        }
        int r = db.bindnexec<int, double, string, vector<char>, int>(sSql, rows);
        std::cout << "bindnexec :" << r << std::endl;
    }

    return 0;
}

int fn_createVehimage()
{
    const string CREATE_T1 = "CREATE TABLE \"Vehimage\" (\n"
                             "  \"vid\" integer,\n"
                             "  \"f\" text,\n"
                             "  \"s\" text,\n"
                             "  \"b\" text,\n"
                             "  PRIMARY KEY (\"vid\")\n"
                             ");";

    string sCount;
    sCount = Config::mainDb()->queryValue("select count(*) from sqlite_master where type='table' and name='Vehimage';");
    if (CxString::toInt32(sCount) <= 0)
    {
        cxPromptCheck(Config::mainDb()->execSql(CREATE_T1), return false);
    }

    return 0;
}

int fn_helloDb2()
{
    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());
    {
        string sSql = "SELECT ManID, ManName, ManLogo FROM Man;";
        sqlite3 *db = (sqlite3 *) Config::mainDb()->getDb();
        int rc, ncols;
        sqlite3_stmt *stmt;
        const char *tail;
        rc = sqlite3_prepare(db, sSql.c_str(), sSql.size(), &stmt, &tail);
        if (rc != SQLITE_OK)
        {
            return -1;
        }
        rc = sqlite3_step(stmt);
        ncols = sqlite3_column_count(stmt);
        vector<vector<string>> rows;
        while (rc == SQLITE_ROW)
        {
            vector<string> row;
            for (int i = 0; i < ncols; ++i)
            {
                string sValue;
                switch (sqlite3_column_type(stmt, i))
                {
                    case SQLITE_INTEGER:
                    {
                        const unsigned char *pch = sqlite3_column_text(stmt, i);
                        if (pch)
                            sValue = string((const char *) pch);
                    }
                        break;
                    case SQLITE_FLOAT:
                    {
                        const unsigned char *pch = sqlite3_column_text(stmt, i);
                        if (pch)
                            sValue = string((const char *) pch);
                    }
                        break;
                    case SQLITE_BLOB:
                    {
                        int len = sqlite3_column_bytes(stmt, i);
                        const void *pch = sqlite3_column_blob(stmt, i);
                        if (pch)
                            sValue = string((const char *) pch, len);
                    }
                        break;
                    case SQLITE3_TEXT:
                    {
                        const unsigned char *pch = sqlite3_column_text(stmt, i);
                        if (pch)
                            sValue = string((const char *) pch);
                    }
                        break;
                    default:
                    {
                        const unsigned char *pch = sqlite3_column_text(stmt, i);
                        if (pch)
                            sValue = string((const char *) pch);
                    }
                        break;
                }
                row.push_back(sValue);
            }
            rows.push_back(row);
            rc = sqlite3_step(stmt);
        }
        sqlite3_finalize(stmt);

        for (int i = 0; i < rows.size(); ++i)
        {
            vector<string> &row = rows[i];
            string sManName = row[1];
            string sManLogo = row[2];
//            CxFile::save(CxFileSystem::mergeFilePath(CxAppEnv::tempPath(), sManName + ".png"), sManLogo);
        }
    }
    return 0;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initData();

    initUi();

    initMenu();

    refreshDcMan("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dcBn2ClickedSlot()
{

}

void MainWindow::dcBn1ClickedSlot()
{

}

void MainWindow::dlBn1ClickedSlot()
{

}

void MainWindow::on_dcLw1_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    string sMan = CxQString::gbkToStdString(current->text());
    ui->dcEd21->setText("");
    refreshDcVeh(sMan, "");
}


void MainWindow::on_dcLw2_currentRowChanged(int currentRow)
{
    viewDcVeh(currentRow);
}

void MainWindow::outInfo(const QString &s)
{
    ui->statusbar->showMessage(s);
}

void MainWindow::outInfo(const std::string &s)
{
    outInfo(CxQString::gbkToQString(s));
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->dcImage1)
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            selectImage(1);
        }
    }
    else if (watched == ui->dcImage2)
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            selectImage(2);
        }
    }
    else if (watched == ui->dcImage3)
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            selectImage(3);
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::initData()
{
//    fn_helloDb1();

//    fn_helloDb2();

    fn_createVehimage();
}

void MainWindow::initUi()
{

    QWebEngineView *webView = new QWebEngineView(ui->pnLeft);
    QWebEnginePage *webPage = new QWebEnginePage(QWebEngineProfile::defaultProfile(), webView);
    webView->setPage(webPage);
    webView->setUrl(Config::defaultUrl());
    ui->pnLeft->layout()->addWidget(webView);

    connect(ui->dcBn1, SIGNAL(clicked()), this, SLOT(dcBn1ClickedSlot()));
//    connect(ui->dcLw1, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(dcLw1currentItemChanged()));

    QSize size = qApp->screens()[0]->size();
    ui->dcImage1->setMaximumSize(size.width() * 0.33, size.height() * 0.33);
    ui->dcImage2->setMaximumSize(size.width() * 0.33, size.height() * 0.33);
    ui->dcImage3->setMaximumSize(size.width() * 0.33, size.height() * 0.33);
    setQss("Aqua.qss");
}

void MainWindow::initMenu()
{
//    openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open"), this);
//    openAction->setShortcuts(QKeySequence::Open);
//    openAction->setStatusTip(tr("Open an existing file"));
//    connect(openAction, &QAction::triggered, this, &MainWindow::open);
//
//    QMenu *file = menuBar()->addMenu(tr("&File"));
//    file->addAction(openAction);

    ui->dcImage1->installEventFilter(this);
    ui->dcImage2->installEventFilter(this);
    ui->dcImage3->installEventFilter(this);
}

void MainWindow::setQss(const std::string& fn)
{
    QFile file(CxQString::gbkToQString(CxFileSystem::mergeFilePath(CxAppEnv::configPath(), fn)));
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);
}

/**
 * @param sFilter
 */
void MainWindow::refreshDcMan(const std::string &sFilter)
{
    string sql = "SELECT ManID, ManName, ManPy, ManLogo FROM Man;";
    string fl = CxString::trim(sFilter);
    if (fl.size() > 0)
    {
        string flUp = CxString::toUpper(fl);
        sql = CxString::format("SELECT ManID, ManName, ManPy, ManLogo FROM Man WHERE ManName LIKE '\\%%s\\%' OR AND UPPER(ManName) like '\\%%s\\%' OR ManPy LIKE '\\%%s\\%' OR AND UPPER(ManPy) like '\\%%s\\%'", fl.c_str(), flUp.c_str(), fl.c_str(), flUp.c_str());
    }

    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());
    auto a = db.bindnquery<int, string, string, vector<char>>(sql);
    ui->dcLw1->clear();
    for (auto x:a)
    {
        int iManID = std::get<0>(x);
        string sManName = std::get<1>(x);
        string sManPy = std::get<2>(x);
        vector<char> sManLogo = std::get<3>(x);
//        CxFile::save(CxFileSystem::mergeFilePath(CxAppEnv::tempPath(), sManName + ".png"), string(sManLogo.data(), sManLogo.size()));
        std::cout << iManID << " " << sManName << " " << std::endl;
        QPixmap pm;
        pm.loadFromData((const uchar *) sManLogo.data(), (uint) sManLogo.size(), "JFIF");
        QListWidgetItem *item = new QListWidgetItem(QIcon(pm), CxQString::gbkToQString(sManName));
        ui->dcLw1->addItem(item);
    }
//    if (ui->dcLw1->count() > 0)
//    {
//        ui->dcLw1->setCurrentRow(0);
//    }
}

/**
 * @param sFilter
 */
void MainWindow::refreshDcVeh(const std::string& sMan, const std::string &sFilter)
{
    string fields = " VehID, ModelName, ModelPy,"
                    " BeginDT, EndDT,"
                    " Wheelbase, TrackDia,"
                    " FTreadWidth, RTreadWidth,"
                    " FToeMin, FToe, FToeMax,"
                    " FCamberMin, FCamber, FCamberMax,"
                    " KpiCasterMin, KpiCaster, KpiCasterMax,"
                    " KpiCamberMin, KpiCamber, KpiCamberMax,"
                    " RToeMin, RToe, RToeMax,"
                    " RCamberMin, RCamber, RCamberMax,"
                    " RThrustMin, RThrust, RThrustMax";
    string sql = CxString::format("SELECT %s FROM Vehicle WHERE ManName='%s' ;", fields.c_str(), sMan.c_str());
    string fl = CxString::trim(sFilter);
    if (fl.size() > 0)
    {
        string flUp = CxString::toUpper(fl);
//        sql = CxString::format("SELECT %s FROM Vehicle WHERE ModelName LIKE '\\%%s\\%' OR AND UPPER(ModelName) like '\\%%s\\%' OR ModelPy LIKE '\\%%s\\%' OR AND UPPER(ModelPy) like '\\%%s\\%'", fields.c_str(), fl.c_str(), flUp.c_str(), fl.c_str(), flUp.c_str());
        sql = CxString::format("SELECT %s FROM Vehicle WHERE ManName='%s' AND ( ModelName LIKE '\\%%s\\%' OR ModelPy LIKE '\\%%s\\%' )", fields.c_str(), sMan.c_str(), fl.c_str(), fl.c_str());
    }
    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());
    auto a = db.bindnquery<int, string, string, string, string
        , double, double, double, double
        , double, double, double
        , double, double, double
        , double, double, double
        , double, double, double
        , double, double, double
        , double, double, double
        , double, double, double>(sql);
    f_vehicles.clear();
    ui->dcLw2->clear();
    for (auto x:a)
    {
        int VehID = std::get<0>(x);
        string ModelName = std::get<1>(x);
        string ModelPy = std::get<2>(x);
        string BeginDT = std::get<3>(x);
        string EndDT = std::get<4>(x);

        double Wheelbase = std::get<5>(x); double TrackDia = std::get<6>(x);
        double FTreadWidth = std::get<7>(x); double RTreadWidth = std::get<8>(x);

        double FToeMin = std::get<9>(x); double FToe = std::get<10>(x); double FToeMax = std::get<11>(x);
        double FCamberMin = std::get<12>(x); double FCamber = std::get<13>(x); double FCamberMax = std::get<14>(x);
        double KpiCasterMin = std::get<15>(x); double  KpiCaster = std::get<16>(x); double KpiCasterMax = std::get<17>(x);
        double KpiCamberMin = std::get<18>(x); double KpiCamber = std::get<19>(x); double KpiCamberMax = std::get<20>(x);

        double RToeMin = std::get<21>(x); double RToe = std::get<22>(x); double RToeMax = std::get<23>(x);
        double RCamberMin = std::get<24>(x); double RCamber = std::get<25>(x); double RCamberMax = std::get<26>(x);
        double RThrustMin = std::get<27>(x); double  RThrust = std::get<28>(x); double RThrustMax = std::get<29>(x);

        Vehicle vehicle{
             VehID, ModelName, ModelPy,
             BeginDT, EndDT,
             Wheelbase, TrackDia,
             FTreadWidth, RTreadWidth,
             FToeMin, FToe, FToeMax,
             FCamberMin, FCamber, FCamberMax,
             KpiCasterMin, KpiCaster, KpiCasterMax,
             KpiCamberMin, KpiCamber, KpiCamberMax,
             RToeMin, RToe, RToeMax,
             RCamberMin, RCamber, RCamberMax,
             RThrustMin, RThrust, RThrustMax
        };
        f_vehicles.push_back(vehicle);
        QListWidgetItem * oItem = new QListWidgetItem();
        oItem->setData(Qt::UserRole, int(f_vehicles.size()));
        oItem->setText(CxQString::gbkToQString(ModelName));
        ui->dcLw2->addItem(oItem);
    }
//    if (ui->dcLw2->count() > 0)
//    {
//        ui->dcLw2->setCurrentRow(0);
//    }
}

void MainWindow::viewDcVeh(int index)
{
    if (index < 0 || index > f_vehicles.size())
    {
        return;
    }
    Vehicle &veh = f_vehicles[index];
    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());
    auto a = db.bindnquery<string, string, string>(CxString::format("SELECT f, s, b FROM Vehimage WHERE vid=%d", veh.VehID));
    if (a.size()>0)
    {
        auto &x = a[0];
        loadImage(1, std::get<0>(x));
        loadImage(2, std::get<0>(x));
        loadImage(3, std::get<0>(x));
    }
    //    int VehID; std::string ModelName, ModelPy;
    //    std::string BeginDT, EndDT;
    //    double Wheelbase, TrackDia;
    //    double FTreadWidth, RTreadWidth;
    ui->dcEd31->setText(CxQString::gbkToQString(veh.ModelName));

    ui->dcEd32->setText(CxQString::gbkToQString(veh.BeginDT));
    ui->dcEd33->setText(CxQString::gbkToQString(veh.EndDT));

    ui->dcEd34->setText(QString::number(veh.Wheelbase, 'g', 3));
    ui->dcEd35->setText(QString::number(veh.TrackDia, 'g', 3));

    ui->dcEd36->setText(QString::number(veh.FTreadWidth, 'g', 3));
    ui->dcEd37->setText(QString::number(veh.RTreadWidth, 'g', 3));
    //
    //    double FToeMin, FToe, FToeMax;
    //    double FCamberMin, FCamber, FCamberMax;
    //    double KpiCasterMin, KpiCaster, KpiCasterMax;
    //    double KpiCamberMin, KpiCamber, KpiCamberMax;
    ui->dcEd41->setText(QString::number(veh.FToeMin, 'g', 3));
    ui->dcEd42->setText(QString::number(veh.FToe, 'g', 3));
    ui->dcEd43->setText(QString::number(veh.FToeMax, 'g', 3));

    ui->dcEd44->setText(QString::number(veh.FCamberMin, 'g', 3));
    ui->dcEd45->setText(QString::number(veh.FCamber, 'g', 3));
    ui->dcEd46->setText(QString::number(veh.FCamberMax, 'g', 3));

    ui->dcEd47->setText(QString::number(veh.KpiCasterMin, 'g', 3));
    ui->dcEd48->setText(QString::number(veh.KpiCaster, 'g', 3));
    ui->dcEd49->setText(QString::number(veh.KpiCasterMax, 'g', 3));

    ui->dcEd4a->setText(QString::number(veh.KpiCamberMin, 'g', 3));
    ui->dcEd4b->setText(QString::number(veh.KpiCamber, 'g', 3));
    ui->dcEd4c->setText(QString::number(veh.KpiCamberMax, 'g', 3));
    //
    //    double RToeMin, RToe, RToeMax;
    //    double RCamberMin, RCamber, RCamberMax;
    //    double RThrustMin, RThrust, RThrustMax;
    ui->dcEd51->setText(QString::number(veh.KpiCamberMax, 'g', 3));
    ui->dcEd52->setText(QString::number(veh.KpiCamberMax, 'g', 3));
    ui->dcEd53->setText(QString::number(veh.KpiCamberMax, 'g', 3));

    ui->dcEd54->setText(QString::number(veh.KpiCamberMax, 'g', 3));
    ui->dcEd55->setText(QString::number(veh.KpiCamberMax, 'g', 3));
    ui->dcEd56->setText(QString::number(veh.KpiCamberMax, 'g', 3));

    ui->dcEd57->setText(QString::number(veh.KpiCamberMax, 'g', 3));
    ui->dcEd58->setText(QString::number(veh.KpiCamberMax, 'g', 3));
    ui->dcEd59->setText(QString::number(veh.KpiCamberMax, 'g', 3));
}

void MainWindow::loadImage(int i, std::string &fn)
{
    QString fp = CxQString::gbkToQString(Config::imageFilePath(fn));
    QLabel *lb = ui->dcImage1;
    QLineEdit *ed = ui->dcImageEd1;
    switch (i)
    {
        case 2:
            lb = ui->dcImage2;
            ed = ui->dcImageEd2;
            break;
        case 3:
            lb = ui->dcImage2;
            ed = ui->dcImageEd2;
            break;
        default:;
    }
    QImage image(fp);
    ed->setText(fp);
    lb->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::selectImage(int i)
{
    QLabel *lb = ui->dcImage1;
    QLineEdit *ed = ui->dcImageEd1;
    switch (i)
    {
        case 2:
            lb = ui->dcImage2;
            ed = ui->dcImageEd2;
            break;
        case 3:
            lb = ui->dcImage2;
            ed = ui->dcImageEd2;
            break;
        default:;
    }
    QString selfilter = tr("JPEG (*.jpg *.jpeg)");
    QString fp = QFileDialog::getOpenFileName(this, tr("选择的图像文件"),
                                              "",
                                              tr("JPEG (*.jpg *.jpeg);;TIFF (*.tif)" )
//                                              CxQString::gbkToQString(Config::imagePath()),
//                                              tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)" )
                                              );
    string fp2 = CxQString::gbkToStdString(fp);
    if (CxFileSystem::isExist(fp2))
    {
        string dst = CxFileSystem::mergeFilePath(Config::imagePath(), CxTime::currentSystemTimeString('-', 't')) + CxFileSystem::extractFileSuffixName(fp2);
        string src = fp2;
        if (CxFileSystem::copyFile(src, dst) <= 0)
        {
            CxQDialog::ShowPrompt("拷贝图像文件失败，请检查空间与权限！");
            return;
        }

        QPixmap p;
        p.load(CxQString::gbkToQString(dst));
        p.scaled(lb->size(), Qt::KeepAspectRatio);
        lb->setScaledContents(true);
        lb->setPixmap(p);
        ed->setText(CxQString::gbkToQString(dst));
//        lb->setPixmap(QPixmap::fromImage( QImage(CxQString::gbkToQString(dst)) ));
    }
}

void MainWindow::on_dcEd11_textChanged(const QString &arg1)
{
    string sFilter = CxQString::gbkToStdString(ui->dcEd11->text());
    refreshDcMan(sFilter);
}

void MainWindow::on_dcEd21_textChanged(const QString &arg1)
{
    if (! ui->dcLw1->currentItem())
    {
        return;
    }
    string sMan = CxQString::gbkToStdString(ui->dcLw1->currentItem()->text());
    string sFilter = CxString::trim(CxQString::gbkToStdString(ui->dcEd12->text()));
    refreshDcVeh(sMan, sFilter);
}

// add Man
void MainWindow::on_dcBn1_clicked()
{
    string sSql = "INSERT INTO \"Man\"(\"ManID\", \"ManName\", \"ManPy\", \"LanID\", \"IsNative\", \"ManLogo\", \"Mem\", \"VIN\", \"recversion\") VALUES (10, 'BMW', 'BMW', 1033, 0, X'', NULL, '', NULL);";
}

// add Veh
void MainWindow::on_dcBn61_clicked()
{

}

// del Veh
void MainWindow::on_dcBn62_clicked()
{

}

// save Veh
void MainWindow::on_dcBn63_clicked()
{

}

void MainWindow::on_muDbExport_clicked()
{
    DbExportWindow dialog;

//    dialog.setWindowTitle( sTitle );
//    dialog.resize( 380, 220 );
    dialog.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            dialog.size(),
            qApp->desktop()->availableGeometry()
        )
    );
    if ( dialog.exec() == QDialog::Accepted )
    {

    }
    else
    {

    }
}

void MainWindow::on_muDbBackup_clicked()
{

}
