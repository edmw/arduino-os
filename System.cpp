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
#include <ESP8266WiFi.h>
#endif

#include "System.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ESP8266

extern "C" {
    #include "user_interface.h"
}

uint32 System::lastResetReason() {
    struct rst_info *info = system_get_rst_info();
    return info->reason;
}

String System::lastException() {
    struct rst_info *info = system_get_rst_info();
    if (info->reason == REASON_WDT_RST ||
        info->reason == REASON_EXCEPTION_RST ||
        info->reason == REASON_SOFT_WDT_RST)
    {
        return "reason=" + ESP.getResetReason() +
            ", exccause=0x" + String(info->exccause, HEX) +
            ", excvaddr=0x" + String(info->excvaddr, HEX) +
            ", epc1=0x" + String(info->epc1, HEX) +
            ", epc2=0x" + String(info->epc2,HEX) +
            ", epc3=0x" + String(info->epc3, HEX) +
            ", depc=0x" + String(info->depc, HEX);
    }
    else {
        return "reason=" + ESP.getResetReason();
    }
}

void System::wifiOn() {
    WiFi.forceSleepWake();
    delay(1);
    WiFi.mode(WIFI_STA);
    delay(100);
}

void System::wifiOff() {
    WiFi.disconnect();
    uint16_t i = 0;
    while ((WiFi.status() == WL_CONNECTED) && (i++ < 3*10)) {
        delay(100);
    }
    WiFi.mode(WIFI_OFF);
    delay(1);
    WiFi.forceSleepBegin();
    delay(100);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#else
///////////////////////////////////////////////////////////////////////////////////////////////////

void System::wifiOn() {
}

void System::wifiOff() {
}

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////
