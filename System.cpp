#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

#include "System.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ESP8266

extern "C" {
    #include "user_interface.h"
}

uint32 System::lastResetReason() {
    struct rst_info *info = system_get_rst_info();
    return info->reason;
}

String System::lastException() {
    struct rst_info *info = system_get_rst_info();
    if (info->reason == REASON_WDT_RST ||
        info->reason == REASON_EXCEPTION_RST ||
        info->reason == REASON_SOFT_WDT_RST)
    {
        return "reason=" + ESP.getResetReason() +
            ", exccause=0x" + String(info->exccause, HEX) +
            ", excvaddr=0x" + String(info->excvaddr, HEX) +
            ", epc1=0x" + String(info->epc1, HEX) +
            ", epc2=0x" + String(info->epc2,HEX) +
            ", epc3=0x" + String(info->epc3, HEX) +
            ", depc=0x" + String(info->depc, HEX);
    }
    else {
        return "reason=" + ESP.getResetReason();
    }
}

void System::wifiOn() {
    WiFi.forceSleepWake();
    delay(1);
    WiFi.mode(WIFI_STA);
    delay(100);
}

void System::wifiOff() {
    WiFi.disconnect();
    uint16_t i = 0;
    while ((WiFi.status() == WL_CONNECTED) && (i++ < 3*10)) {
        delay(100);
    }
    WiFi.mode(WIFI_OFF);
    delay(1);
    WiFi.forceSleepBegin();
    delay(100);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
#else
///////////////////////////////////////////////////////////////////////////////////////////////////

void System::wifiOn() {
}

void System::wifiOff() {
}

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////
