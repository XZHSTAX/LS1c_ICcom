#pragma once

#include "js_object.h"

#include <pm_timer.h>

class JsTimer : public Persimmon::Timer
{
public:
    JsTimer(jerry_value_t obj, int tick, Timer::flag flag);
    ~JsTimer();

    void onTimeout();

private:
    jerry_value_t timeoutObj;
};
