///////////////////////////////////////////////////////////////////////////////////////////////////
// Operating Support code for Arduino or ESP8266 projects.
//
// Copyright (c) 2017/2018 Michael Baumgärtner
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>

#include "Network.h"

#include "OS.h"
extern OS os;

#define REALM F("NETWORK")

#if OS_USE_NETWORK

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

Network::Network() : ssid(""), sspw("") {
    #ifdef ESP8266
    deviceid = "ESP" + String(ESP.getChipId());
    #else
    deviceid = "Arduino" + String(random(1000, 10000));
    #endif
}

Network::Network(String deviceid)
    : deviceid(deviceid), ssid(""), sspw("") {
}

Network::Network(String deviceid, String ssid, String sspw)
    : deviceid(deviceid), ssid(ssid), sspw(sspw) {
}

bool Network::begin(bool prodction) {
    this->production = production;
    #ifdef ESP8266
    WiFi.hostname(deviceid.c_str());
    os.notification.info(REALM, F("*WIFI: device id:"), deviceid);
    #endif
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ESP8266

Ticker ticker;

Network *networkToConfig;

bool configChanged;

void startConfigCallback(WiFiManager *wm) {
    ticker.attach_ms(1000, []() {
        os.signaling.toggle();
    });
}

void saveConfigCallback() {
    configChanged = true;
    ticker.attach_ms(100, []() {
        os.signaling.toggle();
    });
}

void prepareNetworkForWiFi(WiFiManager *wm, Network *network) {
    networkToConfig = network;
    configChanged = false;
    ticker.attach_ms(100, []() {
        os.signaling.toggle();
    });
    wm->setConfigPortalTimeout(300);
    wm->setAPCallback(startConfigCallback);
}

void finishNetworkForWiFi(WiFiManager *wm, Network *network) {
    ticker.detach();
    os.signaling.off();
}

bool Network::connect() {
    System::wifiOn();

    if (connect(ssid, sspw)) {
        return true;
    }

    if (connect(deviceid)) {
        return true;
    }

    return false;
}

bool Network::connect(String ssid, String password) {
    if ((ssid.length() == 0) || (sspw.length() == 0)) { return false; }

    WiFi.begin(ssid.c_str(), password.c_str());
    int status = WiFi.waitForConnectResult();
    if (status != WL_CONNECTED) {
        os.notification.info(REALM, F("*WIFI: status:"), status);
    }
    return status == WL_CONNECTED;
}

bool Network::connect(String deviceid) {
    if (deviceid.length() == 0) { return false; }

    WiFiManager wiFiManager;
    if (production) {
        // Production: disable debug output
        wiFiManager.setDebugOutput(false);
    }
    else {
        // Development: print debug output
        os.notification.info(REALM, F("*WIFI: SSID:"), WiFi.SSID());
        os.notification.info(REALM, F("*WIFI: PASS:"), WiFi.psk());
        wiFiManager.setDebugOutput(true);
    }
    wiFiManager.setConnectTimeout(1*60);
    wiFiManager.setConfigPortalTimeout(5*60);

    bool result = false;

    prepareNetworkForWiFi(&wiFiManager, this);

    if (wiFiManager.autoConnect(deviceid.c_str(), NULL)) {
        result = true;
    }

    finishNetworkForWiFi(&wiFiManager, this);

    return result;
}

void Network::disconnect(void) {
    WiFi.disconnect();
}

std::unique_ptr<Client> Network::createClient(void) {
    return std::unique_ptr<Client>(new WiFiClient());
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#else
///////////////////////////////////////////////////////////////////////////////////////////////////

bool Network::connect(void) {
    return false;
}

bool connect(String ssid, String sspw) {
    return false;
}

bool connect(String deviceid) {
    return false;
}

void Network::disconnect(void) {
}

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
