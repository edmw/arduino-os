///////////////////////////////////////////////////////////////////////////////////////////////////
// Operating Support code for Arduino or ESP8266 projects.
//
// Copyright (c) 2017-2019 Michael Baumgärtner
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
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#endif

#include "OS.h"

#ifdef ESP8266
void ota_begin(void);
void ota_handle(void);
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

OS::OS(void) {
    this->error = F("ERROR");
}

bool OS::begin(bool production) {
    SERIAL_BEGIN();
    if (!production) {
        SERIAL_PRINTLN(F("OS::begin"));
        SERIAL_PRINTLN(System::lastException());
    }

    signaling.begin(production);
    notification.begin(production);

    #if OS_USE_FILES
    files.begin(production);
    #endif
    #if OS_USE_NETWORK
    network.begin(production);
    #endif

    #ifdef ESP8266
    #if OS_USE_OTA
    ota_begin();
    #endif
    #endif

    return true;
}

void OS::yield(void) {
    #ifdef ESP8266
    #if OS_USE_OTA
    ota_handle();
    #endif
    ESP.wdtFeed();
    #endif
    delay(1);
}

void OS::fatal(void) {
    while (true) {
        signaling.once(100, 900);
        yield();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ESP8266

void ota_begin(void) {
    static unsigned int ota_done = 0;

    ArduinoOTA.onStart([]() {
        os.notification.info(F("OS"), F("OTA start"));
        ota_done = 0;
    });

    ArduinoOTA.onEnd([]() {
        os.notification.info(F("OS"), F("OTA end"));
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        unsigned int done = (unsigned int)((progress / (total / 100)) / 5) * 5;
        if (done > ota_done) {
            ota_done = done;
            os.notification.info(F("OS"), F("OTA progress:"), ota_done);
        }
    });

    ArduinoOTA.onError([](ota_error_t error) {
        os.notification.warn(F("OS"), F("OTA error:"), String(error));
    });

    ArduinoOTA.begin();
}

void ota_handle(void) {
    ArduinoOTA.handle();
}

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////

OS os;
