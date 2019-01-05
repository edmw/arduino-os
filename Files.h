#if OS_USE_FILES

#ifndef __FILES_H__
#define __FILES_H__

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
// Class to manage access to the Wear-leveled SPI flash file system (SPIFFS).
// This is a no-op if not run on ESP8266.
///////////////////////////////////////////////////////////////////////////////////////////////////

class Files {
public:
    Files(void);

    // Begin managing the filesystem. Must be called before any other method.
    bool begin(bool production);

    // Saves the given string into a file with the given name.
    void save(String filename, String string);

    // Loads the content of the file with the given name as String.
    String load(String filename);

    // Tests if a file with the given name exists.
    bool exists(String filename);

private:
    bool production;

};

#endif

#endif
