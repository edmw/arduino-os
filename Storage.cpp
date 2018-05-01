#if OS_USE_STORAGE

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
#include <EEPROMex.h>

#include "Storage.h"

#include "OS.h"
extern OS os;

#define REALM F("STORAGE")

#define SLOT_SIZE 8

static_assert (
    sizeof(union Storage::storageValue) <= SLOT_SIZE,
        "STORAGE: slot size to small, must be equal or larger than size of storageValue"
);

//#define DEBUG_STORAGE

///////////////////////////////////////////////////////////////////////////////////////////////////

Storage::Storage(void) {
}

bool Storage::begin(bool production, int memsize) {
    this->production = production;

    EEPROM.setMemPool(0, memsize);
    if (!production) {
        EEPROM.setMaxAllowedWrites(100);
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool Storage::put8(uint16_t slot, uint8_t value) {
    if (dataForSlot.find(slot) == dataForSlot.end()) {
        data_t data = { value: { uint8: value }, dirty: true };
        dataForSlot[slot] = data;
    }
    else {
        if (dataForSlot[slot].value.uint8 != value) {
            dataForSlot[slot].value.uint8 = value;
            dataForSlot[slot].dirty = true;
        }
    }
    return true;
}

bool Storage::put16(uint16_t slot, uint16_t value) {
    if (dataForSlot.find(slot) == dataForSlot.end()) {
        data_t data = { value: { uint16: value }, dirty: true };
        dataForSlot[slot] = data;
    }
    else {
        if (dataForSlot[slot].value.uint16 != value) {
            dataForSlot[slot].value.uint16 = value;
            dataForSlot[slot].dirty = true;
        }
    }
    return true;
}

bool Storage::put32(uint16_t slot, uint32_t value) {
    if (dataForSlot.find(slot) == dataForSlot.end()) {
        data_t data = { value: { uint32: value }, dirty: true };
        dataForSlot[slot] = data;
    }
    else {
        if (dataForSlot[slot].value.uint32 != value) {
            dataForSlot[slot].value.uint32 = value;
            dataForSlot[slot].dirty = true;
        }
    }
    return true;
}

bool Storage::pull8(uint16_t slot, uint8_t &value) {
    if (dataForSlot.find(slot) == dataForSlot.end()) {
        data_t data = { value: { uint8: 0 }, dirty: false };
        uint16_t address = slot_to_address(slot);
        EEPROM.readBlock(address, data.value);
        #ifdef DEBUG_STORAGE
        os.notification.info(REALM, F("read from address"), address);
        os.notification.info(REALM, F("value"), data.value.uint8);
        #endif
        dataForSlot[slot] = data;
    }
    value = dataForSlot[slot].value.uint8;
    return true;
}

bool Storage::pull16(uint16_t slot, uint16_t &value) {
    if (dataForSlot.find(slot) == dataForSlot.end()) {
        data_t data = { value: { uint16: 0 }, dirty: false };
        uint16_t address = slot_to_address(slot);
        EEPROM.readBlock(address, data.value);
        #ifdef DEBUG_STORAGE
        os.notification.info(REALM, F("read from address"), address);
        os.notification.info(REALM, F("value"), data.value.uint16);
        #endif
        dataForSlot[slot] = data;
    }
    value = dataForSlot[slot].value.uint16;
    return true;
}

bool Storage::pull32(uint16_t slot, uint32_t &value) {
    if (dataForSlot.find(slot) == dataForSlot.end()) {
        data_t data = { value: { uint32: 0 }, dirty: false };
        uint16_t address = slot_to_address(slot);
        EEPROM.readBlock(address, data.value);
        #ifdef DEBUG_STORAGE
        os.notification.info(REALM, F("read from address"), address);
        os.notification.info(REALM, F("value"), data.value.uint32);
        #endif
        dataForSlot[slot] = data;
    }
    value = dataForSlot[slot].value.uint32;
    return true;
}

bool Storage::flush() {
    for (auto const &element : dataForSlot) {
        uint16_t slot = element.first;
        data_t data = element.second;
        if (data.dirty) {
            uint16_t address = slot_to_address(slot);
            EEPROM.writeBlock<value_t>(address, data.value);
            #ifdef DEBUG_STORAGE
            os.notification.info(REALM, F("write to address"), address);
            #endif
            data.dirty = false;
        }
    }
    return false;
}

bool Storage::check8(uint16_t slot, uint8_t expected) {
    value_t value;
    uint16_t address = slot_to_address(slot);
    EEPROM.readBlock<value_t>(slot_to_address(slot), value);
    #ifdef DEBUG_STORAGE
    os.notification.info(REALM, F("check at address"), address);
    os.notification.info(REALM, F("value"), value.uint8);
    #endif
    return (value.uint8 == expected);
}

bool Storage::check16(uint16_t slot, uint16_t expected) {
    value_t value;
    uint16_t address = slot_to_address(slot);
    EEPROM.readBlock<value_t>(slot_to_address(slot), value);
    #ifdef DEBUG_STORAGE
    os.notification.info(REALM, F("check at address"), address);
    os.notification.info(REALM, F("value"), value.uint16);
    #endif
    return (value.uint16 == expected);
}

bool Storage::check32(uint16_t slot, uint32_t expected) {
    value_t value;
    uint16_t address = slot_to_address(slot);
    EEPROM.readBlock<value_t>(slot_to_address(slot), value);
    #ifdef DEBUG_STORAGE
    os.notification.info(REALM, F("check at address"), address);
    os.notification.info(REALM, F("value"), value.uint32);
    #endif
    return (value.uint32 == expected);
}

uint16_t Storage::slot_to_address(uint16_t slot) {
    return slot * SLOT_SIZE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif
