#ifndef SEARCHTASK_H
#define SEARCHTASK_H

#include <QObject>
#include <QRunnable>

class SearchTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit SearchTask(const QString& keyword, const QString& path,QObject *parent = nullptr);
    void run() override;

signals:
    void searchFinished(const QStringList&,const QStringList&);

private:
    QString m_keyword;
    QString m_path;
};

#endif // SEARCHTASK_H
