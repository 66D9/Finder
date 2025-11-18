#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "searchmanager.h"
#include <QUrl>
#include <QDesktopServices>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pBSelectDir_clicked();

    void on_pBSearch_clicked();

    void onsearchResultReady(const QStringList&);
    void onFileLinkClicked(const QUrl& url);


private:
    Ui::MainWindow *ui;

    SearchManager *manager;
};
#endif // MAINWINDOW_H
