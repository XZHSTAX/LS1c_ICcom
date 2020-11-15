#pragma once

#include <js_object.h>
#include <pm_page.h>
#include <js_window.h>

#include <string>

class JsPage : public JsObject, public Persimmon::Page
{
public:
    JsPage(JsWindow *win, jerry_value_t obj, std::string &xml);
    virtual ~JsPage();

    void onLoad(jerry_value_t obj);
    void onShowPage(void);
    void onExit(void);
    void onUpdate(jerry_value_t obj);
    virtual void initJsObject(void);
    virtual void setData(void* data);
    virtual void getData(void* data);
    void setData(jerry_value_t data);
    void getData(jerry_value_t data);

    void setExitAnimation(enum AnimType type, rt_uint16_t frames, rt_uint16_t frameInterval)
    {
        exitAnimType = type;
        exitAnimFrames = frames;
        exitAnimFrameInterval = frameInterval;
    }

    void updateExitAnim(void)
    {
        if (exitAnimType != AnimNone)
        {
            setAnimation(exitAnimType, exitAnimFrames, exitAnimFrameInterval, true);
        }
    }

    void setJsFunction(jerry_value_t object, const char* func);
    void bindTouch(const char *type, const struct rtgui_gesture *gest);
    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev, const struct rtgui_gesture *gest);

protected:

private:
    enum AnimType exitAnimType;
    rt_uint16_t exitAnimFrames, exitAnimFrameInterval;
    jerry_value_t jsCallFunc;
    jerry_value_t jsObj;
};
