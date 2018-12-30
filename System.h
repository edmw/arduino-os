#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <Arduino.h>

class System {

public:
    /*
      REASON_DEFAULT_RST // normal startup by power on
      REASON_WDT_RST // hardware watch dog reset
      REASON_EXCEPTION_RST // exception reset
      REASON_SOFT_WDT_RST // software watch	dog	reset
      REASON_SOFT_RESTART // software restart
      REASON_DEEP_SLEEP_AWAKE // wake up from deep sleep
      REASON_EXT_SYS_RST // external system reset
    */
    #ifdef ESP8266
    static uint32 lastResetReason();
    static String lastException();
    #endif

    static void wifiOn();
    static void wifiOff();
};

#endif
