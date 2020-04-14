#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QListView>
#include <QListWidgetItem>

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QStringList>
#include <QUrl>

#include <tuple>
#include <exception>
#include <cstdint>

#include <ccxx/sqlite3/sqlite3.h>
#include <ccxx/cxapplication.h>
#include <ccxx/cxdatabase.h>
#include <ccxx/cxinterinfo.h>
#include <ccxx/cxqtutil.h>

namespace SQL
{
    using std::string;
    using std::vector;
    using std::tuple;

    typedef std::runtime_error SQLRTerror;

    template<typename T>
    static T get_single(sqlite3_stmt *ppsm, int iCol);

    template<>
    inline int get_single(sqlite3_stmt *ppsm, int iCol)
    {
        return sqlite3_column_int(ppsm, iCol);
    }

    template<>
    inline std::int64_t get_single(sqlite3_stmt *ppsm, int iCol)
    {
        return sqlite3_column_int64(ppsm, iCol);
    }

    template<>
    inline double get_single(sqlite3_stmt *ppsm, int iCol)
    {
        return sqlite3_column_double(ppsm, iCol);
    }

    template<>
    inline std::string get_single(sqlite3_stmt *ppsm, int iCol)
    {
        const char *foo = reinterpret_cast<const char *>(sqlite3_column_text(ppsm, iCol));
        return (foo ? string(foo) : "");
    }

    template<>
    inline std::vector<char> get_single(sqlite3_stmt *ppsm, int iCol)
    {
        size_t len = sqlite3_column_bytes(ppsm, iCol);
        const char *foo = reinterpret_cast<const char *>(sqlite3_column_blob(ppsm, iCol));
        if (foo)
        {
            std::vector<char> r(len);
            memcpy(r.data(), foo, len);
            return r;
        }
        return std::vector<char>();
    }

    class Con {
    protected:
        sqlite3 *_db;

    private:
        string _dbfilename;
        bool _autoClose;

    public:
        Con(const string &dbfile) :
            _dbfilename(dbfile),
            _autoClose(false)
        {
            int erg;
            erg = sqlite3_open(_dbfilename.c_str(), &_db);
            if (erg != SQLITE_OK)
            {
                throw (SQLRTerror(sqlite3_errmsg(_db)));
            }
            _autoClose = true;
        }

        Con(sqlite3 *db1) :
            _db(db1),
            _autoClose(false)
        {
            _dbfilename = string(sqlite3_db_filename(db1, NULL));
        }

        ~Con()
        {
            if (_autoClose)
            {
                sqlite3_close(_db);
            }
        }

    private:
        struct PPSM {
            sqlite3_stmt *me;

            PPSM(sqlite3 *db, const string &query) :
                me(nullptr)
            {
                if (sqlite3_prepare_v2(db, query.c_str(), query.size(),
                                       &me, nullptr)
                    != SQLITE_OK)
                {
                    throw (SQLRTerror(sqlite3_errmsg(db)));
                }
            }

            void bindvals(vector<string> &&vals)
            {
                int pos = 0;
                for (auto &v : vals)
                {
                    sqlite3_bind_text(me, ++pos, v.c_str(), v.size(), SQLITE_TRANSIENT);
                }
            }

            ~PPSM()
            {
                sqlite3_finalize(me);
            }

        };

    public:

//> Within the initializer-list of a braced-init-list, the initializer-clauses, including
// any that result from pack expansions, are evaluated in the order in which they appear.
// That is, every value computation and side effect associated with a given initializer-clause
// is sequenced before every value computation and side effect associated with any
// initializer-clause that follows it in the comma-separated list of the initializer-list.

        template<typename ...ARGS>
        vector<tuple<ARGS...>> bindnquery(const string &query,
                                          vector<string> &&bindvals = {})
        {
            PPSM ppsm(_db, query);
            ppsm.bindvals(std::forward<decltype(bindvals)>(bindvals));
            vector<tuple<ARGS...> > answer{};

            while (sqlite3_step(ppsm.me) == SQLITE_ROW)
            {
                int col = 0;
#pragma GCC diagnostic ignored "-Wsequence-point"
                tuple<ARGS...> r{get_single<ARGS>(ppsm.me, (col++))...};
                answer.push_back(r);
            }
            return answer;
        }

        //for  update and such....
        void query_nothing(const string &query, vector<string> &&bindvals = {})
        {
            PPSM ppsm(_db, query);
            ppsm.bindvals(std::forward<decltype(bindvals)>(bindvals));
            auto result = sqlite3_step(ppsm.me);
            if (result == SQLITE_BUSY)
            {
                do
                {
                    sched_yield();
                    result = sqlite3_step(ppsm.me);;
                }
                while (result == SQLITE_BUSY);
            }
        }

        template<typename QType>
        QType query_one(const string &query, vector<string> &&bindvals = {})
        {
            PPSM ppsm(_db, query);
            ppsm.bindvals(std::forward<decltype(bindvals)>(bindvals));
            if (sqlite3_step(ppsm.me) != SQLITE_ROW)
            {
                throw (std::runtime_error("Query did not yield answer:" + query));
            }
            return get_single<QType>(ppsm.me, 0);
        }
    };

}

using namespace std;

QUrl f_url = QUrl(QStringLiteral("http://news.baidu.com/"));
string f_fpDb = "";
CxDatabase *f_db = NULL;

