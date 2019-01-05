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

#include "Notification.h"
#include "Signaling.h"

#include "SERIAL.h"

#include "OS.h"
extern OS os;

///////////////////////////////////////////////////////////////////////////////////////////////////

Notification::Notification() {
    production = false;
}

bool Notification::begin(bool production) {
    this->production = production;
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Notification::print(const __FlashStringHelper *realm, const String &printable, const __FlashStringHelper *level) {
    if (!production) {
        SERIAL_PRINT(F("["));
        SERIAL_PRINT(millis());
        SERIAL_PRINT(F("]"));
        SERIAL_PRINT(F("["));
        SERIAL_PRINT(String(level));
        SERIAL_PRINT(F("]"));
        SERIAL_PRINT(F("{"));
        SERIAL_PRINT(String(realm));
        SERIAL_PRINT(F("} "));
        SERIAL_PRINT(printable);
    }
}

void Notification::info(const __FlashStringHelper *realm, const String &printable) {
    if (!production) {
        print(realm, printable, F("INFO"));
        SERIAL_PRINTLN();
    }
}
void Notification::info(const __FlashStringHelper *realm, const __FlashStringHelper *message) {
    if (!production) { info(realm, String(message)); }
}
void Notification::info(const __FlashStringHelper *realm, const __FlashStringHelper *message, const String &printable) {
    if (!production) { info(realm, String(message) + " " + printable); }
}
void Notification::info(const __FlashStringHelper *realm, const __FlashStringHelper *message, const char *printable) {
    if (!production) { info(realm, message, String(printable)); }
}
void Notification::info(const __FlashStringHelper *realm, const __FlashStringHelper *message, int16_t printable) {
    if (!production) { info(realm, message, String(printable)); }
}
void Notification::info(const __FlashStringHelper *realm, const __FlashStringHelper *message, uint16_t printable) {
    if (!production) { info(realm, message, String(printable)); }
}
void Notification::info(const __FlashStringHelper *realm, const __FlashStringHelper *message, int32_t printable) {
    if (!production) { info(realm, message, String(printable)); }
}
void Notification::info(const __FlashStringHelper *realm, const __FlashStringHelper *message, uint32_t printable) {
    if (!production) { info(realm, message, String(printable)); }
}
void Notification::info(const __FlashStringHelper *realm, const __FlashStringHelper *message, float printable) {
    if (!production) { info(realm, message, String(printable)); }
}
void Notification::info_millis(const __FlashStringHelper *realm, const __FlashStringHelper *message, const uint32_t millis) {
    if (!production) { info(realm, message, String(millis) + " ms"); }
}
void Notification::info_byte(const __FlashStringHelper *realm, const __FlashStringHelper *message, const uint8_t byte) {
    if (!production) { info(realm, message, "0x" + String(byte, HEX)); }
}
void Notification::info(const __FlashStringHelper *realm, const __FlashStringHelper *message, const Printable &printable) {
    if (!production) {
        print(realm, String(message), F("INFO"));
        SERIAL_PRINT(" ");
        SERIAL_PRINT_PRINTABLE(printable);
        SERIAL_PRINTLN();
    }
}

void Notification::warn(const __FlashStringHelper *realm, const String &printable) {
    if (!production) { print(realm, printable, F("WARN")); }
    os.signaling.once(500);
}
void Notification::warn(const __FlashStringHelper *realm, const __FlashStringHelper *message) {
    if (!production) { warn(realm, String(message)); }
}
void Notification::warn(const __FlashStringHelper *realm, const __FlashStringHelper *message, const String &printable) {
    if (!production) { warn(realm, String(message) + " " + printable); }
}

void Notification::fatal(const __FlashStringHelper *realm, const String &printable) {
    if (!production) { print(realm, printable, F("FATAL")); }
    os.fatal();
}
void Notification::fatal(const __FlashStringHelper *realm, const __FlashStringHelper *message) {
    if (!production) { fatal(realm, String(message)); }
}
void Notification::fatal(const __FlashStringHelper *realm, const __FlashStringHelper *message, const String &printable) {
    if (!production) { fatal(realm, String(message) + " " + printable); }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
