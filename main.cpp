#include "alarmmodel.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    AlarmModel *alarmModel = new AlarmModel(&engine);
    engine.rootContext()->setContextProperty(QStringLiteral("alarmModel"),
                                             alarmModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
