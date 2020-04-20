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

using namespace std;

vector<Man> f_mans;
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

        sqlite3_stmt *stmt;
        const char *tail;
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
            char buffer[50];
            sprintf(buffer, "i = %d, i * i is %d", i, i * i);
            sqlite3_bind_text(stmt, 3, buffer, strlen(buffer), 0);
            sqlite3_bind_blob(stmt, 4, buffer, 50, 0);
            sqlite3_bind_int64(stmt, 1, (sqlite3_int64) i * i + i);
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
            char buffer[50];
            sprintf(buffer, "i = %d, i * i is %d", i, i * i);
            vector<char> image{static_cast<char>(1 * i), static_cast<char>(2 * i), static_cast<char>(3 * i),
                               static_cast<char>(4 * i), static_cast<char>(5 * i)};
            rows.push_back(std::tuple<int, double, string, vector<char>, int>(i,
                                                                              i * i * 123.456, string(buffer), image,
                                                                              i * i * i));
        }
        int r = db.bindnexec<int, double, string, vector<char>, int>(sSql, rows);
        std::cout << "bindnexec :" << r << std::endl;
    }

    return 0;
}

int fn_createVehimage()
{
    const string CREATE_T1 = "CREATE TABLE \"Vehimage\" (\n"
                             "  \"VehID\" integer,\n"
                             "  \"f\" text,\n"
                             "  \"s\" text,\n"
                             "  \"b\" text,\n"
                             "  PRIMARY KEY (\"VehID\")\n"
                             ");";

    string sCount;
    sCount = Config::mainDb()->queryValue("select count(*) from sqlite_master where type='table' and name='Vehimage';");
    if (CxString::toInt32(sCount) <= 0)
    {
        cxPromptCheck(Config::mainDb()->execSql(CREATE_T1), return false);
    }

    return 0;
}

int fn_cleanupDb()
{
    {
        //select * from Vehicle
        //where VehID in (select  VehID  from  Vehicle  group  by  VehID  having  count(VehID) > 1)
        string sCount;
        sCount = Config::mainDb()->queryValue("select count(VehID) from Vehicle where VehID in (select  VehID  from  Vehicle  group  by  VehID  having  count(VehID) > 1);");
        if (CxString::toInt32(sCount) > 0)
        {
            int result = Config::mainDb()->execSql("DELETE FROM Vehicle WHERE VehID in (select VehID from Vehicle group by VehID having count(VehID) > 1);");
            cxPrompt() << "DELETE REPEAT Vehicle : " << result;
        }
    }

    {
        // select * from Vehicle where VehID is null or VehID <= 0;
        string sCount;
        sCount = Config::mainDb()->queryValue("select count(VehID) from Vehicle where VehID is null or VehID = 0;");
        if (CxString::toInt32(sCount) > 0)
        {
            int result = Config::mainDb()->execSql("DELETE FROM Vehicle WHERE VehID is null or VehID = 0;");
            cxPrompt() << "DELETE INVALID Vehicle : " << result;
        }
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

    initContent();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    _qssFilePath = CxFileSystem::mergeFilePath(CxAppEnv::resPath(), CxAppEnv::findConfig(string("system"), string("qss"), string()));
    cxPrompt() << "_qssFilePath: " << _qssFilePath;

//    fn_helloDb1();

//    fn_helloDb2();

    fn_cleanupDb();

    fn_createVehimage();

    initMan();
}

/**
 * @param sFilter
 */
int MainWindow::initMan()
{
    string sql = "SELECT ManID, ManName, ManPy, ManLogo FROM Man;";
//    string fl = CxString::trim(sFilter);
//    if (fl.size() > 0)
//    {
//        string flUp = CxString::toUpper(fl);
//        sql = CxString::format("SELECT ManID, ManName, ManPy, ManLogo FROM Man WHERE ManName LIKE '\\%%s\\%' OR AND UPPER(ManName) like '\\%%s\\%' OR ManPy LIKE '\\%%s\\%' OR AND UPPER(ManPy) like '\\%%s\\%'", fl.c_str(), flUp.c_str(), fl.c_str(), flUp.c_str());
//    }
    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());
    auto a = db.bindnquery<int, string, string, vector<char>>(sql);
    f_mans.clear();
    for (auto x:a)
    {
        Man man;
        man.ManID = std::get<0>(x);
        man.ManName = std::get<1>(x);
        man.ManPy = std::get<2>(x);
        man.ManLogo = std::get<3>(x);
        f_mans.push_back(man);
    }
    return f_mans.size();
}

