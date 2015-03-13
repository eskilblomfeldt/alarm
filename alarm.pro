TEMPLATE = app

QT += qml quick widgets androidextras core-private

SOURCES += main.cpp \
    alarmmodel.cpp \
    jni.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    alarmmodel.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/src/org/qtproject/example/alarm/CheckBirthdayService.java \
    android/src/org/qtproject/example/alarm/BirthdayAlarm.java

SUBDIRS += \
    android/templates.pro

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
