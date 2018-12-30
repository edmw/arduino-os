#ifndef ESP8266

#ifndef TICKER_H
#define TICKER_H

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

#include "Arduino.h"

enum status_t { STOPPED, RUNNING, PAUSED };

typedef void (*callback_t)(void*);

class Ticker {
public:
    Ticker();
    ~Ticker();

    void attach_ms(uint32_t interval, callback_t callback_ptr, void* callback_arg);
    void detach();

    void pause();
    void resume();

    void update();

    uint32_t getElapsedTime();
    status_t getState();
    uint32_t getInterval();

private:
    bool tick();

    bool enabled;

    uint32_t interval;
    status_t state;

    callback_t callback_ptr;
    void* callback_arg;

    uint32_t lastTime;
    uint32_t diffTime;
};

#endif // TICKER_H

#else // ESP8266
#include <Ticker.h>
#endif // ESP8266