void MainWindow::initUi()
{
    QWebEngineView *webView = new QWebEngineView(ui->pnLeft);
    QWebEnginePage *webPage = new QWebEnginePage(QWebEngineProfile::defaultProfile(), webView);
    webView->setPage(webPage);
    webView->setUrl(Config::defaultUrl());
    ui->pnLeft->layout()->addWidget(webView);

//    connect(ui->dcBn1, SIGNAL(clicked()), this, SLOT(dcBn1ClickedSlot()));
//    connect(ui->dcLw1, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(dcLw1currentItemChanged()));

    QSize size = qApp->screens()[0]->size();
    ui->dcImage1->setMaximumSize(size.width() * 0.33, size.height() * 0.33);
    ui->dcImage2->setMaximumSize(size.width() * 0.33, size.height() * 0.33);
    ui->dcImage3->setMaximumSize(size.width() * 0.33, size.height() * 0.33);
    ui->dcImageEd1->setVisible(false);
    ui->dcImageEd2->setVisible(false);
    ui->dcImageEd3->setVisible(false);

    CxQWidget::setQSS(this, _qssFilePath);
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

void MainWindow::initContent()
{
    refreshDcMan("");
}

void MainWindow::on_dcLw1_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current)
    {
        string sMan = CxQString::gbkToStdString(current->text());
        initVeh(sMan);
        refreshDcVeh("");
        ui->dcEd21->setText("");
    }
}

void MainWindow::on_dcLw2_currentRowChanged(int currentRow)
{
    if (f_vehicles.size() <= 0 || currentRow < 0 || currentRow >= f_vehicles.size())
    {
        return;
    }

    Vehicle &veh = f_vehicles[currentRow];
    viewOutDcVeh(veh);
    ui->dcBn61->setEnabled(true);
}

void MainWindow::on_dcEd11_textChanged(const QString &arg1)
{
    refreshDcMan(CxQString::gbkToStdString(arg1));
}

void MainWindow::on_dcEd21_textChanged(const QString &arg1)
{
    string sFilter = CxString::trim(CxQString::gbkToStdString(arg1));
    refreshDcVeh(sFilter);
}

void MainWindow::refreshDcMan(const string &sFilter)
{
    ui->dcLw1->clear();
    string sub = sFilter;
    for (int i = 0; i < f_mans.size(); ++i)
    {
        Man &man = f_mans[i];
        if (sub.size()>0)
        {
            if ( ! CxString::containCase(man.ManName, sub) && ! CxString::containCase(man.ManPy, sub))
            {
                continue;
            }
        }
        QPixmap pm;
        pm.loadFromData((const uchar *) man.ManLogo.data(), (uint) man.ManLogo.size(), "JFIF");
        QListWidgetItem *item = new QListWidgetItem(QIcon(pm), CxQString::gbkToQString(man.ManName));
        ui->dcLw1->addItem(item);
    }
}

/**
 * @param sFilter
 */
int MainWindow::initVeh(const std::string &sMan)
{
    string fields = " ManID, ManName, ManPy,"
                    " VehID, ModelName, ModelPy,"
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
    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());
    auto a = db.bindnquery<int, string, string, int, string, string, string, string, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>(sql);
    f_vehicles.clear();
    for (auto x:a)
    {
        int ManID = std::get<0>(x);
        string ManName = std::get<1>(x);
        string ManPy = std::get<2>(x);
        int VehID = std::get<3>(x);
        string ModelName = std::get<4>(x);
        string ModelPy = std::get<5>(x);
        string BeginDT = std::get<6>(x);
        string EndDT = std::get<7>(x);
        double Wheelbase = std::get<8>(x);
        double TrackDia = std::get<9>(x);
        double FTreadWidth = std::get<10>(x);
        double RTreadWidth = std::get<11>(x);
        double FToeMin = std::get<12>(x);
        double FToe = std::get<13>(x);
        double FToeMax = std::get<14>(x);
        double FCamberMin = std::get<15>(x);
        double FCamber = std::get<16>(x);
        double FCamberMax = std::get<17>(x);
        double KpiCasterMin = std::get<18>(x);
        double KpiCaster = std::get<19>(x);
        double KpiCasterMax = std::get<20>(x);
        double KpiCamberMin = std::get<21>(x);
        double KpiCamber = std::get<22>(x);
        double KpiCamberMax = std::get<23>(x);
        double RToeMin = std::get<24>(x);
        double RToe = std::get<25>(x);
        double RToeMax = std::get<26>(x);
        double RCamberMin = std::get<27>(x);
        double RCamber = std::get<28>(x);
        double RCamberMax = std::get<29>(x);
        double RThrustMin = std::get<30>(x);
        double RThrust = std::get<31>(x);
        double RThrustMax = std::get<32>(x);

        Vehicle vehicle{
            ManID, ManName, ManPy,
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
    }
    return f_vehicles.size();
}

