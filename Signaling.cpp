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
#ifdef ESP8266
#include <Ticker.h>
#endif
#ifdef ESP32
#include "analogWrite.h"
#endif

#include "Signaling.h"

#include "OS.h"
extern OS os;

///////////////////////////////////////////////////////////////////////////////////////////////////

class Signaling::Implementation {
    Signaling * const signaling;

public:
    uint8_t ledpin = LED_BUILTIN;

    uint8_t ledon = HIGH;
    uint8_t ledoff = LOW;

    bool state;

    elapsed_millis instant;

    bool production;

    Ticker ticker;

    Implementation(Signaling *p) : signaling(p) {
    }

    void dwrite(uint8_t ledpin, bool value) {
        state = value;
        analogWrite(ledpin, 0);
        digitalWrite(ledpin, value);
        instant = 0;
    }

    void awrite(uint8_t ledpin, uint8_t value) {
        state = (value > 0) ? ledon : ledoff;
        analogWrite(ledpin, value);
        instant = 0;
    }

    void on(bool force) {
        if (ledpin >= 0) {
            if (force) ticker.detach();
            dwrite(ledpin, ledon);
        }
    }
    void off(bool force) {
        if (ledpin >= 0) {
            if (force) ticker.detach();
            dwrite(ledpin, ledoff);
        }
    }
    void toggle(bool force) {
        if (ledpin >= 0) {
            if (force) ticker.detach();
            dwrite(ledpin, !state);
        }
    }

    void set(uint32_t brightness) {
        if (ledpin >= 0) {
            if (brightness == 0) {
                dwrite(ledpin, ledoff);
            }
            else if (brightness == PWMRANGE) {
                dwrite(ledpin, ledon);
            }
            else {
                awrite(ledpin, brightness);
            }
        }
    }

    static void __elapsing(void *me) {
        Signaling::Implementation *self = static_cast<Signaling::Implementation*>(me);
        self->off(true);
    }

    static void __blinking(void *me) {
        Signaling::Implementation *self = static_cast<Signaling::Implementation*>(me);
        self->toggle(false);
    }

    static void __flashing(void *me) {
        Signaling::Implementation *self = static_cast<Signaling::Implementation*>(me);
        uint32_t ms = millis() % 1000;
        if (ms < 100) {
            self->on(false);
        }
        else {
            self->off(false);
        }
    }

    static void __pulsing(void *me) {
        Signaling::Implementation *self = static_cast<Signaling::Implementation*>(me);
        float ms = millis() / 1000.0;
        self->set(sin(ms * 2.0 * PI) * PWMRANGE/2.0 + PWMRANGE/2.0);
    }

};

///////////////////////////////////////////////////////////////////////////////////////////////////

Signaling::Signaling()
    : impl { new Implementation(this) } {
    impl->ledpin = LED_BUILTIN;
    impl->ledon = LOW;
    impl->ledoff = HIGH;
    impl->production = false;
    impl->state = impl->ledoff;
}

Signaling::Signaling(uint8_t ledpin, uint8_t active)
    : impl { new Implementation(this) } {
    impl->ledpin = ledpin;
    impl->ledon = active;
    impl->ledoff = !active;
    impl->production = false;
    impl->state = impl->ledoff;
}

Signaling::~Signaling() {
    delete impl;
}

bool Signaling::begin(bool production = true) {
    impl->production = production;

    if (impl->ledpin >= 0) {
        pinMode(impl->ledpin, OUTPUT);
        impl->off(true);
    }
    return true;
}

bool Signaling::loop() {
    #ifndef ESP8266
    impl->ticker.update();
    #endif
    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool Signaling::isOn(void) {
    return impl->state == impl->ledon;
}

void Signaling::on(Brightness brightness) {
    impl->on(true);
    switch (brightness) {
    case Brightness::Percent10: impl->set(102); break;
    case Brightness::Percent50: impl->set(512); break;
    case Brightness::Full: break;
    // default: 100 % without pwm
    }
}
void Signaling::off(void) {
    impl->off(true);
}
void Signaling::toggle(void) {
    impl->toggle(true);
}

elapsed_millis Signaling::lastChanged(void) {
    return impl->instant;
}

void Signaling::set(uint32_t brightness) {
    impl->set(brightness);
}

void Signaling::once(uint32_t ms) {
    once(ms, ms);
}

void Signaling::once(uint32_t on_ms, uint32_t off_ms) {
    impl->on(true);
    delay(on_ms);
    impl->off(true);
    delay(off_ms);
}

void Signaling::elapsing(uint32_t ms) {
    if (impl->ledpin >= 0) {
        impl->on(true);
        impl->ticker.attach_ms(ms, &Implementation::__elapsing, (void*)this);
    }
}

void Signaling::blinking() {
    if (impl->ledpin >= 0) {
        impl->ticker.attach_ms(1000, &Implementation::__blinking, (void*)this);
    }
}

void Signaling::flashing() {
    if (impl->ledpin >= 0) {
        impl->ticker.attach_ms(100, &Implementation::__flashing, (void*)this);
    }
}

void Signaling::pulsing() {
    if (impl->ledpin >= 0) {
        impl->ticker.attach_ms(10, &Implementation::__pulsing, (void*)this);
    }
}

void Signaling::loop_pulsing() {
    float ms = millis() / 5000.0;
    impl->set(sin(ms * 2.0 * PI) * PWMRANGE / 4.0 + PWMRANGE / 2.0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
