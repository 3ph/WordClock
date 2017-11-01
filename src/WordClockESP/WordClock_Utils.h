//
//  WordClock_Utils.h
//  WordClock
//
//  Created by Tomas Friml on 29/06/16.
//  Copyright © 2016 Tomas Friml. All rights reserved.
//

#ifndef WordClock_Utils_h
#define WordClock_Utils_h

#include "DisplayData.h"
#include "NTP_Utils.h"

#include <Arduino.h>

void initClock();
void startUpSequence();

// update brightness
void setBrightness(byte brightness);
    
void updateStrip();

// show time
void showTime();
void showDayOfWeek();

void showConnection(WifiStatus status);

// led functions
void clearTime();
void clearScreen();
void setPixel(byte position, uint32_t color);
void clearPixel(byte position);

void wordFor(const tCoordinate* coordinate, bool isVisible, uint32_t color);
void toggleOneSecLed();

int coordinateToLedNum(const tCoordinate* coordinate);

#endif /* WorldClock_Utils_h */
