#include "TFT_eSPI.h"
#include "RTC_SAMD51.h"
#include "Alert.h"

class Clock
{
private:
    TFT_eSPI *_tft;
    TFT_eSprite _sprHead = TFT_eSprite(_tft);
    TFT_eSprite _sprClock = TFT_eSprite(_tft);
    TFT_eSprite _sprStatus = TFT_eSprite(_tft);
    RTC_SAMD51 _rtc;
    void setHead();
    void setClock();
    void setStatus();
public:
    Clock(TFT_eSPI *tft);
    bool _alarmStatus = false;

    void drawClock();
    void updateRTC();
    void updateRTCNtp(unsigned long dt);
    void updateTFT();
    void drawAlarm();
    void unDrawAlarm();
    void setAlarm(unsigned long seconds,rtcCallBack cb);
    void disAlarm();
    void detAlarm();
};