/**
 * @param sFilter
 */
void MainWindow::refreshDcVeh(const std::string &sFilter)
{
    ui->dcLw2->clear();
    string sub = sFilter;
    for (int i = 0; i < f_vehicles.size(); ++i)
    {
        Vehicle &veh = f_vehicles[i];
        if (sub.size()>0)
        {
            if ( ! CxString::containCase(veh.ModelName, sub) && ! CxString::containCase(veh.ModelPy, sub))
            {
                continue;
            }
        }
        QListWidgetItem *oItem = new QListWidgetItem();
        oItem->setData(Qt::UserRole, int(f_vehicles.size()));
        oItem->setText(CxQString::gbkToQString(veh.ModelName));
        ui->dcLw2->addItem(oItem);
    }
}

/**
  INSERT INTO Vehicle(
        ManID, ManName, ManPy,
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
        ) VALUES (
        ?, ?, ?,
        ?, ?, ?,
        ?, ?,
        ?, ?,
        ?, ?,
        ?, ?, ?,
        ?, ?, ?,
        ?, ?, ?,
        ?, ?, ?,
        ?, ?, ?,
        ?, ?, ?,
        ?, ?, ?
            );
 * @param veh
 * @return
 */
int MainWindow::insertVeh(int VehID, const Vehicle &veh)
{
    string sSql = "INSERT INTO Vehicle(\n"
                  "        ManID, ManName, ManPy,\n"
                  "        VehID, ModelName, ModelPy,\n"
                  "        BeginDT, EndDT,\n"
                  "        Wheelbase, TrackDia,\n"
                  "        FTreadWidth, RTreadWidth,\n"
                  "        FToeMin, FToe, FToeMax,\n"
                  "        FCamberMin, FCamber, FCamberMax,\n"
                  "        KpiCasterMin, KpiCaster, KpiCasterMax,\n"
                  "        KpiCamberMin, KpiCamber, KpiCamberMax,\n"
                  "        RToeMin, RToe, RToeMax,\n"
                  "        RCamberMin, RCamber, RCamberMax,\n"
                  "        RThrustMin, RThrust, RThrustMax\n"
                  "        ) VALUES (\n"
                  "        ?, ?, ?,\n"
                  "        ?, ?, ?,\n"
                  "        ?, ?,\n"
                  "        ?, ?,\n"
                  "        ?, ?,\n"
                  "        ?, ?, ?,\n"
                  "        ?, ?, ?,\n"
                  "        ?, ?, ?,\n"
                  "        ?, ?, ?,\n"
                  "        ?, ?, ?,\n"
                  "        ?, ?, ?,\n"
                  "        ?, ?, ?\n"
                  "            );";
    vector<tuple<int, string, string, int, string, string, string, string, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>> rows;
    rows.push_back(tuple<int, string, string, int, string, string, string, string, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>
                       (
                           veh.ManID, veh.ManName, veh.ManPy,
                           VehID, veh.ModelName, veh.ModelPy,
                           veh.BeginDT, veh.EndDT,
                           veh.Wheelbase, veh.TrackDia,
                           veh.FTreadWidth, veh.RTreadWidth,
                           veh.FToeMin, veh.FToe, veh.FToeMax,
                           veh.FCamberMin, veh.FCamber, veh.FCamberMax,
                           veh.KpiCasterMin, veh.KpiCaster, veh.KpiCasterMax,
                           veh.KpiCamberMin, veh.KpiCamber, veh.KpiCamberMax,
                           veh.RToeMin, veh.RToe, veh.RToeMax,
                           veh.RCamberMin, veh.RCamber, veh.RCamberMax,
                           veh.RThrustMin, veh.RThrust, veh.RThrustMax
                       ));
    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());
    int r = db.bindnexec<int, string, string, int, string, string, string, string, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>(sSql, rows);
    return r;
}

