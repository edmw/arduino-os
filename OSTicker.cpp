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

#ifndef ESP8266

#include "OSTicker.h"

#include "OS.h"
extern OS os;

Ticker::Ticker() {
    lastTime = 0;
    enabled = false;
}

Ticker::~Ticker() {
}

void Ticker::attach_ms(uint32_t interval, callback_t callback_ptr, void *callback_arg) {
    if (interval > 0 && callback_ptr != NULL) {
        this->interval = interval;
        this->callback_ptr = callback_ptr;
        this->callback_arg = callback_arg;
        lastTime = millis();
        enabled = true;
        state = RUNNING;
    }
}

void Ticker::detach() {
    enabled = false;
    state = STOPPED;
}

void Ticker::pause() {
    diffTime = millis() - lastTime;
    enabled = false;
    state = PAUSED;
}

void Ticker::resume() {
    if (interval > 0 && callback_ptr != NULL) {
        lastTime = millis() - diffTime;
        enabled = true;
        state = RUNNING;
    }
}

void Ticker::update() {
    if(tick()) {
        callback_ptr(callback_arg);
    }
}

bool Ticker::tick() {
    if(!enabled) return false;

    if ((millis() - lastTime) >= interval) {
        lastTime = millis();
        return true;
    }
    return false;
}

uint32_t Ticker::getElapsedTime() {
    return millis() - lastTime;
}

status_t Ticker::getState() {
    return state;
}

uint32_t Ticker::getInterval() {
    return interval;
}

#endif
