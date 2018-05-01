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
#include <FS.h>
#endif

#include "Files.h"

#include "OS.h"
extern OS os;

///////////////////////////////////////////////////////////////////////////////////////////////////

Files::Files(void) {
}

bool Files::begin(bool production) {
    this->production = production;
    #ifdef ESP8266
    if (SPIFFS.begin()) {
        if (!production) {
            // Development: print statistics
            FSInfo fs_info;
            SPIFFS.info(fs_info);
            os.notification.info(F("FILES"), F("Total bytes:"), fs_info.totalBytes);
            os.notification.info(F("FILES"), F("Used bytes:"), fs_info.usedBytes);
        }
        return true;
    }
    return false;
    #else
    return true;
    #endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Files::save(String filename, String string) {
    #ifdef ESP8266
    File outfile = SPIFFS.open(String(filename + ".dat"), "w");
    if (outfile) {
        outfile.println(String(string + String('\r')));
        outfile.close();
    }
    else {
        os.notification.warn(F("FILES"), F("Failed to write to file:"), filename);
    }
    #endif
}

String Files::load(String filename) {
    #ifdef ESP8266
    String string;
    File infile = SPIFFS.open(String(filename + ".dat"), "r");
    if (infile) {
        string = infile.readStringUntil('\r');
        string.replace("\n", "");
        infile.close();
        return string;
    }
    else {
        os.notification.warn(F("FILES"), F("Failed to read from file:"), filename);
    }
    #endif
    return String();
}

bool Files::exists(String filename) {
    #ifdef ESP8266
    return SPIFFS.exists(String(filename + ".dat"));
    #else
    return false;
    #endif
}
