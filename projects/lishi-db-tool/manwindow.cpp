#include "manwindow.h"
#include "ui_manwindow.h"

#include <QFileDialog>
#include <QBuffer>
#include <QScreen>

#include <ccxx/cxqtutil.h>
#include <ccxx/cxappenv.h>
#include "config.h"

#include "sqlite3template.hpp"

using namespace std;

ManWindow::ManWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManWindow)
{
    ui->setupUi(this);

    ui->maEd6->installEventFilter(this);

    for(auto & langInfo: Config::langInfos())
    {
        ui->maEd3->addItem(CxQString::gbkToQString(langInfo.second), langInfo.first);
    }
    QSize size = qApp->screens()[0]->size();
    ui->maEd6->setMaximumSize(size.width() * 0.33, size.height() * 0.33);
}

ManWindow::~ManWindow()
{
    delete ui;
}

void ManWindow::on_maBn1_clicked()
{
//    [ManID] integer  NOT NULL,
//    [ManName] nvarchar(50)  NULL,
//    [ManPy] nvarchar(50)  NULL,
//    [LanID] integer  NULL,
//    [IsNative] bit  NULL,
//    [ManLogo] blob(2147483647)  NULL,
    ManID = Config::maxManId() + 1;
    ManName = CxQString::gbkToStdString(ui->maEd1->text());
    ManPy = CxQString::gbkToStdString(ui->maEd2->text());
    LanID = ui->maEd3->currentData().toInt();
    IsNative = ui->maEd4->isChecked() ? 1 : 0;
//    QByteArray arr;
//    QBuffer buffer(&arr);
//    buffer.open(QIODevice::WriteOnly);
//    ManLogoImage.save(&buffer, "JPEG");
//    ManLogo.resize(arr.size());
//    memcpy(ManLogo.data(), arr.data(), arr.size());
//
//
//    QByteArray inByteArray;
//    QBuffer inBuffer( &inByteArray );
//    inBuffer.open( QIODevice::WriteOnly );
//    ManLogoImage.save( &inBuffer, "PNG" ); // write inPixmap into inByteArray in PNG format


    if (ManName.empty() || ManPy.empty() || ManLogo.size()<=0)
    {
        CxQDialog::ShowPrompt("[ 品牌名称 | 品牌拼音 | LOGO图标 ] 不能为空！请重新填选！");
        return;
    }

    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());

    string sSql = "INSERT INTO Man(\"ManID\", \"ManName\", \"ManPy\", \"LanID\", \"IsNative\", \"ManLogo\") VALUES (?, ?, ?, ?, ?, ?);";
    vector<tuple<int, string, string, int, int, vector<char>>> rows;
    rows.push_back(tuple<int, string, string, int, int, vector<char>>(ManID, ManName, ManPy, LanID, IsNative, ManLogo));
    int r = db.bindnexec<int, string, string, int, int, vector<char>>(sSql, rows);

    sqlResult = r;

    if (r > 0)
    {
        Config::setMaxManId(ManID);
    }

    accept();
}

void ManWindow::on_maBn2_clicked()
{
    reject();
}

bool ManWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->maEd6)
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            QString selfilter = tr("JPEG (*.jpg *.jpeg)");
            QString fp = QFileDialog::getOpenFileName(this, tr("选择的图像文件"),
                                                      CxQString::gbkToQString(Config::imagePath()),
                                                      tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)"));

            string s = CxFile::load(CxQString::gbkToStdString(fp));
            ManLogo.resize(s.size());
            memcpy(ManLogo.data(), s.data(), s.size());
            ManLogoImage = QImage(fp);
            QPixmap p = QPixmap::fromImage(ManLogoImage);
//            p.load(fp);
            p.scaled(ui->maEd6->size(), Qt::KeepAspectRatio);
            ui->maEd6->setScaledContents(true);
            ui->maEd6->setPixmap(p);
            ui->maEd6_2->setText(fp);
        }
    }
    return QDialog::eventFilter(watched, event);
}
