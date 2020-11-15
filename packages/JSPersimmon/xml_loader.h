#pragma once

#include <persimmon.h>
#include "js_page.h"

using namespace Persimmon;

class XmlRenderPrivate;

class XmlLoadWidget
{
public:
    XmlLoadWidget(JsPage *page);
    XmlLoadWidget(JsPage *page, const char* filename, bool isLoadPage = true);
    ~XmlLoadWidget();

    Widget *loadJsWidget(const char* filename);
    Widget *loadJsPanel(Widget *panel, const char* filename);
    Widget *getJsWidget(void)
    {
        return jsWidget;
    }

    friend class XmlRenderPrivate;

protected:
    JsPage *jsPage;
    Widget *jsWidget;
};
