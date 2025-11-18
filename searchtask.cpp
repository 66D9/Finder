#include "searchtask.h"
#include <QDir>

SearchTask::SearchTask( const QString& keyword, const QString& path, QObject *parent)
    :QObject{parent}
    ,m_keyword(keyword)
    ,m_path(path)

{

}
void SearchTask::run()
{
    QDir dir(m_path);

    QStringList fileList = dir.entryList();
    QStringList matchedFiles;
    for (const QString &fileName : fileList) {
        if (fileName.contains(m_keyword, Qt::CaseInsensitive)) { // 忽略大小写匹配
            matchedFiles << (m_path + '/' + fileName);
        }
    }
    dir.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
    QStringList subdirList = dir.entryList();
    for(QString &subdir : subdirList)
    {
        subdir = m_path + '/' + subdir;
    }
    emit searchFinished(subdirList,matchedFiles);
}
