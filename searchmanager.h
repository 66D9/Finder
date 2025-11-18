#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <QObject>
#include <QThreadPool>

class SearchManager : public QObject
{
    Q_OBJECT
public:
    explicit SearchManager(QObject *parent = nullptr);

    void Search(const QString&, const QString& );

    void startSearch(const QString&)const;

private:
    QThreadPool* m_threadPool;
    QString m_keyword;

private slots:
    void onSearchFinished(const QStringList&, const QStringList&);


signals:

    void searchResultReady(const QStringList&);
};

#endif // SEARCHMANAGER_H
