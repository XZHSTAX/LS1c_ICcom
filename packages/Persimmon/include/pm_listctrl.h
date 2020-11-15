/*
 * File      : pm_listctrl.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <vector>
#include <pm_container.h>
#include <pm_animation.h>

namespace Persimmon
{

class ListCtrl : public Container
{
public:
    enum type
    {
        HORIZONTAL = 1 << 0,
        VERTICAL = 1 << 1,
        CYCLE = 1 << 2,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(type);

    ListCtrl();
    ListCtrl(const Rect& rect);
    virtual ~ListCtrl();

    void addItem(Widget* widget);
    void addItem(int index, Widget* widget);
    void removeItem(Widget* widget);
    void removeItem(int index);
    void removeItem(const char *name);
    void emptyItem(void);

    void setDirection(enum type direction)
    {
        this->direction = direction;

        if (direction & HORIZONTAL)
            setInterestGesture(RTGUI_GESTURE_TAP | RTGUI_GESTURE_LONGPRESS | RTGUI_GESTURE_DRAG_HORIZONTAL);
        else
            setInterestGesture(RTGUI_GESTURE_TAP | RTGUI_GESTURE_LONGPRESS | RTGUI_GESTURE_DRAG_VERTICAL);
    }

    void setItemGap(int gap)
    {
        if (gap < 0)
            return;

        itemGap = gap;
        firstPosition = itemGap;
        lastPosition = itemGap;
    }

    void fixItemExtent(void);

    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev,
                                    const struct rtgui_gesture *gest);

    Signal<bool> bindSignal;

protected:
    void onAnimation(void);
    void stopAnimation(void);

    int firstPosition, lastPosition;
    int itemGap;
    enum type direction;

    Timer *animTimer;
    int animMovePitch, animMoveProgress;
    bool isAnim, isTop, isDown;
};

}