int MainWindow::updateVeh(int VehID, const Vehicle &veh)
{
    string sSql = "    UPDATE Vehicle SET\n"
                  "        ManID = ?, ManName = ?, ManPy = ?,\n"
                  "        VehID = ?, ModelName = ?, ModelPy = ?,\n"
                  "        BeginDT = ?, EndDT = ?,\n"
                  "        Wheelbase = ?, TrackDia = ?,\n"
                  "        FTreadWidth = ?, RTreadWidth = ?,\n"
                  "        FToeMin = ?, FToe = ?, FToeMax = ?,\n"
                  "        FCamberMin = ?, FCamber = ?, FCamberMax = ?,\n"
                  "        KpiCasterMin = ?, KpiCaster = ?, KpiCasterMax = ?,\n"
                  "        KpiCamberMin = ?, KpiCamber = ?, KpiCamberMax = ?,\n"
                  "        RToeMin = ?, RToe = ?, RToeMax = ?,\n"
                  "        RCamberMin = ?, RCamber = ?, RCamberMax = ?,\n"
                  "        RThrustMin = ?, RThrust = ?, RThrustMax = ?\n"
                  "    WHERE VehID = %d ;";
    sSql = CxString::format(sSql.c_str(), VehID);
    vector<tuple<int, string, string, int, string, string, string, string, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>> rows;
    rows.push_back(tuple<int, string, string, int, string, string, string, string, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>
        (
            veh.ManID, veh.ManName, veh.ManPy,
            VehID, veh.ModelName, veh.ModelPy,
            veh.BeginDT, veh.EndDT,
            veh.Wheelbase, veh.TrackDia,
            veh.FTreadWidth, veh.RTreadWidth,
            veh.FToeMin, veh.FToe, veh.FToeMax,
            veh.FCamberMin, veh.FCamber, veh.FCamberMax,
            veh.KpiCasterMin, veh.KpiCaster, veh.KpiCasterMax,
            veh.KpiCamberMin, veh.KpiCamber, veh.KpiCamberMax,
            veh.RToeMin, veh.RToe, veh.RToeMax,
            veh.RCamberMin, veh.RCamber, veh.RCamberMax,
            veh.RThrustMin, veh.RThrust, veh.RThrustMax
        ));
    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());
    int r = db.bindnexec<int, string, string, int, string, string, string, string, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double>(sSql, rows);
    return r;
}

int MainWindow::insertUpdateVehImage(int VehID)
{
    string fn1 = CxQString::gbkToStdString(ui->dcImageEd1->text());
    string fn2 = CxQString::gbkToStdString(ui->dcImageEd2->text());
    string fn3 = CxQString::gbkToStdString(ui->dcImageEd3->text());

    string sCount;
    sCount = Config::mainDb()->queryValue(CxString::format("select count(VehID) from Vehimage where VehID=%d;", VehID));
    bool bAdd = CxString::toInt32(sCount) <= 0;
    string sql;
    string msg = " Vehimage, Status: ";
    if (bAdd)
    {
        sql = CxString::format("INSERT INTO \"Vehimage\"(\"VehID\", \"f\", \"s\", \"b\") VALUES (%d, '%s', '%s', '%s');", VehID, fn1.c_str(), fn2.c_str(), fn3.c_str());
        msg = "INSERT INTO " + msg;
    }
    else
    {
        sql = CxString::format("UPDATE \"Vehimage\" SET \"f\" = '%s', \"s\" = '%s', \"b\" = '%s' WHERE \"VehID\" = %d;", VehID, fn1.c_str(), fn2.c_str(), fn3.c_str());;
        msg = "UPDATE " + msg;
    }
    int r = Config::mainDb()->execSql(sql);
    msg += r > 0 ? " 成功" : " 失败";
    outInfo(msg);
    return r;
}

