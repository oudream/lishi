#include "dbexportwindow.h"
#include "ui_dbexportwindow.h"

#include <QFileDialog>

#include <ccxx/cxappenv.h>
#include <ccxx/cxqtutil.h>

#include "config.h"

using namespace std;

DbExportWindow::DbExportWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbExportWindow)
{
    ui->setupUi(this);

    ui->epEd1->setText(CxQString::gbkToQString(Config::mainDbFilePath()));

    std::map<int, std::string> langInfos = Config::langInfos();
    for (typename std::map<int, std::string>::const_iterator it = langInfos.begin(); it != langInfos.end(); ++it)
    {
        ui->epCb2->addItem(CxQString::gbkToQString(it->second), it->first);
    }
}

DbExportWindow::~DbExportWindow()
{
    delete ui;
}

void DbExportWindow::on_epBn1_clicked()
{
    QString fp = QFileDialog::getOpenFileName(this, tr("选择的数据库文件"),
                                                    CxQString::gbkToQString(CxAppEnv::dataPath()),
                                                    ".db");
    if (!fp.isEmpty())
    {
        ui->epEd1->setText(fp);
    }
}

void DbExportWindow::on_epBn2_clicked()
{
    int lang = ui->epCb2->currentData().toInt();
//    if (ui->epCb2->currentData() == QVariant::Invalid)
    if (lang < 1)
    {
        CxQDialog::ShowPrompt("区域语言不正确，导出停止！");
        return;
    }

    string p = CxAppEnv::dataPath();
    string f = CxFileSystem::extractFilePrefixName(Config::mainDbFilePath()) + "-lang-" + CxString::toString(lang) + ".db";
    string dst = CxFileSystem::mergeFilePath(p, f);
    string src = CxQString::gbkToStdString(ui->epEd1->text());
    string st = "失败";
    string msg = "导出文件到：" + dst;
    if (! CxFileSystem::isExist(src))
    {
        CxQDialog::ShowPrompt("源数据库不存在，导出停止！");
        return;
    }
    if (CxFileSystem::isExist(dst))
    {
        if (CxQDialog::ShowQuery(CxQString::gbkToQString(msg + "\n\n文件已存在，请确认是否要覆盖？")))
        {
            if (!CxFileSystem::deleteFile(dst))
            {
                CxQDialog::ShowPrompt("删除文件失败，导出停止！");
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
        CxDatabase * db = CxDatabaseManager::createDatabase(dst);
        db->openDatabase();
        if (! db->isOpen()){
            CxQDialog::ShowPrompt("导出失败，不能操作导出的数据库文件！");
            return;
        }
        db->execSql(CxString::format("DELETE FROM Man WHERE LanID!=%d;", lang));
        db->execSql(CxString::format("DELETE FROM Vehicle WHERE LanID!=%d;", lang));
        db->closeDatabase();
        st = "完成";
    }

    ui->epPte3->appendPlainText(CxQString::gbkToQString(msg + ". " + st + ". " + CxTime::currentSystemTimeString()));
}

