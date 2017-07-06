//
// WordClock
//
// Description of the project
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		Tomas Friml
// 				Tomas Friml
//
// Date			11/05/16 8:11 PM
// Version		<#version#>
//
// Copyright	© Tomas Friml, 2016
// Licence		<#licence#>
//
// See         ReadMe.txt for references
//

#include "WordClock_Utils.h"
#include "NTP_Utils.h"
#include "TimeLib.h"

#define BTN1_PIN 5
#define BTN2_PIN 4

time_t minuteTimer = 0;
time_t hourTimer = 0;
time_t secondTimer = 0;

// Prototypes
bool timerExpired(time_t timer, time_t timeout, time_t curTime);
void handleBtn1();
void handleBtn2();
/*
void rainbow(byte startPosition);
void singleRainbow(byte position);
uint32_t rainbowOrder(byte position);
 */

byte numWifiAttempts = 10;

// Add setup code
void setup()
{
    Serial.begin(115200);
    
    pinMode(BTN1_PIN, INPUT);
    pinMode(BTN2_PIN, INPUT);
    
    initClock();
    initWifi();
    
    for (int i = 0; i < numWifiAttempts; ++i) {
        if (isWifiConnected() == false) {
            // wait a bit 
            delay(2000);
        } else {
            Serial.println("WiFi connected");
            // have valid WiFi connection, break
            break;
        }
    }
    
    if (isWifiConnected()) {
        initUdp();
        
        syncTime();
    }
}

// Add loop code
void loop()
{
    int btn1State = digitalRead(BTN1_PIN);
    int btn2State = digitalRead(BTN2_PIN);
    
    /*
    if (btn1State == HIGH) {
        Serial.println("BTN1 pressed");
        handleBtn1();
    }
    
    if (btn2State == HIGH) {
        Serial.println("BTN2 pressed");
        handleBtn2();
    }
     */
    
    time_t curTime = now();
    
    // toggle led once a second
    if (timerExpired(secondTimer, 1, curTime)) {
        Serial.println("ONE SEC");
        toggleOneSecLed();
        secondTimer = curTime;
    
        // update time every minute
        if (timerExpired(minuteTimer, 60, curTime)) {
            Serial.println("ONE MIN");
            showTime();
            minuteTimer = curTime;
            
            // update day every hour
            if (timerExpired(hourTimer, 60*60, curTime)) {
                Serial.println("ONE HOUR");
                showDayOfWeek();
                hourTimer = curTime;
            }
        }
    }
    updateStrip();
    
    delay(10);
}

// PRIVATE
bool timerExpired(time_t timer, time_t timeout, time_t now) {
    return (timer + timeout) < now;
}

void handleBtn1() {
    // cycle through weather?
    
}

void handleBtn2() {
    
}

/*
// Prints a rainbow on the ENTIRE LED strip.
//  The rainbow begins at a specified position.
// ROY G BIV!
void rainbow(byte startPosition)
{
    // Need to scale our rainbow. We want a variety of colors, even if there
    // are just 10 or so pixels.
    int rainbowScale = 192 / WC_NUM_LEDS;
    
    // Next we setup each pixel with the right color
    for (int i=0; i<WC_NUM_LEDS; i++)
    {
        // There are 192 total colors we can get out of the rainbowOrder function.
        // It'll return a color between red->orange->green->...->violet for 0-191.
        leds.setPixelColor(i, rainbowOrder((rainbowScale * (i + startPosition)) % 192));
    }
    // Finally, actually turn the LEDs on:
    leds.show();
}

void singleRainbow(byte position)
{
    // Need to scale our rainbow. We want a variety of colors, even if there
    // are just 10 or so pixels.
    int rainbowScale = 192 / WC_NUM_LEDS;
    
    // Next we setup each pixel with the right color
    for (int i=0; i<WC_NUM_LEDS; i++)
    {
        // There are 192 total colors we can get out of the rainbowOrder function.
        // It'll return a color between red->orange->green->...->violet for 0-191.
        if (i == position) {
            leds.setPixelColor(i, rainbowOrder((rainbowScale * (position)) % 192));
            leds.setPixelColor(i/2, rainbowOrder((rainbowScale * (position/2)) % 192));
        } else {
            clearLED(i);
        }
    }
    // Finally, actually turn the LEDs on:
    leds.show();
}



// Input a value 0 to 191 to get a color value.
// The colors are a transition red->yellow->green->aqua->blue->fuchsia->red...
//  Adapted from Wheel function in the Adafruit_NeoPixel library example sketch
uint32_t rainbowOrder(byte position)
{
    // 6 total zones of color change:
    if (position < 31)  // Red -> Yellow (Red = FF, blue = 0, green goes 00-FF)
    {
        return leds.Color(0xFF, position * 8, 0);
    }
    else if (position < 63)  // Yellow -> Green (Green = FF, blue = 0, red goes FF->00)
    {
        position -= 31;
        return leds.Color(0xFF - position * 8, 0xFF, 0);
    }
    else if (position < 95)  // Green->Aqua (Green = FF, red = 0, blue goes 00->FF)
    {
        position -= 63;
        return leds.Color(0, 0xFF, position * 8);
    }
    else if (position < 127)  // Aqua->Blue (Blue = FF, red = 0, green goes FF->00)
    {
        position -= 95;
        return leds.Color(0, 0xFF - position * 8, 0xFF);
    }
    else if (position < 159)  // Blue->Fuchsia (Blue = FF, green = 0, red goes 00->FF)
    {
        position -= 127;
        return leds.Color(position * 8, 0, 0xFF);
    }
    else  //160 <position< 191   Fuchsia->Red (Red = FF, green = 0, blue goes FF->00)
    {
        position -= 159;
        return leds.Color(0xFF, 0x00, 0xFF - position * 8);
    }
}
*/