int fn_init()
{
    f_fpDb = CxFileSystem::normalize(CxFileSystem::mergeFilePath(CxAppEnv::applicationDeployPath(), "../alignerchen/lsmasterlite.db"));
    cxPrompt() << "sqlite db file path: " << f_fpDb;
    f_db = CxDatabaseManager::createDatabase(f_fpDb);
    f_db->openDatabase();

    return 0;
}

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
    sCount = f_db->queryValue("select count(*) from sqlite_master where type='table' and name='t1';");
    if (CxString::toInt32(sCount) <= 0)
    {
        cxPromptCheck(f_db->execSql(CREATE_T1), return false);
    }

    SQL::Con db((sqlite3 *) f_db->getDb());

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

    return 0;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebEngineView *webView = new QWebEngineView(ui->pnLeft);
    QWebEnginePage *webPage = new QWebEnginePage(QWebEngineProfile::defaultProfile(), webView);
    webView->setPage(webPage);
    webView->setUrl(f_url);
    ui->pnLeft->layout()->addWidget(webView);

    connect(ui->dcBn1, SIGNAL(clicked()), this, SLOT(dcBn1ClickedSlot()));
    connect(ui->dcBn2, SIGNAL(clicked()), this, SLOT(dcBn2ClickedSlot()));
    connect(ui->dlBn1, SIGNAL(clicked()), this, SLOT(dlBn1ClickedSlot()));
//    connect(ui->dcLw1, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(dcLw1currentItemChanged()));

    fn_init();
    fn_helloDb1();

    ui->buPathEd->setText(CxQString::gbkToQString(CxAppEnv::dataPath()));
    ui->buFileNameEd->setText(CxQString::gbkToQString(
        CxFileSystem::extractFilePrefixName(f_fpDb) + "-" + CxTime::currentDayString('-') + ".db"));

    SQL::Con db((sqlite3 *) f_db->getDb());

    {
        string sSql = "SELECT ManID, ManName, ManLogo FROM Man;";
        sqlite3 *db = (sqlite3 *) f_db->getDb();
        int rc, ncols;
        sqlite3_stmt *stmt;
        const char *tail;
        rc = sqlite3_prepare(db, sSql.c_str(), sSql.size(), &stmt, &tail);
        if (rc != SQLITE_OK)
        {
            return;
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

    auto a = db.bindnquery<int, string, vector<char>>("SELECT ManID, ManName, ManLogo FROM Man;");
    std::cout << "erg :" << std::endl;
    for (auto x:a)
    {
        int iManID = std::get<0>(x);
        string sManName = std::get<1>(x);
        vector<char> sManLogo = std::get<2>(x);
//        CxFile::save(CxFileSystem::mergeFilePath(CxAppEnv::tempPath(), sManName + ".png"), string(sManLogo.data(), sManLogo.size()));
        std::cout << iManID << " " << sManName << " " << std::endl;
        QPixmap pm;
        pm.loadFromData((const uchar *) sManLogo.data(), (uint) sManLogo.size(), "JFIF");
        QListWidgetItem *item = new QListWidgetItem(QIcon(pm), CxQString::gbkToQString(sManName));
        ui->dcLw1->addItem(item);
    }

    QFile file(CxQString::gbkToQString(CxFileSystem::mergeFilePath(CxAppEnv::configPath(), "Aqua.qss")));
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);
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

void MainWindow::on_dcEd1_textChanged(const QString &arg1)
{

}

void MainWindow::on_dcLw1_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    string s = CxQString::gbkToStdString(current->text());
    SQL::Con db((sqlite3 *) f_db->getDb());
    QListWidget *lw = ui->dcLw2;
    lw->clear();
    for (auto row: db.bindnquery<string, double, double, double, double, double>(CxString::format("SELECT ModelName, FToeMin, FToeMax, FToe, FToeSumMin, FToeSumMax FROM Vehicle WHERE ManName == '%s'", s.c_str())))
    {
        QListWidgetItem *item = new QListWidgetItem(CxQString::gbkToQString(std::get<0>(row)));
        lw->addItem(item);
    }
}

void MainWindow::on_dcLw2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

}

void MainWindow::on_buPathBn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("选择备份的目录"),
                                                    CxQString::gbkToQString(CxAppEnv::dataPath()),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
}

void MainWindow::on_buRunBn_clicked()
{
    string p = CxQString::gbkToStdString(ui->buPathEd->text());
    string f = CxQString::gbkToStdString(ui->buFileNameEd->text());
    string dst = CxFileSystem::mergeFilePath(p, f);
    string src = f_fpDb;
    string st = "失败";
    string msg = "备份文件到：" + dst;
    if (CxFileSystem::isExist(dst))
    {
        if (CxQDialog::ShowQuery(CxQString::gbkToQString(msg + "\n\n文件已存在，请确认是否要覆盖？")))
        {
            if (!CxFileSystem::deleteFile(dst))
            {
                CxQDialog::ShowPrompt("删除文件失败，备份停止！");
                return;
            }
        }
        else
        {
            return;
        }
    }
    if (CxFileSystem::copyFile(src, dst) > 0)
    {
        st = "完成";
    }
    outInfo(msg + ". " + st + ". " + CxTime::currentSystemTimeString());
}

void MainWindow::outInfo(const QString &s)
{
    ui->statusbar->showMessage(s);
}

void MainWindow::outInfo(const std::string &s)
{
    outInfo(CxQString::gbkToQString(s));
}
