#if OS_USE_NETWORK

#ifndef __NETWORK_H__
#define __NETWORK_H__

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

///////////////////////////////////////////////////////////////////////////////////////////////////
// Operating Support:
// Class to manage access to the wireless local area network (WiFi).
// This is a no-op if not run on ESP8266.
//
// On connect tries to connect to a previously saved Access Point or opens an own Access Point and
// serves a web configuration portal.
// Uses https://github.com/tzapu/WiFiManager
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ESP8266
#include <WiFiManager.h>
#endif

class Network {
public:
    Network();
    Network(String deviceid);
    Network(String deviceid, String ssid, String sspw);

    // Begin managing the WiFi network. Must be called before any other method.
    bool begin(bool production);

    // Timeout for a connection attempt. Must be set before connect is called.
    uint16_t connectTimeout = 60;

    // Connects to the WiFi network.
    bool connect();

    // Disconnects from the WiFi network.
    void disconnect(void);

    String deviceid;

    #ifdef ESP8266
    // Returns a new WiFi client. Only available on ESP8266.
    std::unique_ptr<Client> createClient(void);
    #endif

private:
    bool production;

    String ssid;
    String sspw;

    bool connect(String ssid, String sspw);
    bool connect(String deviceid);
};

#endif

#endif
