//
//  DisplayData.c
//  WordClock
//
//  Created by Tomas Friml on 29/06/16.
//  Copyright © 2016 Tomas Friml. All rights reserved.
//

#include "DisplayData.h"

#define SIZE(x) strlen(x)

const char* wcIt = "IT";
const char* wcIs = "IS";
const char* wcPast = "PAST";
const char* wcTo = "TO";
const char* wcAm = "AM";
const char* wcPm = "PM";

const char* wcHour = "HOUR";
const char* wcHours = "HOURS";
const char* wcMinute = "MINUTE";
const char* wcMinutes = "MINUTES";

const tNumber numbers[] = {
                    /* 0 */  { 1,  "ONE" },
                    /* 1 */  { 2,  "TWO" },
                    /* 2 */  { 3,  "THREE" },
                    /* 3 */  { 4,  "FOUR" },
                    /* 4 */  { 5,  "FIVE" },
                    /* 5 */  { 6,  "SIX" },
                    /* 6 */  { 7,  "SEVEN" },
                    /* 7 */  { 8,  "EIGHT" },
                    /* 8 */  { 9,  "NINE" },
                    /* 9 */  { 10, "TEN" },
                    /* 10 */ { 11, "ELEVEN" },
                    /* 11 */ { 12, "TWELVE" },
                    /* 12 */ { 13, "THIRTEEN" },
                    /* 13 */ { 14, "FOURTEEN" },
                    /* 14 */ { 15, "FIFTEEN" },
                    /* 15 */ { 16, "SIXTEEN" },
                    /* 16 */ { 17, "SEVENTEEN" },
                    /* 17 */ { 18, "EIGHTEEN" },
                    /* 18 */ { 19, "NINETEEN" },
                    /* 19 */ { 20, "TWENTY" },
                    /* 20 */ { 30, "THIRTY" },
                    /* 21 */ { 40, "FOURTY" },
                    /* 22 */ { 50, "FIFTY" },
};

const tCoordinate* hours[] = {
    /*  0 */ &coHrTwelve,
    /*  1 */ &coHrOne,
    /*  2 */ &coHrTwo,
    /*  3 */ &coHrThree,
    /*  4 */ &coHrFour,
    /*  5 */ &coHrFive,
    /*  6 */ &coHrSix,
    /*  7 */ &coHrSeven,
    /*  8 */ &coHrEight,
    /*  9 */ &coHrNine,
    /* 10 */ &coHrTen,
    /* 11 */ &coHrEleven,
    /* 12 */ &coHrTwelve,
    /* 13 */ &coHrOne,
    /* 14 */ &coHrTwo,
    /* 15 */ &coHrThree,
    /* 16 */ &coHrFour,
    /* 17 */ &coHrFive,
    /* 18 */ &coHrSix,
    /* 19 */ &coHrSeven,
    /* 20 */ &coHrEight,
    /* 21 */ &coHrNine,
    /* 22 */ &coHrTen,
    /* 23 */ &coHrEleven,
};           

const tNumber numberWords[] = {
                    /* 0 */ { 15, "QUARTER" },
                    /* 1 */ { 30, "HALF" },
};

const char* days[] = {
    /* 0 */ "MON",
    /* 1 */ "TUE",
    /* 2 */ "WED",
    /* 3 */ "THU",
    /* 4 */ "FRI",
    /* 5 */ "SAT",
    /* 6 */ "SUN",
};

const tCoordinate coSec = { 2, 0, SIZE("."), "." };

const tCoordinate coIt = {  0,  0, SIZE(wcIt), wcIt };
const tCoordinate coIs = {  3,  0, SIZE(wcIs), wcIs };
const tCoordinate coAm = {  6,  5, SIZE(wcAm), wcAm };
const tCoordinate coPm = {  8,  5, SIZE(wcPm), wcPm };
const tCoordinate coTo = {  3,  2, SIZE(wcTo), wcTo };
const tCoordinate coPast = {  0,  2, SIZE(wcPast), wcPast };

// minutes
const tCoordinate coMinFive = {  3,  1, SIZE(numbers[4].word), numbers[4].word };
const tCoordinate coMinTen = {  0,  1, SIZE(numbers[9].word), numbers[9].word };
const tCoordinate coMinTwenty = {  6,  0, SIZE(numbers[19].word), numbers[19].word };
const tCoordinate coMinHalf = {  12,  0, SIZE(numberWords[1].word), numberWords[1].word };
const tCoordinate coMinQuarter = {  7,  1, SIZE(numberWords[0].word), numberWords[0].word };

// hours
const tCoordinate coHrOne = {  10,  4, SIZE(numbers[0].word), numbers[0].word };
const tCoordinate coHrTwo = {  8,  4, SIZE(numbers[1].word), numbers[1].word };
const tCoordinate coHrThree = {  0,  4, SIZE(numbers[2].word), numbers[2].word };
const tCoordinate coHrFour = {  6,  2, SIZE(numbers[3].word), numbers[3].word };
const tCoordinate coHrFive = {  10,  2, SIZE(numbers[4].word), numbers[4].word };
const tCoordinate coHrSix = {  13,  4, SIZE(numbers[5].word), numbers[5].word };
const tCoordinate coHrSeven = {  3,  3, SIZE(numbers[6].word), numbers[6].word };
const tCoordinate coHrEight = {  4,  4, SIZE(numbers[7].word), numbers[7].word };
const tCoordinate coHrNine = {  7,  3, SIZE(numbers[8].word), numbers[8].word };
const tCoordinate coHrTen = {  0,  3, SIZE(numbers[9].word), numbers[9].word };
const tCoordinate coHrEleven = {  10,  3, SIZE(numbers[10].word), numbers[10].word };
const tCoordinate coHrTwelve = {  0,  5, SIZE(numbers[11].word), numbers[11].word };

// days
const tCoordinate coMon = {  10,  5, SIZE(days[0]), days[0] };
const tCoordinate coTue = {  13,  5, SIZE(days[1]), days[1] };
const tCoordinate coWed = {  0,  6, SIZE(days[2]), days[2] };
const tCoordinate coThu = {  3,  6, SIZE(days[3]), days[3] };
const tCoordinate coFri = {  6,  6, SIZE(days[4]), days[4] };
const tCoordinate coSat = {  9,  6, SIZE(days[5]), days[5] };
const tCoordinate coSun = {  12,  6, SIZE(days[6]), days[6] };

// other
const tCoordinate coWifi = { 5, 2, SIZE("."), "." };
