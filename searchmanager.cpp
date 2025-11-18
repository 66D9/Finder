#include "searchmanager.h"
#include <QDir>
#include "searchtask.h"

SearchManager::SearchManager(QObject *parent)
    : QObject{parent}
{
    m_threadPool = new QThreadPool(this);
    m_threadPool->setMaxThreadCount(4);

}

void SearchManager::Search(const QString& searchDir, const QString& searchText)
{
    m_keyword = searchText;
    startSearch(searchDir);
}

void SearchManager::startSearch(const QString& path)const
{
    SearchTask* task = new SearchTask(m_keyword, path);
    task->setAutoDelete(false);

    // 连接任务完成信号到管理器的槽
    connect(task, &SearchTask::searchFinished,
            this, &SearchManager::onSearchFinished,
            Qt::QueuedConnection); // 显式指定队列连接（安全）

    // 提交任务到线程池
    m_threadPool->start(task);
}

void SearchManager::onSearchFinished(const QStringList& subdir, const QStringList& results)
{
    if(!results.isEmpty())
    {
        emit searchResultReady(results);
    }
    for(const QString& dir : subdir)
    {
        startSearch(dir);
    }

    // 手动 delete 任务对象（因为我们 setAutoDelete(false)）
    SearchTask* task = qobject_cast<SearchTask*>(sender());
    if (task) {
        task->deleteLater(); // 安全删除（跨线程）
    }
}
