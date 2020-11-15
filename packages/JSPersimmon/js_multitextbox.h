#pragma once

#include <pm_multi_textbox.h>

class JsMultiTextBox : public Persimmon::MultiTextBox
{
public:
    JsMultiTextBox();

    virtual void setData(void* data);

protected:
};
