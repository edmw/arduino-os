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

#ifdef ESP8266
#include <WiFiManager.h>
#include <Ticker.h>
#endif

#include "Network.h"

#include "OS.h"
extern OS os;

///////////////////////////////////////////////////////////////////////////////////////////////////

Network::Network(void) {
}

bool Network::begin(bool prodction) {
    this->production = production;
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
    ticker.attach_ms(500, []() {
        os.signaling.toggle();
    });
    wm->setConfigPortalTimeout(300);
    wm->setAPCallback(startConfigCallback);
    wm->setSaveConfigCallback(saveConfigCallback);
}

void finishNetworkForWiFi(WiFiManager *wm, Network *network) {
    ticker.detach();
    os.signaling.off();
}

bool Network::connect(bool reset) {
    WiFi.forceSleepWake();

    if (reset) {
        WiFi.persistent(true);
        WiFi.disconnect(true);
    }
    WiFi.persistent(true);

    WiFiManager wiFiManager;
    if (production) {
        // Production: disable debug output
        wiFiManager.setDebugOutput(false);
    }
    else {
        // Development: print debug output
        wiFiManager.setDebugOutput(true);
    }
    wiFiManager.setConnectTimeout(connectTimeout);

    bool result = false;
    prepareNetworkForWiFi(&wiFiManager, this);
    result = wiFiManager.autoConnect();
    finishNetworkForWiFi(&wiFiManager, this);
    return result;
}

void Network::disconnect(void) {
    WiFi.forceSleepBegin();
}

std::unique_ptr<Client> Network::createClient(void) {
    return std::unique_ptr<Client>(new WiFiClient());
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#else
///////////////////////////////////////////////////////////////////////////////////////////////////

bool Network::connect(bool reset) {
    return false;
}

void Network::disconnect(void) {
}

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////
