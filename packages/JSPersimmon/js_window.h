#pragma once

#include <js_object.h>
#include <pm_window.h>
#include <pm_timer.h>

using namespace Persimmon;

class JsPage;

class JsWindow : public JsObject, public Persimmon::Window
{
public:
    JsWindow(const char* name);
    virtual ~JsWindow();

    void onUpdate(jerry_value_t obj);
    virtual bool dealCmd(struct rtgui_event_command *cmd);
    void keyboard(jerry_value_t obj);

    void timeout(void);
#ifdef PKG_JS_PERSIMMON_DEVELOPMENT_MODE
    void timeoutEnv(void);
#endif
    void doDelPage(JsPage *page);

private:
    Timer *timer;
#ifdef PKG_JS_PERSIMMON_DEVELOPMENT_MODE
    Timer *timerEnv;
#endif
    JsPage *delPage;
};

