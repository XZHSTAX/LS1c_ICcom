/*
 * File      : pm_window.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <rtgui/widgets/window.h>

#include <pm_widget.h>
#include <pm_container.h>
#include <vector>
#include <pm_animation.h>
#include <pm_page.h>

namespace Persimmon
{

class Page;

class Window : public Container
{
    typedef Container super;
public:
    enum AnimType
    {
        AnimNone = 0x00,
        AnimFade = 0x01,
        AnimMove = 0x02,
        AnimMoveTop = 0x04,
        AnimMoveBottom = 0x08,
        AnimMoveLeft = 0x10,
        AnimMoveRight = 0x20,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(AnimType);

    /* create a main window */
    Window(const char *title);
    /* create a normal window */
    Window(struct rtgui_win *parent, const char *title, rtgui_rect_t *rect, rt_uint16_t style);

    virtual ~Window();

    virtual int show(rt_bool_t isModal = RT_FALSE);
    virtual void close(int code = 0);
    void hide()
    {
        rtgui_win_hide(getWindow());
    }

    void move(int x, int y);

    struct rtgui_win* getWindow(void)
    {
        return RTGUI_WIN(widget);
    }
    Widget *getChildbyName(const char *name);

    rt_bool_t privateEventHandler(struct rtgui_event *event);
    virtual rt_bool_t eventHandler(struct rtgui_event *event);
    virtual bool dealKbd(struct rtgui_event_kbd *kev);
    virtual bool dealCmd(struct rtgui_event_command *cmd);

    void saveClip(struct rtgui_region &region);
    void restoreClip(struct rtgui_region &region);

    void addFloatingWidget(Widget *widget);
    Widget *getFloatingWidgetbyName(const char *name);
    void removeFloatingWidget(Widget *widget);
    void renderFloatingWidget(struct rtgui_dc *dc, rtgui_rect_t *rect);
    void renderLogo(struct rtgui_dc *dc, rtgui_rect_t *rect);

    /* Animation */
    void setAnimType(enum AnimType type, Point start = Point(0, 0), Point end = Point(0, 0));
    void setAnimFrame(rt_uint16_t frames, rt_uint16_t frameInterval = 50);  //frameInterval(ms)
    void setAnimDc(struct rtgui_dc *fgDc, struct rtgui_dc *bgDc);
    void setAnimFade(bool fadeOut, rt_uint8_t min = 0, rt_uint8_t max = 255);
    void doAnimation(void);
    void setAnimation(enum AnimType type, rt_uint16_t frames, rt_uint16_t frameInterval, bool fadeOut = false);
    void doAnimShow(Page *page = RT_NULL);
    void doAnimHide(Page *page = RT_NULL);

    void paintWindow(void);
    void clearGesture(void);

    Signal<void> signalShow;

    /* Page manage API */
    void navigateTo(Page *page);
    void redirectTo(Page *page);
    void doJumpAnimShow(Page *page);
    Page *navigateBack(bool update = true);
    void navigateBack(unsigned int num, bool update = true);
    void emptyPage(void);
    Page* getCurrentPage(void);
    Page* getLastPage(unsigned int index = 1);
    unsigned int getPageSize(void);
    virtual void pageEmpty(void);

protected:
    void paintChildren();
    bool dealMouseButton(struct rtgui_event_mouse *mev);
    bool dealMouseMotion(struct rtgui_event_mouse *mev);
    bool dealGesture(struct rtgui_event_gesture *gev);

private:
    void setupMouseOwner(struct rtgui_event_mouse *mev);
    Widget *setupMouseOwnerFloating(struct rtgui_event_mouse *mev);
    void renderFloatingWidget(rtgui_rect_t *rect);
    void renderLogo(rtgui_rect_t *rect);

    struct rtgui_gesture gesture;
    Widget *mouseEventOwner;
    rt_uint32_t curMouseId;
    bool RTGUI_MOUSE_BUTTON_IS_DOWN, SHOW_FIRST;

    /* floating widget */
    std::vector<Widget*> childrenFloating;

    /* Animation */
    enum AnimType animType;
    Point animStart, animEnd;
    bool doAnim, animFadeOut;
    rt_uint8_t animFadeMin, animFadeMax;
    rt_uint16_t animFrames, animFrameInterval;
    struct rtgui_dc *animFgDc, *animBgDc;

    /* page */
    friend class Page;
    std::vector<Page*> page;
    bool firstPageShow;
};

}
