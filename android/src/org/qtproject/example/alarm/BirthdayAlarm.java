package org.qtproject.example.alarm;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.SystemClock;
import android.util.Log;

import java.util.Calendar;

import org.qtproject.qt5.android.bindings.*;

public class BirthdayAlarm extends QtActivity {
    private AlarmManager m_alarmManager     = null;
    private Intent m_intent                 = null;
    private PendingIntent m_pendingIntent   = null;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        m_intent = new Intent(this, CheckBirthdayService.class);
        m_pendingIntent = PendingIntent.getService(this, 0, m_intent, 0);

        m_alarmManager = (AlarmManager) getSystemService(Context.ALARM_SERVICE);
        m_alarmManager.setInexactRepeating(AlarmManager.ELAPSED_REALTIME_WAKEUP,
                                           SystemClock.elapsedRealtime() + 60000,
                                           60000,
                                           m_pendingIntent);
    }

}

