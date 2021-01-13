#include <TFT_eSPI.h>
#include <time.h>
#ifndef _Clock_H_
#define _Clock_H_
#endif
#include "Clock.h"
TFT_eSPI tft = TFT_eSPI();

Clock clk = Clock(&tft);

void setup()
{
    tft.init();
    tft.fillScreen(TFT_BLACK);
    tft.setRotation(1);
    clk.setHead();
    clk.setClock();
    Serial.begin(115200);
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