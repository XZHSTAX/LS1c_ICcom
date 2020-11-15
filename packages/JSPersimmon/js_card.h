#pragma once

#include "js_object.h"
#include <card.h>


class JsCard : public Persimmon::Card
{
public:
    JsCard();
    virtual ~JsCard();

    void setJsFunction(jerry_value_t object, const char* func);

    void onSignal(int id, int value);

    virtual void setData(void* data);

private:
    jerry_value_t jsCallFunc;
    jerry_value_t jsObj;
};

