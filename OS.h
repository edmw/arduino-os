#ifndef __OS_H__
#define __OS_H__

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

// use #define OS_USE_STORAGE to disable storage support
#ifndef OS_USE_STORAGE
#define OS_USE_STORAGE true
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// Operating Support:
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "SERIAL.h"
#include "millis.h"
#include "micros.h"
#include "memory.h"

#include "Signaling.h"
#include "Notification.h"

#if OS_USE_STORAGE
#include "Storage.h"
#endif
#include "Files.h"
#include "Network.h"

#ifndef ESP8266
#include "Ticker.h"
#endif

class OS {
public:
    OS();

    bool begin(bool production);

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Give control to OS within the main loop. Necessary to be able to perform an OTA update.
    ///////////////////////////////////////////////////////////////////////////////////////////
    void yield(void);

    ///////////////////////////////////////////////////////////////////////////////////////////
    // End execution in OS because of a fatal error. Will still be able to perform a OTA update.
    ///////////////////////////////////////////////////////////////////////////////////////////
    void fatal(void);

    ///////////////////////////////////////////////////////////////////////////////////////////
    // Signaling:
    // * blinking 2 times a second: network connecting
    // * blinking 1 time a second: network configuring
    // * flashing once a second: fatal error
    ///////////////////////////////////////////////////////////////////////////////////////////
    Signaling signaling;

    Notification notification;

    Files files;
    Network network;

    String error;
};

extern OS os;

#endif
