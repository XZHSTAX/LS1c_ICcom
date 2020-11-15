#pragma once

#include <pm_listctrl.h>
#include "js_object.h"

class JsListCtrl : public Persimmon::ListCtrl
{
public:
    JsListCtrl();
    virtual ~JsListCtrl();

    void setJsFunc(jerry_value_t object, const char* func);
    void onSignal(bool value);

    virtual void setData(void* data);

private:
    jerry_value_t jsObj;
    jerry_value_t jsCallFunc;
};
