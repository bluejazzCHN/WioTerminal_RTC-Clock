#include <TFT_eSPI.h>
#include <time.h>
#include "Clock.h"
#include "NtpServer.h"


TFT_eSPI tft = TFT_eSPI();

Clock clk = Clock(&tft);
NtpServer ntp = NtpServer("********","******");

void setup()
{
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);
    clk.setHead();
    clk.setClock();
    Serial.begin(115200);
    delay(10000);
    clk.updateRTCNtp(ntp.getNTPtime());
}

void loop()
{
    delay(1000);
    clk.updateTFT();
    if (Serial.available())
    {
        char input = Serial.read();
        if (input == 'u')
            clk.updateRTC(); // update RTC time
    }
}
