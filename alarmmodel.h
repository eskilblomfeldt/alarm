#ifndef ALARMMODEL_H
#define ALARMMODEL_H

#include <QAbstractItemModel>
#include <QDate>
#include <QPair>

class QFileSystemWatcher;
class AlarmModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    AlarmModel(QObject *parent = 0);
    ~AlarmModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE bool addAlarm(const QDate &date, const QString &name);
    Q_INVOKABLE bool removeAlarm(const QDate &date, const QString &name);

    QString firstAlarmForDate(const QDate &date);

private slots:
    void updateAlarms();

private:
    static QString alarmsPath(const QDate &date = QDate());
    bool dateExhausted(const QDate &date) const;
    void markDateAsExhausted(const QDate &date) const;

    QFileSystemWatcher *m_alarmsWatcher;
    QList<QPair<QDate, QString> > m_alarms;
};

#endif // ALARMMODEL_H
