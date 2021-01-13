#include "Clock.h"

Clock::Clock(TFT_eSPI *tft)
{
    _tft = tft;
    rtc.begin();
}

void Clock::setHead()
{
    _sprHead.setColorDepth(1);
    _sprHead.createSprite(320, 50);
    _sprHead.fillSprite(TFT_BLACK);
    _sprHead.setTextColor(TFT_WHITE);
    _sprHead.setTextDatum(CC_DATUM);
    _sprHead.drawString("RTC Clock", 160, 25, 4);
    _sprHead.pushSprite(0, 0);
}
void Clock::setClock()
{
    _sprClock.setColorDepth(1);
    _sprClock.createSprite(320, 190);
    _sprClock.fillSprite(TFT_WHITE);
    _sprClock.setTextColor(TFT_BLACK);
    _sprClock.setTextDatum(CC_DATUM);
    _sprClock.drawString("Digital Clock By Bluejazz", 160, 80, 2);
    _sprClock.pushSprite(0, 50);
    delay(5000);
}

void Clock::updateRTC()
{
    // ask user to enter new date and time
    const char txt[6][15] = {"year [4-digit]", "month [1~12]", "day [1~31]",
                             "hours [0~23]", "minutes [0~59]", "seconds [0~59]"};
    String str = "";
    long newDate[6];

    while (Serial.available())
    {
        Serial.read(); // clear serial buffer
    }

    for (int i = 0; i < 6; i++)
    {

        Serial.print("Enter ");
        Serial.print(txt[i]);
        Serial.print(": ");

        while (!Serial.available())
        {
            ; // wait for user input
        }

        str = Serial.readString(); // read user input
        newDate[i] = str.toInt();  // convert user input to number and save to array

        Serial.println(newDate[i]); // show user input
    }

    // update RTC
    rtc.adjust(DateTime(newDate[0], newDate[1], newDate[2], newDate[3], newDate[4], newDate[5]));
    Serial.println("RTC Updated!");
}

void Clock::updateTFT()
{
    DateTime now = rtc.now();
    int ss = now.second();
    int mm = now.minute();
    int hh = now.hour();
    int DD = now.dayOfTheWeek();
    int dd = now.day();
    int MM = now.month();
    int yyyy = now.year();

    _sprClock.fillSprite(TFT_WHITE);
    char clock_ss[4];
    if (ss < 10)
    {
        sprintf(clock_ss, "%s%d", "0", ss);
    }
    else
    {
        sprintf(clock_ss, "%2d", ss);
    }
    char clock_mm[4];
    if (mm < 10)
    {
        sprintf(clock_mm, "%s%d", "0", mm);
    }
    else
    {
        sprintf(clock_mm, "%2d", mm);
    }
    char clock_yy[4];
    sprintf(clock_yy,"%4d",yyyy);

    char clockTime[12];
    sprintf(clockTime, "%2d-%2s-%2s", hh, clock_mm, clock_ss);
    _sprClock.drawString(clockTime, 160, 120, 6);

    char clock_dd[4];
    if (dd < 10)
    {
        sprintf(clock_dd, "%s%d", "0", dd);
    }
    else
    {
        sprintf(clock_dd, "%2d", dd);
    }

    char clockDate[14];

    sprintf(clockDate,"%4d-%4s-%2s %4s",yyyy,monthInWords[MM],clock_dd,dayInWords[DD]);
    _sprClock.drawString(clockDate, 160, 60, 4);

    _sprClock.pushSprite(0, 50);
}