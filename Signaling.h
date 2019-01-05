#ifndef __SIGNALING_H__
#define __SIGNALING_H__

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

#ifndef ESP8266
#define PWMRANGE 255
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// Operating Support:
// Class to produce output to a digital pin. Which most often will be a LED.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "millis.h"

class Signaling {
    class Implementation;

public:
    enum class Brightness : uint8_t { Percent10, Percent50, Full };

    // Constructs a handler for the builtin LED.
    Signaling();
    // Constructs a handler for the given pin with the given mode (active-low or active-high).
    Signaling(uint8_t ledpin, uint8_t active);
    ~Signaling();

    // Begin handling output. Must be called before any other method.
    bool begin(bool production);

    // Handle output. Must be called within the loop.
    bool loop(void);

    // Returns true, if the output is on.
    bool isOn(void);

    // Turns the output on (LOW on active-low, HIGH on active-high)
    void on(Brightness brightness = Brightness::Full);
    // Turns the output off.
    void off(void);
    // Toggles the output’s state.
    void toggle(void);

    // Elapsed milliseconds since the last change of state of the output.
    elapsed_millis lastChanged(void);

    // Sets the output to the given value (only works for PWM enabled outputs).
    void set(uint32_t brightness = PWMRANGE);

    // Turns the output on for the given amount of time and off for the same amount of time.
    void once(uint32_t ms);
    // Turns the output on for the given amount of time and off for the other given amount of time.
    void once(uint32_t on_ms, uint32_t off_ms);

    // Turns the output on and off after the given amount of time.
    void elapsing(uint32_t ms);
    // Starts blinking the output (1000 ms on and off).
    void blinking(void);
    // Starts flashing the output (100 ms on, 900 ms off).
    void flashing(void);
    // Starts pulsing the output (works for PWM enabled outputs only).
    void pulsing(void);

    void loop_pulsing(void);

private:
    Signaling(const Signaling&);
    Signaling& operator=(const Signaling&);

    Implementation *impl;

};

#endif
