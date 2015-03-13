#include "alarmmodel.h"

#include <QFile>
#include <QStandardPaths>
#include <QFileSystemWatcher>
#include <QDirIterator>
#include <QDebug>

AlarmModel::AlarmModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QDir().mkpath(alarmsPath());

    updateAlarms();

    m_alarmsWatcher = new QFileSystemWatcher(this);
    m_alarmsWatcher->addPath(alarmsPath());
    connect(m_alarmsWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(updateAlarms()));
}

AlarmModel::~AlarmModel()
{
}

QString AlarmModel::firstAlarmForDate(const QDate &date)
{
    if (dateExhausted(date))
        return QString();

    markDateAsExhausted(date);
    for (int i = 0; i < m_alarms.size(); ++i) {
        QPair<QDate, QString> alarm = m_alarms.at(i);

        if (alarm.first.day() == date.day() && alarm.first.month() == date.month())
            return alarm.second;
    }

    return QString();
}

int AlarmModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_alarms.size();
    else
        return 0;
}

int AlarmModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QModelIndex AlarmModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid())
        return createIndex(row, column);
    else
        return QModelIndex();
}

QModelIndex AlarmModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

QVariant AlarmModel::data(const QModelIndex &index, int role) const
{
    QPair<QDate, QString> birthday = m_alarms.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
        return birthday.first.toString(Qt::SystemLocaleLongDate) + QLatin1Char(' ') + birthday.second;
    }

    return QVariant();
}

QString AlarmModel::alarmsPath(const QDate &date)
{
    return QStandardPaths::writableLocation(QStandardPaths::DataLocation)
            + QStringLiteral("/alarms/")
            + (date.isValid() ? date.toString(QStringLiteral("yyyy_MM_dd")) : QString());
}

bool AlarmModel::addAlarm(const QDate &date, const QString &name)
{
    QFile file(alarmsPath(date) + QLatin1Char('_') + name);
    if (file.exists()) // Already registered
        return true;

    return file.open(QIODevice::WriteOnly);
}

bool AlarmModel::removeAlarm(const QDate &date, const QString &name)
{
    QFile file(alarmsPath(date) + QLatin1Char('_') + name);
    if (!file.exists()) // Not registered
        return false;

    return file.remove();
}

void AlarmModel::updateAlarms()
{
    beginResetModel();
    m_alarms.clear();
    QDirIterator it(alarmsPath(), QDir::Files);
    while (it.hasNext()) {
        it.next();

        QString fileName = it.fileName();

        QStringList split = fileName.split(QLatin1Char('_'));
        if (split.size() != 4)
            continue;

        bool ok;
        int year = split.at(0).toInt(&ok);
        if (!ok)
            continue;

        int month = split.at(1).toInt(&ok);
        if (!ok)
            continue;

        int day = split.at(2).toInt(&ok);
        if (!ok)
            continue;

        QString name = split.at(3);
        m_alarms.append(qMakePair(QDate(year, month, day), name));
    }
    endResetModel();
}

bool AlarmModel::dateExhausted(const QDate &date) const
{
    qDebug() << alarmsPath() << QDir(alarmsPath()).entryList();

    return QFileInfo(alarmsPath(date)).exists();
}

void AlarmModel::markDateAsExhausted(const QDate &date) const
{
    QFile file(alarmsPath(date));
    if (!file.open(QIODevice::WriteOnly))
        qWarning() << "Can't open" << file.fileName();
}