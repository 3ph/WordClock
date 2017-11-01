//
//  NTP_Utils.h
//  WordClock
//
//  Created by Tomas Friml on 07/12/16.
//  Copyright © 2016 Tomas Friml. All rights reserved.
//

#ifndef NTP_Utils_h
#define NTP_Utils_h

typedef enum {
    ws_disconnected,
    ws_connecting,
    ws_failed,
    ws_connected,
} WifiStatus;


void initWifi();
void initUdp();
bool isWifiConnected();
WifiStatus wifiStatus();

void syncTime();

#endif /* NTP_Utils_h */
