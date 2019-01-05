#if OS_USE_STORAGE

#ifndef __STORAGE_H__
#define __STORAGE_H__

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

#include <map>

///////////////////////////////////////////////////////////////////////////////////////////////////
// Operating Support:
// Class to manage access to the EEPROM.
///////////////////////////////////////////////////////////////////////////////////////////////////

class Storage {
public:
    Storage(void);

    // Begin managing the eeprom. Must be called before any other method.
    bool begin(bool production, int memsize);

    bool put8(uint16_t slot, uint8_t value);
    bool put16(uint16_t slot, uint16_t value);
    bool put32(uint16_t slot, uint32_t value);

    bool pull8(uint16_t slot, uint8_t &value);
    bool pull16(uint16_t slot, uint16_t &value);
    bool pull32(uint16_t slot, uint32_t &value);

    bool check8(uint16_t slot, uint8_t value);
    bool check16(uint16_t slot, uint16_t value);
    bool check32(uint16_t slot, uint32_t value);

    bool flush(void);

    typedef union storageValue {
        uint8_t uint8;
        uint16_t uint16;
        uint32_t uint32;
    } value_t;

    typedef struct storageData {
        value_t value;
        bool dirty;
    } data_t;

private:
    bool production;

    std::map<uint16_t, data_t> dataForSlot;

    uint16_t slot_to_address(uint16_t slot);
};

#endif

#endif
