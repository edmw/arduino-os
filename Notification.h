#ifndef __NOTIFICATION_H__
#define __NOTIFICATION_H__

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

///////////////////////////////////////////////////////////////////////////////////////////////////
// Operating Support:
// Class to produce output to the serial connection.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "Signaling.h"

class Notification {
public:
    // Constructs a handler for the default serial connection.
    Notification();

    // Begin handling output. Must be called before any other method.
    bool begin(bool production);

    void info(const __FlashStringHelper *realm, const __FlashStringHelper *message);
    void info(const __FlashStringHelper *realm, const __FlashStringHelper *message, const String &printable);
    void info(const __FlashStringHelper *realm, const __FlashStringHelper *message, const char *printable);
    void info(const __FlashStringHelper *realm, const __FlashStringHelper *message, int16_t printable);
    void info(const __FlashStringHelper *realm, const __FlashStringHelper *message, uint16_t printable);
    void info(const __FlashStringHelper *realm, const __FlashStringHelper *message, int32_t printable);
    void info(const __FlashStringHelper *realm, const __FlashStringHelper *message, uint32_t printable);
    void info(const __FlashStringHelper *realm, const __FlashStringHelper *message, float printable);
    void info(const __FlashStringHelper *realm, const __FlashStringHelper *message, const Printable &printable);

    void info_millis(const __FlashStringHelper *realm, const __FlashStringHelper *message, const uint32_t millis);
    void info_byte(const __FlashStringHelper *realm, const __FlashStringHelper *message, const uint8_t byte);

    // Any of the following methods produces output to the serial connection and triggers a signal.

    void warn(const __FlashStringHelper *realm, const __FlashStringHelper *message);
    void warn(const __FlashStringHelper *realm, const __FlashStringHelper *message, const String &printable);

    // Any of the following methods produces output to the serial connection, triggers a signal
    // and stops execution.

    void fatal(const __FlashStringHelper *realm, const __FlashStringHelper *message);
    void fatal(const __FlashStringHelper *realm, const __FlashStringHelper *message, const String &printable);

private:
    bool production;

    void print(const __FlashStringHelper *realm, const String &printable, const __FlashStringHelper *level);

    void info(const __FlashStringHelper *realm, const String &printable);
    void warn(const __FlashStringHelper *realm, const String &printable);
    void fatal(const __FlashStringHelper *realm, const String &printable);

};

#endif
