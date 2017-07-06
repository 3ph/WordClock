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

#include <Arduino.h>

void initClock();
void startUpSequence();
void updateStrip();

// show time
void showTime();
void showDayOfWeek();


// led functions
void clearTime();
void clearScreen();
void setPixel(byte position);
void clearPixel(byte position);

void wordFor(const tCoordinate* coordinate, bool isVisible);
void toggleOneSecLed();

#endif /* WorldClock_Utils_h */
