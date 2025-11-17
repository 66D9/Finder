#ifndef SEARCHTASK_H
#define SEARCHTASK_H

#include <QObject>

class SearchTask : public QObject
{
    Q_OBJECT
public:
    explicit SearchTask(QObject *parent = nullptr);

signals:
};

#endif // SEARCHTASK_H
