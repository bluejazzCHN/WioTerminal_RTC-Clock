#include "TFT_eSPI.h"
#include "RTC_SAMD51.h"
#include "DateTime.h"

class Clock
{
private:
    const char dayInWords[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    const char monthInWords[13][4] = {" ", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                                      "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    TFT_eSPI *_tft;
    TFT_eSprite _sprHead = TFT_eSprite(_tft);
    TFT_eSprite _sprClock = TFT_eSprite(_tft);
    RTC_SAMD51 rtc;

public:
    Clock(TFT_eSPI *tft);
    void setHead();
    void setClock();
    void updateRTC();
    void updateTFT();
};