void MainWindow::viewOutDcVeh(int index)
{
    if (index < 0 || index > f_vehicles.size())
    {
        return;
    }

}

void MainWindow::viewOutDcVeh(const Vehicle &veh)
{
    bool bImage = false;
    if (veh.VehID >= 0)
    {
        SQL::Con db((sqlite3 *) Config::mainDb()->getDb());
        auto a = db.bindnquery<string, string, string>(CxString::format("SELECT f, s, b FROM Vehimage WHERE VehID=%d", veh.VehID));
        if (a.size() > 0)
        {
            auto &x = a[0];
            loadImage(1, std::get<0>(x));
            loadImage(2, std::get<1>(x));
            loadImage(3, std::get<2>(x));
            bImage = true;
        }
    }
    if (! bImage)
    {
        ui->dcImage1->clear();
        ui->dcImageEd1->clear();
        ui->dcImage2->clear();
        ui->dcImageEd2->clear();
        ui->dcImage2->clear();
        ui->dcImageEd2->clear();
    }
    //    int VehID; std::string ModelName, ModelPy;
    //    std::string BeginDT, EndDT;
    //    double Wheelbase, TrackDia;
    //    double FTreadWidth, RTreadWidth;
    ui->dcEd31->setText(CxQString::gbkToQString(veh.ModelName));
    ui->dcEd31_2->setText(CxQString::gbkToQString(veh.ModelPy));

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
    ui->dcEd51->setText(QString::number(veh.RToeMin, 'g', 3));
    ui->dcEd52->setText(QString::number(veh.RToe, 'g', 3));
    ui->dcEd53->setText(QString::number(veh.RToeMax, 'g', 3));

    ui->dcEd54->setText(QString::number(veh.RCamberMin, 'g', 3));
    ui->dcEd55->setText(QString::number(veh.RCamber, 'g', 3));
    ui->dcEd56->setText(QString::number(veh.RCamberMax, 'g', 3));

    ui->dcEd57->setText(QString::number(veh.RThrustMin, 'g', 3));
    ui->dcEd58->setText(QString::number(veh.RThrust, 'g', 3));
    ui->dcEd59->setText(QString::number(veh.RThrustMax, 'g', 3));
}

Vehicle MainWindow::viewInDcVeh()
{
    Vehicle veh;
    veh.ModelName = CxQString::gbkToStdString(ui->dcEd31->text());
    veh.ModelPy = CxQString::gbkToStdString(ui->dcEd31_2->text());

    veh.BeginDT = CxQString::gbkToStdString(ui->dcEd32->text());
    veh.EndDT = CxQString::gbkToStdString(ui->dcEd33->text());

    veh.Wheelbase = ui->dcEd34->text().toDouble();
    veh.TrackDia = ui->dcEd35->text().toDouble();

    veh.FTreadWidth = ui->dcEd36->text().toDouble();
    veh.RTreadWidth = ui->dcEd37->text().toDouble();

    //
    //    double FToeMin, FToe, FToeMax;
    //    double FCamberMin, FCamber, FCamberMax;
    //    double KpiCasterMin, KpiCaster, KpiCasterMax;
    //    double KpiCamberMin, KpiCamber, KpiCamberMax;
    veh.FToeMin = ui->dcEd41->text().toDouble();
    veh.FToe = ui->dcEd42->text().toDouble();
    veh.FToeMax = ui->dcEd43->text().toDouble();

    veh.FCamberMin = ui->dcEd44->text().toDouble();
    veh.FCamber = ui->dcEd45->text().toDouble();
    veh.FCamberMax = ui->dcEd46->text().toDouble();

    veh.KpiCasterMin = ui->dcEd47->text().toDouble();
    veh.KpiCaster = ui->dcEd48->text().toDouble();
    veh.KpiCasterMax = ui->dcEd49->text().toDouble();

    veh.KpiCamberMin = ui->dcEd4a->text().toDouble();
    veh.KpiCamber = ui->dcEd4b->text().toDouble();
    veh.KpiCamberMax = ui->dcEd4c->text().toDouble();

    //
    //    double RToeMin, RToe, RToeMax;
    //    double RCamberMin, RCamber, RCamberMax;
    //    double RThrustMin, RThrust, RThrustMax;
    veh.RToeMin = ui->dcEd51->text().toDouble();
    veh.RToe = ui->dcEd52->text().toDouble();
    veh.RToeMax = ui->dcEd53->text().toDouble();

    veh.RCamberMin = ui->dcEd54->text().toDouble();
    veh.RCamber = ui->dcEd55->text().toDouble();
    veh.RCamberMax = ui->dcEd56->text().toDouble();

    veh.RThrustMin = ui->dcEd57->text().toDouble();
    veh.RThrust = ui->dcEd58->text().toDouble();
    veh.RThrustMax = ui->dcEd59->text().toDouble();

    return veh;
}

