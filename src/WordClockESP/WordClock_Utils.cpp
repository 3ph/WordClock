//
//  WordClock_Utils.c
//  WordClock
//
//  Created by Tomas Friml on 29/06/16.
//  Copyright © 2016 Tomas Friml. All rights reserved.
//

#include "WordClock_Utils.h"
#include "Adafruit_NeoPixel.h"

#include "DisplayData.h"
//#include "Color.h"

#include "WS2812_Definitions.h"

#include <stdio.h>
#include <TimeLib.h>

// Set parameters
#define WS2811_DATA_PIN D5

#define DBG_PRINT 1

// Define variables and constants
Adafruit_NeoPixel strip = Adafruit_NeoPixel(WC_NUM_LEDS, WS2811_DATA_PIN, NEO_GRB + NEO_KHZ800);


void initClock()
{
    strip.begin();  // Call this to start up the LED strip.
    clearScreen();  // This function, defined below, turns all strip off...
    strip.show();   // ...but the strip don't actually update until you call this.
    
    startUpSequence();
    
    strip.setBrightness(50);
}

void updateStrip() {
    strip.show();
}

void setBrightness(byte brightness) {
    strip.setBrightness(brightness);
}

void startUpSequence() {
    for (int i = 0; i < WC_NUM_LEDS; ++i) {
        if (i > 0) {
            clearPixel(i-1);
        }
        setPixel(i, BLUE);
        delay(50);
        updateStrip();
    }
    clearPixel(WC_NUM_LEDS-1);
    updateStrip();
}

void showTime() {
    // clear current time
    clearTime();
    
    // show "it is"
    wordFor(&coIt, true, BROWN);
    wordFor(&coIs, true, BROWN);
    
    time_t t = now();
    bool to = false;
    
    // obtain minutes
    const tCoordinate* coPrefixStr = 0;
    const tCoordinate* coSuffixStr = 0;
    const tCoordinate* coHourStr = 0;
    const tCoordinate* coMinStr = 0;
    const tCoordinate* coMinPlusStr = 0;
    
    uint32_t minuteColor = DIMGRAY;
    uint32_t hourColor = BEIGE;
    uint32_t dayColor = ORANGE;
    
    // MINUTE
    int min = minute(t);
    if (min > 2 && min < 33) {
        coPrefixStr = &coPast;
        
        if (min < 7) {
            coMinStr = &coMinFive;
        } else if (min < 13) {
            coMinStr = &coMinTen;
        } else if (min < 18) {
            coMinStr = &coMinQuarter;
        } else if (min < 23) {
            coMinStr = &coMinTwenty;
        } else if (min < 28) {
            coMinStr = &coMinTwenty;
            coMinPlusStr = &coMinFive;
        } else {
            coMinStr = &coMinHalf;
        }
    } else {
        coPrefixStr = &coTo;
        to = true;
        
        if (min < 38) {
            coMinStr = &coMinTwenty;
            coMinPlusStr = &coMinFive;
        } else if (min < 43) {
            coMinStr = &coMinTwenty;
        } else if (min < 48) {
            coMinStr = &coMinQuarter;
        } else if (min < 53) {
            coMinStr = &coMinTen;
        } else if (min < 58) {
            coMinStr = &coMinFive;
        }
    } // else whole hour don't show minutes
    
    // HOUR
    int hr = to ? (hour(t)+1) % 24 : hour(t);
    coHourStr = hours[hr];
    
    // AM/PM
    coSuffixStr = isAM(t) ? &coAm : &coPm;
    
    // debug print
#if DBG_PRINT
    Serial.print(coMinStr->word);
    if (coMinPlusStr) {
        Serial.print(' ');
        Serial.print(coMinPlusStr->word);
    }
    Serial.print(' ');
    Serial.print(coPrefixStr->word);
    Serial.print(' ');
    Serial.print(coHourStr->word);
    Serial.print(' ');
    Serial.println(coSuffixStr->word);
#endif
    
    // show minutes
    wordFor(coMinStr, true, minuteColor);
    if (coMinPlusStr) {
        wordFor(coMinPlusStr, true, minuteColor);
    }
    wordFor(coPrefixStr, true, minuteColor);
    
    // show hours
    wordFor(coHourStr, true, hourColor);
    
    // show suffix
    wordFor(coSuffixStr, true, dayColor);
    
    updateStrip();
}

void showDayOfWeek() {
    
    time_t t = now();
    
    const tCoordinate* coDayStr = 0;
    int day = weekday(t);
    switch (day) {
        case 1 : coDayStr = &coSun;
            break;
        case 2 : coDayStr = &coMon;
            break;
        case 3 : coDayStr = &coTue;
            break;
        case 4 : coDayStr = &coWed;
            break;
        case 5 : coDayStr = &coThu;
            break;
        case 6 : coDayStr = &coFri;
            break;
        case 7 : coDayStr = &coSat;
            break;
    }
    
#if DBG_PRINT
    Serial.print("Day is ");
    Serial.println(coDayStr->word);
#endif
    
    wordFor(coDayStr, true, GREEN);
    
}

void showConnection(WifiStatus status) {
    int ledNum = coordinateToLedNum(&coWifi);
    int color = BLUE;
    
    switch (status) {
        case ws_connecting: color = ORANGE;
            break;
        case ws_failed: color = RED;
            break;
        case ws_connected: color = GREEN;
            break;
        default: color = YELLOW;
    }
    
    setPixel(ledNum, color);
}

void wordFor(const tCoordinate* coordinate, bool isVisible, uint32_t color)
{
    // figure out which strip we should turn on
    // x * COLS + (y - 1) * COLS
    
    
    int startLED = coordinateToLedNum(coordinate);
    int endLED = startLED + coordinate->length - 1;
    
    Serial.println(coordinate->word);
    Serial.println(startLED,DEC);
    Serial.println(endLED,DEC);
    Serial.println(coordinate->length,DEC);
    
    for (int i = startLED; i <= endLED; ++i) {
        setPixel(i, (isVisible ? color : BLACK));
    }
}

void toggleOneSecLed() {
    static bool on = false;
    
    int ledNum = coordinateToLedNum(&coSec);
    Serial.println(ledNum,DEC);
    
    if (on) {
        clearPixel(ledNum);
    } else {
        setPixel(ledNum, YELLOW);
    }
    on = !on;
}

// MARK: Clearing functions
void clearTime() {
    for (int i=WC_START_TIME_LED; i<WC_END_TIME_LED; ++i) {
        clearPixel(i);
    }
}


// Sets all strip to off, but DOES NOT update the display;
// call strip.show() to actually turn them off after this.
void clearScreen()
{
    for (int i=0; i<WC_NUM_LEDS; i++)
    {
        clearPixel(i);
    }
}

void clearPixel(byte position) {
    strip.setPixelColor(position, 0);
}

void setPixel(byte position, uint32_t color) {
    strip.setPixelColor(position, color);
}

/*
 4  3  2  1  0
 5  6  7  8  9
 14 13 12 11 10
 
 even rows
 (rows + 1)*cols - (col+1) - (len-1) -> (rows + 1)*cols - col - len
 
 (0,2) -> (2+1)*5 - 0 - 3 = 12
 (2,2) -> (2+1)*5 - 2 - 3 = 10
 PAP -> len = 3
 
 */

int coordinateToLedNum(const tCoordinate* coordinate) {
    if (coordinate->y % 2 == 0) {
        // even rows are reversed
        return (coordinate->y + 1) * WC_NUM_COLS - coordinate->x - coordinate->length;
    } else {
        // odd rows are correct
        return coordinate->x + coordinate->y * WC_NUM_COLS;
    }
}
