#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QStringList>
#include <QUrl>

QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (const QString &arg : args.mid(1)) {
        if (!arg.startsWith(QLatin1Char('-')))
            return QUrl::fromUserInput(arg);
    }
    return QUrl(QStringLiteral("https://www.baidu.com"));
}

QUrl url = commandLineUrlArgument();


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWebEngineView *webView = new QWebEngineView(ui->pnLeft);
    QWebEnginePage *webPage = new QWebEnginePage(QWebEngineProfile::defaultProfile(), webView);
    webView->setPage(webPage);
    webView->setUrl(url);
    ui->pnLeft->layout()->addWidget(webView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

