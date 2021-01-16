#include <TFT_eSPI.h>
#include <time.h>
#include "Clock.h"
#include "NtpServer.h"

TFT_eSPI tft = TFT_eSPI();

Clock clk = Clock(&tft);
NtpServer ntp = NtpServer("ZSJ_HOME_robin", "QQqq11!!");

//defined Clock timer interrupt callback
void  rtc_cb(uint32_t flag)
{
    //question: if calling clk.fillsprite, routine will crash
    clk._alarmStatus = false;
    clk.detAlarm();
    Serial.println("RTC interrupt fired.");
}

void setup()
{
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);
    clk.drawClock();
    Serial.begin(115200);
    delay(10000);
    clk.updateRTCNtp(ntp.getNTPtime()); //auto update rtc time from NTP
    pinMode(WIO_KEY_A, INPUT);
    pinMode(WIO_KEY_B, INPUT);
}

void loop()
{
    int buttonStateA = digitalRead(WIO_KEY_A);
    if (buttonStateA == false && clk._alarmStatus == false)
    {
        clk.drawAlarm();
        clk.setAlarm(10, rtc_cb);
        Serial.println("RTC interrupt setted.");
    }
    
    if(clk._alarmStatus== false){
        clk.unDrawAlarm();
    }
    int buttonStateB = digitalRead(WIO_KEY_B);
    if(buttonStateB == false)
    {
        clk._alarmStatus = false;
    }
    delay(1000);
    clk.updateTFT();
    if (Serial.available())
    {
        char input = Serial.read();
        if (input == 'u')
            clk.updateRTC(); // update rtc time from Serial
    }
}
