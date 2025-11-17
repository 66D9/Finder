#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <QObject>

class SearchManager : public QObject
{
    Q_OBJECT
public:
    explicit SearchManager(QObject *parent = nullptr);

    QStringList Search(const QString&, const QString& )const;

signals:
};

#endif // SEARCHMANAGER_H
