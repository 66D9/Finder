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

    QStringList matchedFiles = manager->Search(searchDir,searchText);

    ui->tBSearchResult->clear();
    if(matchedFiles.isEmpty())
    {
        ui->tBSearchResult->setText("没有任何匹配结果。");
        return;
    }

    for(const QString& matchedfile : matchedFiles)
    {
        ui->tBSearchResult->append(matchedfile);
    }

}