void MainWindow::loadImage(int i, std::string &fn)
{
    string fp2 = Config::imageFilePath(fn);
    QString fp = CxQString::gbkToQString(fp2);
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
    if (! CxFileSystem::isExist(fp2))
    {
        lb->clear();
        ed->clear();
    }
    else
    {
        QImage image(fp);
        ed->setText(fp);
        lb->setPixmap(QPixmap::fromImage(image));
    }
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
            lb = ui->dcImage3;
            ed = ui->dcImageEd3;
            break;
        default:;
    }
    QString selfilter = tr("JPEG (*.jpg *.jpeg)");
    QString fp = QFileDialog::getOpenFileName(this, tr("选择的图像文件"),
                                              "",
                                              tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;TIFF (*.tif)")
//                                              CxQString::gbkToQString(Config::imagePath()),
//                                              tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)" )
    );
    string fp2 = CxQString::gbkToStdString(fp);
    if (CxFileSystem::isExist(fp2))
    {
        string fn;
        if (! CxFileSystem::isSubDirectory(Config::imagePath(), fp2))
        {
            fn = CxTime::currentSystemTimeString('-', 't') + CxFileSystem::extractFileSuffixName(fp2);
            string dst = CxFileSystem::mergeFilePath(Config::imagePath(), fn);
            string src = fp2;
            if (CxFileSystem::copyFile(src, dst) <= 0)
            {
                CxQDialog::ShowPrompt("拷贝图像文件失败，请检查空间与权限！");
                return;
            }
        }
        else
        {
            fn = CxFileSystem::relativeFilePath(Config::imagePath(), fp2);
        }

        QPixmap p;
        p.load(CxQString::gbkToQString(Config::imageFilePath(fn)));
        p.scaled(lb->size(), Qt::KeepAspectRatio);
        lb->setScaledContents(true);
        lb->setPixmap(p);
        ed->setText(CxQString::gbkToQString(fn));
//        lb->setPixmap(QPixmap::fromImage( QImage(CxQString::gbkToQString(dst)) ));
    }
    else
    {
        outInfo(CxString::format("图像文件[%s]不存在，请重新选择!", fp2.c_str()));
    }
}

// add Man
void MainWindow::on_dcBn1_clicked()
{
    ManWindow dialog;
    CxQWidget::setQSS(&dialog, _qssFilePath);

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
    if (dialog.exec() == QDialog::Accepted)
    {
        Man man{
            dialog.ManID,
            dialog.ManName,
            dialog.ManPy,
            dialog.LanID,
            dialog.IsNative,
            dialog.ManLogo
        };
        f_mans.push_back(man);
    }
    else
    {
    }
}

// add Veh
void MainWindow::on_dcBn61_clicked()
{
    string sManName = ui->dcLw1->currentItem() ? CxQString::gbkToStdString(ui->dcLw1->currentItem()->text()) : string();
    if (sManName.empty())
    {
        return;
    }
    Vehicle veh;
    veh.init();
    viewOutDcVeh(veh);
    ui->dcBn61->setEnabled(false);
}

