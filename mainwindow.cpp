#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new SearchManager(this);

    ui->tBSearchResult->setOpenLinks(false);
    connect(manager,&SearchManager::searchResultReady,this,&MainWindow::onsearchResultReady);
    connect(ui->tBSearchResult, &QTextBrowser::anchorClicked,
            this, &MainWindow::onFileLinkClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pBSelectDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this,tr("选择查找目录"),"C:\\" ,QFileDialog::ShowDirsOnly);
    if(!dir.isEmpty())
    {
        ui->lSearchDir->setText(dir);
    }
}


void MainWindow::on_pBSearch_clicked()
{
    QString searchDir = ui->lSearchDir->text();
    QString searchText = ui->lESearchStr->text();
    if(searchDir.isEmpty() || searchText.isEmpty())
    {
        QMessageBox::warning(this,"错误！","无效路径或查询字符！");
        return;
    }

    manager->Search(searchDir,searchText);
    ui->tBSearchResult->clear();

}

void MainWindow::onsearchResultReady(const QStringList& matchedFiles)
{

    if(matchedFiles.isEmpty())
    {
        ui->tBSearchResult->setText("没有任何匹配结果。");
        return;
    }

    for(const QString& matchedfile : matchedFiles)
    {
        QString link = QString("<a href=\"file:///%1\">%1</a><br>").arg(matchedfile);
        ui->tBSearchResult->insertHtml(link);
    }
}

void MainWindow::onFileLinkClicked(const QUrl& url)
{
    // 确保是本地文件路径
    if (url.scheme() == "file") {
        // 使用系统默认程序打开文件
        bool success = QDesktopServices::openUrl(url);
        if (!success) {
            QMessageBox::warning(this, "错误", "无法打开文件: " + url.toLocalFile());
        }
    }
}
