//
// File			display_data.h
// Header
//
// Details		<#details#>
//
// Project		 WordClock
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author		Tomas Friml
// 				Tomas Friml
//
// Date			25/05/16 9:30 PM
// Version		<#version#>
//
// Copyright	© Tomas Friml, 2016
// Licence    license
//
// See			ReadMe.txt for references
//

/*
    Various time formats:
    1) 12/24 hr time - IT IS TWO THIRTY (AM/PM)
    2) wordy time - IT IS THIRTY PAST TWO
    3) wordy time with quarter - IT IS HALF PAST TWO
 
    Sort:
    1) numbers 1..12/0..23 + (hour(s)) + 0..59 + (minute(s))
    2) 0..59 + TO + PAST + 1..12 + AM/PM (MORNING/AFTERNOON)
    3) 0..59 + QUARTER + HALF + TO + PAST + 1..12 + AM/PM (MORNING/AFTERNOON)
 
    Overall sort:
    IT + IS + 0..23 + HOUR + HOURS + 20..50 + 0..9 + 10..19 + MINUTE + MINUTES
 
    Additional data:
    - b'day/nameday
    - other days
    - temperature F-0-5-10-15-20-25-30-HOT
    - weather 
    - moon phases
 */

#ifndef display_data_h
#define display_data_h

#include <Arduino.h>

#define SIZE(x) (sizeof(x)-1)

// TODO: use ROWS*COLS
#define WC_NUM_ROWS 8
#define WC_NUM_COLS 16
#define WC_START_TIME_LED 6
#define WC_END_TIME_LED WC_NUM_COLS*5 + 10

#define WC_NUM_LEDS WC_NUM_ROWS*WC_NUM_COLS

typedef struct {
    int numeric;
    char* word;
    
} tNumber;

typedef struct {
    byte x;
    byte y;
    byte length;
    const char* word;
} tCoordinate;

extern const char* wcIt;
extern const char* wcIs;
extern const char* wcPast;
extern const char* wcTo;
extern const char* wcAm;
extern const char* wcPm;

extern const char* wcHour;
extern const char* wcHours;
extern const char* wcMinute;
extern const char* wcMinutes;

extern const tNumber numbers[];
extern const tNumber numberWords[];
extern const tCoordinate* hours[];

extern const tCoordinate coSec;
extern const tCoordinate coIt;
extern const tCoordinate coIs;
extern const tCoordinate coAm;
extern const tCoordinate coPm;
extern const tCoordinate coTo;
extern const tCoordinate coPast;

// minutes
extern const tCoordinate coMinFive;
extern const tCoordinate coMinTen;
extern const tCoordinate coMinTwenty;
extern const tCoordinate coMinHalf;
extern const tCoordinate coMinQuarter;

// hours
extern const tCoordinate coHrOne;
extern const tCoordinate coHrTwo;
extern const tCoordinate coHrThree;
extern const tCoordinate coHrFour;
extern const tCoordinate coHrFive;
extern const tCoordinate coHrSix;
extern const tCoordinate coHrSeven;
extern const tCoordinate coHrEight;
extern const tCoordinate coHrNine;
extern const tCoordinate coHrTen;
extern const tCoordinate coHrEleven;
extern const tCoordinate coHrTwelve;

// days
extern const tCoordinate coMon;
extern const tCoordinate coTue;
extern const tCoordinate coWed;
extern const tCoordinate coThu;
extern const tCoordinate coFri;
extern const tCoordinate coSat;
extern const tCoordinate coSun;

// other
extern const tCoordinate coWifi;

#endif