// del Veh
void MainWindow::on_dcBn62_clicked()
{
    if (f_vehicles.size() <= 0 || !ui->dcLw2->currentRow() < 0 || ui->dcLw2->currentRow() >= f_vehicles.size())
    {
        return;
    }
    Vehicle veh = f_vehicles[ui->dcLw2->currentRow()];
    if (! CxQDialog::ShowQuery("请确认删除车型: " + CxQString::gbkToQString(veh.ManName)))
        return;
    int result = Config::mainDb()->execSql(CxString::format("DELETE FROM Vehicle WHERE VehID = %d;", veh.ManID));
    string msg = CxString::format("DELETE FROM Vehicle: {ModelName: %s, ManName: %s}, Status: %s} : ", veh.ManName.c_str(), veh.ModelName.c_str());
    if (result > 0)
    {
        msg = CxString::format(msg.c_str(), "成功");
        f_vehicles.erase(f_vehicles.begin() + ui->dcLw2->currentRow());
        QListWidgetItem * oItem = ui->dcLw2->takeItem(ui->dcLw2->currentRow());
        delete oItem;
    }
    else
    {
        msg = CxString::format(msg.c_str(), "失败");
    }
    outInfo(msg);
    ui->dcBn61->setEnabled(true);
}

// save Veh
void MainWindow::on_dcBn63_clicked()
{
    if (f_vehicles.size() <= 0 || ui->dcLw1->currentRow() < 0 || ui->dcLw1->currentRow() >= f_mans.size())
    {
        CxQDialog::ShowPrompt("品牌不能为空，请选择品牌，再保存！");
        return;
    }
    Man man = f_mans[ui->dcLw1->currentRow()];
    Vehicle veh = viewInDcVeh();
    if (veh.isValid())
    {
        veh.ManID = man.ManID;
        veh.ManName = man.ManName;
        veh.ManPy = man.ManPy;
        // in Add Status
        if (! ui->dcBn61->isEnabled())
        {
            int VehID = Config::maxVehId()+1;
            string msg = CxString::format("添加车型{Vehicle: {ManID: %d, ManName: %s, VehID: %d, ModelName: %s}}", veh.ManID, veh.ManName.c_str(), veh.VehID, veh.ModelName.c_str());
            int r = insertVeh(VehID, veh);
            if (r > 0)
            {
                Config::setMaxVehId(VehID);
                f_vehicles.push_back(veh);
                int r2 = insertUpdateVehImage(VehID);
                msg += " 成功, Image.Result: " + CxString::toString(r2) + CxTime::currentSystemTimeString();
            }
            else
            {
                msg += " 失败！" + CxTime::currentSystemTimeString();
            }
            outInfo(msg);
        }
        else
        {
            string msg = CxString::format("更新车型{Vehicle: {ManID: %d, ManName: %s, VehID: %d, ModelName: %s}}", veh.ManID, veh.ManName.c_str(), veh.VehID, veh.ModelName.c_str());
            if (f_vehicles.size() > 0 && ui->dcLw2->currentRow() >= 0 && ui->dcLw2->currentRow() < f_vehicles.size())
            {
                int VehID = f_vehicles[ui->dcLw2->currentRow()].VehID;
                int r = updateVeh(VehID, veh);
                if (r > 0)
                {
                    if (f_vehicles.size() >= 0 && ui->dcLw2->currentRow() >= 0 && ui->dcLw2->currentRow() < f_vehicles.size())
                    {
                        f_vehicles[ui->dcLw2->currentRow()] =veh;
                    }
                    int r2 = insertUpdateVehImage(veh.VehID);
                    msg += " 成功, Image.Result: " + CxString::toString(r2) + CxTime::currentSystemTimeString();
                }
                else
                {
                    msg += " 失败！" + CxTime::currentSystemTimeString();
                }
            }
            else
            {
                msg += " 失败！（界面错误，请重启！）" + CxTime::currentSystemTimeString();
            }
            outInfo(msg);
        }
        ui->dcBn61->setEnabled(true);
    }
    else
    {
        CxQDialog::ShowPrompt("车型与车型拼音不能为空，请检查！");
    }
}

void MainWindow::on_muDbExport_clicked()
{
    DbExportWindow dialog;
    CxQWidget::setQSS(&dialog, _qssFilePath);

    dialog.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            dialog.size(),
            qApp->desktop()->availableGeometry()
        )
    );
    if (dialog.exec() == QDialog::Accepted)
    {
    }
    else
    {
    }
}

void MainWindow::on_muDbBackup_clicked()
{
    DbBackupWindow dialog;
    CxQWidget::setQSS(&dialog, _qssFilePath);

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
    if (dialog.exec() == QDialog::Accepted)
    {
    }
    else
    {
    }
}

