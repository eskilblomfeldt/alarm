#include "alarmmodel.h"

#include <QDebug>
#include <QtAndroidExtras/QAndroidJniObject>

#include <QtCore/private/qjnihelpers_p.h>
#include <QStandardPaths>

#include <android/log.h>
#include <jni.h>

static jstring nextBirthday(JNIEnv *env, jclass)
{
    AlarmModel model;

    qDebug() << "Activity:" << QtAndroidPrivate::activity() << "Service:" << QtAndroidPrivate::service() << QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    return reinterpret_cast<jstring>(env->NewGlobalRef(QAndroidJniObject::fromString(model.firstAlarmForDate(QDate::currentDate())).object()));
}

static JNINativeMethod methods[] = {
    {"nextBirthday", "()Ljava/lang/String;", (void *) nextBirthday}
};

static int registerNatives(JNIEnv *env)
{
    jclass clazz = env->FindClass("org/qtproject/example/alarm/CheckBirthdayService");
    if (clazz == 0) {
        __android_log_print(ANDROID_LOG_FATAL, "Qt", "Failed to find CheckBirthdayService class");
        return JNI_FALSE;
    }

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        __android_log_print(ANDROID_LOG_FATAL, "Qt", "RegisterNatives failed");
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

Q_DECL_EXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void */*reserved*/)
{
    QT_USE_NAMESPACE
    typedef union {
        JNIEnv *nativeEnvironment;
        void *venv;
    } UnionJNIEnvToVoid;

    UnionJNIEnvToVoid uenv;
    uenv.venv = Q_NULLPTR;

    if (vm->GetEnv(&uenv.venv, JNI_VERSION_1_4) != JNI_OK) {
        __android_log_print(ANDROID_LOG_FATAL, "Qt", "GetEnv failed");
        return -1;
    }

    JNIEnv *env = uenv.nativeEnvironment;
    if (!registerNatives(env)) {
        __android_log_print(ANDROID_LOG_FATAL, "Qt", "registerNatives failed");
        return -1;
    }

    return JNI_VERSION_1_4;
}

