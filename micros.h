// Based on https://github.com/pfeerick/elapsedMillis
//
// Copyright (c) 2011 PJRC.COM, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef __MICROS_H__
#define __MICROS_H__

#include "Arduino.h"

class elapsed_micros {
public:
    elapsed_micros(void) {
        us = micros();
    }
    elapsed_micros(uint32_t val) {
        us = micros() - val;
    }
    elapsed_micros(const elapsed_micros &orig) {
        us = orig.us;
    }
    operator uint32_t () const {
        return micros() - us;
    }
    elapsed_micros & operator = (const elapsed_micros &rhs) {
        us = rhs.us; return *this;
    }
    elapsed_micros & operator = (uint32_t val) {
        us = micros() - val; return *this;
    }
    elapsed_micros & operator -= (uint32_t val) {
        us += val; return *this;
    }
    elapsed_micros & operator += (uint32_t val) {
        us -= val; return *this;
    }
    elapsed_micros operator - (int16_t val) const {
        elapsed_micros r(*this); r.us += val; return r;
    }
    elapsed_micros operator - (uint16_t val) const {
        elapsed_micros r(*this); r.us += val; return r;
    }
    elapsed_micros operator - (int32_t val) const {
        elapsed_micros r(*this); r.us += val; return r;
    }
    elapsed_micros operator - (uint32_t val) const {
        elapsed_micros r(*this); r.us += val; return r;
    }
    elapsed_micros operator + (int16_t val) const {
        elapsed_micros r(*this); r.us -= val; return r;
    }
    elapsed_micros operator + (uint16_t val) const {
        elapsed_micros r(*this); r.us -= val; return r;
    }
    elapsed_micros operator + (int32_t val) const {
        elapsed_micros r(*this); r.us -= val; return r;
    }
    elapsed_micros operator + (uint32_t val) const {
        elapsed_micros r(*this); r.us -= val; return r;
    }

private:
    uint32_t us;

};

#endif
