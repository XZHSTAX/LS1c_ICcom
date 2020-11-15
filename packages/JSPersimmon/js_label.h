#pragma once

#include <pm_label.h>

class JsLabel : public Persimmon::Label
{
public:
    JsLabel();
    JsLabel(const char* label);
    JsLabel(const char* label, const Persimmon::Rect& rect);
    JsLabel(const char *label, struct rtgui_font* font);
    JsLabel(const char *label, struct rtgui_font* font, const Persimmon::Rect& rect);

    virtual void setData(void* data);

protected:
};
