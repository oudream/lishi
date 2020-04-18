#include "dbbackupwindow.h"
#include "ui_dbbackupwindow.h"

#include <ccxx/cxappenv.h>
#include <ccxx/cxqtutil.h>

#include "config.h"

using namespace std;

DbBackupWindow::DbBackupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbBackupWindow)
{
    ui->setupUi(this);

    std::vector<CxFileSystem::PathInfo> ps;
    CxFileSystem::scanDir(Config::dbBackupPath(), ps);
    for (int i = 0; i < ps.size(); ++i)
    {
        CxFileSystem::PathInfo pi = ps[i];
        if (CxString::containCase(pi.fileName, ".db"))
        {
            QListWidgetItem *item = new QListWidgetItem(CxQString::gbkToQString(pi.fileName));
            ui->buLw->addItem(item);
        }
    }
}

DbBackupWindow::~DbBackupWindow()
{
    delete ui;
}

void DbBackupWindow::on_buBackupBn_clicked()
{
    string p = Config::dbBackupPath();
    string f = CxFileSystem::extractFilePrefixName(Config::mainDbFilePath()) + "-" + CxTime::currentSystemTimeString('-', '-') + ".db";
    string dst = CxFileSystem::mergeFilePath(p, f);
    string src = Config::mainDbFilePath();
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
        QListWidgetItem *item = new QListWidgetItem(CxQString::gbkToQString(f));
        ui->buLw->addItem(item);
        st = "完成";
    }

    CxQDialog::ShowPrompt(CxQString::gbkToQString(msg + ". " + st + ". " + CxTime::currentSystemTimeString()));
}

void DbBackupWindow::on_buRestoreBn_clicked()
{
    if (! ui->buLw->currentItem()) return;
    QString buFileName = ui->buLw->currentItem()->text();
    string p = Config::dbBackupPath();
    string f = CxFileSystem::extractFilePrefixName(Config::mainDbFilePath()) + "-" + CxTime::currentSystemTimeString('-', '-') + ".db";
    string src = CxFileSystem::mergeFilePath(Config::dbBackupPath(), CxQString::gbkToStdString(buFileName));
    string dst = Config::mainDbFilePath();
    string st = "失败";
    string msg = "还原文件到：" + dst;
    if (! CxFileSystem::isExist(src))
    {
        CxQDialog::ShowPrompt("还原的文件不存在失败，请确认后再还原！");
        return ;
    }
    if (CxFileSystem::isExist(dst))
    {
        if (CxQDialog::ShowQuery(CxQString::gbkToQString(msg + "\n\n原文件会给删除，请确认？")))
        {
            if (!CxFileSystem::deleteFile(dst))
            {
                CxQDialog::ShowPrompt("删除文件失败，还原停止！");
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

    CxQDialog::ShowPrompt(CxQString::gbkToQString(msg + ". " + st + ". " + CxTime::currentSystemTimeString()));
}

