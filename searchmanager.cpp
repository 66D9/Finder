#include "searchmanager.h"
#include <QDir>

SearchManager::SearchManager(QObject *parent)
    : QObject{parent}
{}

QStringList SearchManager::Search(const QString& searchDir, const QString& searchText)const
{
    QDir dir(searchDir);
    dir.setFilter(QDir::Files|QDir::NoDotAndDotDot);
    QStringList fileList = dir.entryList();

    QStringList matchedFiles;
    for (const QString &fileName : fileList) {
        if (fileName.contains(searchText, Qt::CaseInsensitive)) { // 忽略大小写匹配
            matchedFiles << fileName;
        }
    }
    return matchedFiles;
}
