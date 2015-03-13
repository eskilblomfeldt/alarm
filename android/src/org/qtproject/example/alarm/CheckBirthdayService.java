package org.qtproject.example.alarm;

import org.qtproject.qt5.android.bindings.*;

import android.content.Intent;
import android.util.Log;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;

public class CheckBirthdayService extends QtService
{
    private NotificationManager m_notificationManager;

    public CheckBirthdayService()
    {
        super("Check Birthday Service");
    }

    @Override
    public void onCreate()
    {
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        int id = 0;
        for (String birthday = nextBirthday(); birthday.length() > 0; birthday = nextBirthday()) {
            if (m_notificationManager == null)
                m_notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

            Notification.Builder builder = new Notification.Builder(this);
            builder.setSmallIcon(R.drawable.icon);
            builder.setContentTitle("Birthday reminder!");
            builder.setContentText("Remember that " + birthday + " has a birthday today!");
            m_notificationManager.notify(id++, builder.build());
            break;
        }

        return START_NOT_STICKY;
    }

    private static native String nextBirthday();
}

