//
//  NTP_Utils.c
//  WordClock
//
//  Created by Tomas Friml on 07/12/16.
//  Copyright © 2016 Tomas Friml. All rights reserved.
//

// NTP
#include "NTP_Utils.h"

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Time.h>
#include <Timezone.h>

// Forward declarations
unsigned long sendNTPpacket(IPAddress& address);

// WiFi settings
const char ssid[] = "YOUR SSID";
const char pass[] = "YOUR PASSWORD";

const char ntpServerName[] = "pool.ntp.org";

unsigned int localPort = 2390;      // local port to listen for UDP packets
WifiStatus status = ws_disconnected;


TimeChangeRule nzDT = {"NZDT", Last, Sun, Sep, 2, 780};  //NZDT - +13 hours
TimeChangeRule nzST = {"NZST", First, Sun, Apr, 2, 720}; //NZST - +12 hours
Timezone nzt(nzDT, nzST);

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
WiFiUDP udp; // A UDP instance to let us send and receive packets over UDP

void initWifi()
{
    status = ws_connected;
    WiFi.begin(ssid, pass);
}

void initUdp() {
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
}

bool isWifiConnected() {
    WiFi.printDiag(Serial);
    return WiFi.status() == WL_CONNECTED;
}

WifiStatus wifiStatus() {
    switch (WiFi.status()) {
        case WL_CONNECTED: return ws_connected;
        case WL_NO_SSID_AVAIL: return ws_failed;
        case WL_SCAN_COMPLETED: return ws_connecting;
        case WL_CONNECT_FAILED: return ws_failed;
        case WL_CONNECTION_LOST: return ws_failed;
        default: return ws_disconnected;
    }
}


void syncTime() {
    if (isWifiConnected()) {
        //get a random server from the pool
        IPAddress timeServerIP; // time.nist.gov NTP server address
        WiFi.hostByName(ntpServerName, timeServerIP);

        Serial.print("IP: - ");
        Serial.println(timeServerIP.toString());
        sendNTPpacket(timeServerIP); // send an NTP packet to a time server
        // wait to see if a reply is available
        delay(2000);
  
        int cb = udp.parsePacket();
        if (!cb) {
            Serial.println("no packet yet");
        }
        else {
            Serial.print("packet received, length=");
            Serial.println(cb);

            // We've received a packet, read the data from it
            udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
            
            //the timestamp starts at byte 40 of the received packet and is four bytes,
            // or two words, long. First, esxtract the two words:
            
            unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
            unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
            // combine the four bytes (two words) into a long integer
            // this is NTP time (seconds since Jan 1 1900):
            unsigned long secsSince1900 = highWord << 16 | lowWord;
            Serial.print("Seconds since Jan 1 1900 = " );
            Serial.println(secsSince1900);
            
            // now convert NTP time into everyday time:
            Serial.print("Unix time = ");
            // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
            const unsigned long seventyYears = 2208988800UL;
            // subtract seventy years:
            unsigned long epoch = secsSince1900 - seventyYears;
            // print Unix time:
            Serial.println(epoch);
            
            
            // print the hour, minute and second:
            Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
            Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
            Serial.print(':');
            if ( ((epoch % 3600) / 60) < 10 ) {
                // In the first 10 minutes of each hour, we'll want a leading '0'
                Serial.print('0');
            }
            Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
            Serial.print(':');
            if ( (epoch % 60) < 10 ) {
                // In the first 10 seconds of each minute, we'll want a leading '0'
                Serial.print('0');
            }
            Serial.println(epoch % 60); // print the second
            
            TimeChangeRule *tcr;
            time_t localEpoch = nzt.toLocal(epoch, &tcr);
            Serial.print("The time zone is: ");
            Serial.println(tcr -> abbrev);
            
            // set time
            setTime(localEpoch);
            time_t time = now();
            Serial.print("Local time is ");
            Serial.print(day(time));
            Serial.print('/');
            Serial.print(month(time));
            Serial.print('/');
            Serial.print(year(time));
            Serial.print(' ');
            Serial.print(hour(time));
            Serial.print(':');
            Serial.println(minute(time));
            
        }
        // wait ten seconds before asking for the time again
        delay(10000);
    }
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
    //Serial.println("sending NTP packet...");
    // set all bytes in the buffer to 0
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    packetBuffer[0] = 0b11100011;   // LI, Version, Mode
    packetBuffer[1] = 0;     // Stratum, or type of clock
    packetBuffer[2] = 6;     // Polling Interval
    packetBuffer[3] = 0xEC;  // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12]  = 49;
    packetBuffer[13]  = 0x4E;
    packetBuffer[14]  = 49;
    packetBuffer[15]  = 52;
    
    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    udp.beginPacket(address, 123); //NTP requests are to port 123
    udp.write(packetBuffer, NTP_PACKET_SIZE);
    udp.endPacket();
}
