#pragma once

#include "js_object.h"
#include "js_window.h"
#include "js_page.h"

#include <pm_application.h>

#include <vector>
#include <string>
#include <list>

class JsApp : public JsObject, public Persimmon::Application
{
public:
    JsApp(jerry_value_t obj);
    virtual ~JsApp();

    virtual void initJsObject(void);
    void onLaunch(void);
    void onExit(void);
    void onUpdate(jerry_value_t obj);
    void onShow(void);
    void jsWindowShow(void);

    static JsApp *getAppSelf();
    virtual rt_bool_t eventHandler(struct rtgui_event *event);

    void loadPage(const char* url);
    void navigateTo(const char* url);
    void navigateTo(jerry_value_t obj);
    void redirectTo(const char* url);
    void redirectTo(jerry_value_t obj);
    void navigateBack(jerry_value_t obj);
    double getCurrentPages(void)
    {
        return (double)window->getPageSize();
    }

    JsPage* getLastPage(unsigned int index = 1)
    {
        return (JsPage*)window->getLastPage(index);
    }

    JsPage* getCurrentPage(void)
    {
        return (JsPage*)window->getCurrentPage();
    }

    std::string &getJumpPageXml()
    {
        return jumpPageXml;
    }

    JsWindow *getWindow(void)
    {
        return window;
    }

    void setJumpPage(JsPage* page)
    {
        jumpPage = page;
    }

    std::string getAppPath()
    {
        return appPath;
    }

protected:
    std::string appPath, jumpPageXml;
    JsWindow *window;
    JsPage *jumpPage, *delPage;
};

