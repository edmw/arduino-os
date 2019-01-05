#ifndef __SYSTEM_H__
#define __SYSTEM_H__

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

class System {

public:
    /*
      REASON_DEFAULT_RST // normal startup by power on
      REASON_WDT_RST // hardware watch dog reset
      REASON_EXCEPTION_RST // exception reset
      REASON_SOFT_WDT_RST // software watch	dog	reset
      REASON_SOFT_RESTART // software restart
      REASON_DEEP_SLEEP_AWAKE // wake up from deep sleep
      REASON_EXT_SYS_RST // external system reset
    */
    #ifdef ESP8266
    static uint32 lastResetReason();
    static String lastException();
    #endif

    static void wifiOn();
    static void wifiOff();
};

#endif
