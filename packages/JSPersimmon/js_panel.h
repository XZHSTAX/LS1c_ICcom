#pragma once

#include "js_object.h"
#include <pm_panel.h>
#include <sigslot.h>


class JsPanel : public Persimmon::Panel
{
public:
    JsPanel();
    virtual ~JsPanel();

    virtual void setData(void* data);

    void setJsFunction(jerry_value_t object, const char* func);
    void bindTouch(const char *type, const struct rtgui_gesture *gest);
    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev, const struct rtgui_gesture *gest);

private:
    jerry_value_t jsCallFunc;
    jerry_value_t jsObj;
    bool bindtouch;
};
