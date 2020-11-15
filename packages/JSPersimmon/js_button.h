#pragma once

#include "js_object.h"
#include <pm_button.h>
#include <pm_image.h>

class JsButton : public Persimmon::Button
{
public:
    JsButton();
    virtual ~JsButton();

    void setJsFunction(jerry_value_t object, const char* func);

    void onSignal(int id);

    virtual void setData(void* data);

private:
    jerry_value_t jsCallFunc;
    jerry_value_t jsObj;
    jerry_value_t jsCustomProperty;
};

