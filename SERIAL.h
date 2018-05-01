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

// Macros for printing to the serial console.

#define SERIAL_OUT 1

#if SERIAL_OUT
#define SERIAL_BEGIN() { delay(500); Serial.begin(9600); while (!Serial); }
#define SERIAL_PRINT(s) { Serial.print(s); }
#define SERIAL_PRINTF(s, f) { Serial.print(s, f); }
#define SERIAL_PRINTB(b) { b ? Serial.print(F("TRUE")) : Serial.print(F("FALSE")); }
#define SERIAL_PRINTLN(s) { Serial.println(s); }
#define SERIAL_PRINT_BANNER(m) { Serial.println(); Serial.println(m); }
#define SERIAL_PRINT_NUMBER(m, v) { Serial.print(m); Serial.print(v); Serial.println(); }
#define SERIAL_PRINT_MILLIS(m, v) { Serial.print(m); Serial.print(v); Serial.print(F(" ms")); Serial.println(); }
#define SERIAL_PRINT_BYTE(b) { Serial.print(F("0x")); if (b < 16) Serial.print(F("0")); Serial.print(b, HEX); }
#define SERIAL_PRINT_PRINTABLE(p) { p.printTo(Serial); }
#else
#define SERIAL_BEGIN()
#define SERIAL_PRINT(s)
#define SERIAL_PRINTF(s, f)
#define SERIAL_PRINTB
#define SERIAL_PRINTLN(s)
#define SERIAL_PRINT_BANNER(m)
#define SERIAL_PRINT_NUMBER(m, v)
#define SERIAL_PRINT_MILLIS(m, v)
#define SERIAL_PRINT_BYTE(b)
#define SERIAL_PRINT_PRINTABLE(p)
#endif
