#include "manwindow.h"
#include "ui_manwindow.h"

#include <QFileDialog>
#include <QBuffer>

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

    std::map<int, std::string> langInfos = Config::langInfos();
    for (typename std::map<int, std::string>::const_iterator it = langInfos.begin(); it != langInfos.end(); ++it)
    {
        ui->maEd3->addItem(CxQString::gbkToQString(it->second), it->first);
    }
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
    int ManID = Config::maxManId()+1;
    string ManName = CxQString::gbkToStdString(ui->maEd1->text());
    string ManPy = CxQString::gbkToStdString(ui->maEd2->text());
    int LanID = ui->maEd3->currentData().toInt();
    int IsNative = ui->maEd4->isChecked() ? 1 : 0;
    QByteArray arr;
    QBuffer buffer(&arr);
    buffer.open(QIODevice::WriteOnly);
    _image.save(&buffer, "JPEG");
    vector<char> ManLogo(arr.size());
    memcpy(ManLogo.data(), arr.data(), arr.size());

    SQL::Con db((sqlite3 *) Config::mainDb()->getDb());

    string sSql = "INSERT INTO Man(\"ManID\", \"ManName\", \"ManPy\", \"LanID\", \"IsNative\", \"ManLogo\") VALUES (?, ?, ?, ?, ?, ?);";
    vector<tuple<int, string, string, int, int, vector<char>>> rows;
    rows.push_back(tuple<int, string, string, int, int, vector<char>>(ManID, ManName, ManPy, LanID, IsNative, ManLogo));
    int r = db.bindnexec<int, string, string, int, int, vector<char>>(sSql, rows);

    sqlResult = r;

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
                                                      tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)" ));

            _image = QImage(fp);
            ui->maEd6_2->setText(fp);
            ui->maEd6->setPixmap(QPixmap::fromImage(_image));
        }
    }
    return QDialog::eventFilter(watched, event);
}
