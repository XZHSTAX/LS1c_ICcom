/*
 * File      : pm_wheel.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <vector>
#include <pm_container.h>
#include <sigslot.h>
#include <pm_timer.h>

namespace Persimmon
{

class Wheel : public Container
{
public:
    enum type
    {
        HORIZONTAL = 1 << 0,
        VERTICAL = 1 << 1,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(type);

    Wheel(enum type tp = HORIZONTAL);
    Wheel(const Rect& rect, enum type tp = HORIZONTAL);
    virtual ~Wheel();

    void fixSelItem(void);
    void fixSelItem(unsigned int num);
    void fixItemPtich(bool actEnable = true);
    void selectItem(unsigned int num);

    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev, const struct rtgui_gesture *gest);
    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(), const Rect &srcRect = Rect(), RenderFlag flags = DrawNormal);

    virtual void act(unsigned int num)
    {
        //rt_kprintf(" act num : %d\n", num);
    }

    virtual void end(unsigned int num)
    {
        //rt_kprintf(" end num : %d\n", num);
    }

    virtual void tap(unsigned int num)
    {
        //rt_kprintf(" tap num : %d\n", num);
    }

    void setShowSize(unsigned int normal, unsigned int center = 0)
    {
        normalSize = normal;
        centerSize = normal > center ? normal : center;
    }

    void setShowItems(unsigned int items)
    {
        showItems = items / 2 * 2 + 1;
    }

    void setItemSize(unsigned int size)
    {
        itemSize = size;
    }

    int getCenterSelNum(void)
    {
        return centerSelNum;
    }

    void setDirection(enum type t)
    {
        direction = t;

        if (direction & HORIZONTAL)
            setInterestGesture(RTGUI_GESTURE_TAP | RTGUI_GESTURE_LONGPRESS | RTGUI_GESTURE_DRAG_HORIZONTAL);
        else
            setInterestGesture(RTGUI_GESTURE_TAP | RTGUI_GESTURE_LONGPRESS | RTGUI_GESTURE_DRAG_VERTICAL);
    }

    void enableBindTap(bool tap = true)
    {
        bindTapEnable = tap;
    }

    void enableTapSwitch(bool tap = true)
    {
        bindTapSwitch = tap;
    }

    void switchNextItem(void)
    {
        switchItem(false);
    }

    void switchPrevItem(void)
    {
        switchItem(true);
    }

protected:
    void onAnimation(void);
    void stopAnimation(void);
    void switchItem(bool type);

    enum type direction;
    int movePitch, gestPitch;
    int centerSelNum;

    int normalSize, centerSize, showItems, itemSize;
    int firstItemPitch, firstItemNum, itemMovePitch;
    int centerNum, oldNum;

    Timer *animTimer;
    int animMovePitch, animMoveProgress;
    bool isFirstRender, isAnim, isStopAnim;
    bool bindTapEnable, bindTapSwitch;
};

class WheelImage : public Wheel
{
public:
    WheelImage();
    WheelImage(const Rect& rect);
    virtual ~WheelImage();

    void addImage(Image *img);

    void setForeImage(Image *img)
    {
        if (foreImage)
            delete foreImage;

        foreImage = img;
    }

    virtual void act(unsigned int num)
    {
        bindChanged(num);
    }

    virtual void tap(unsigned int num)
    {
        bindTap(num);
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

    Signal<unsigned int> bindChanged, bindTap;

protected:
    std::vector<Image *> image;

private:
    Image *foreImage;
};

class WheelString : public Wheel
{
public:
    WheelString();
    WheelString(const Rect& rect);
    virtual ~WheelString();

    void addString(const char* str);

    void setFontColor(rtgui_color_t nor, rtgui_color_t sel)
    {
        norColor = nor;
        selColor = sel;
    }

    void setForeImage(Image *img)
    {
        if (foreImage)
            delete foreImage;

        foreImage = img;
    }

    void signalEnableString(bool enable = true)
    {
        signalString = enable;
    }

    virtual void act(unsigned int num)
    {
        if (signalString)
            bindChangedS(str[num]);
        else
            bindChanged(num);
    }

    virtual void tap(unsigned int num)
    {
        if (signalString)
            bindTapS(str[num]);
        else
            bindTap(num);
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

    Signal<unsigned int> bindChanged, bindTap;
    Signal<std::string> bindChangedS, bindTapS;

protected:
    std::vector<std::string> str;

private:
    rtgui_color_t norColor, selColor;
    Image *foreImage;
    bool signalString;
};

class CarouselImage : public Wheel
{
public:
    CarouselImage();
    CarouselImage(const Rect& rect);
    virtual ~CarouselImage();

    void addImage(Image *img);
    void addString(const char* str);
    void removeItem(const char* str);
    void emptyItem(void);
    void selectItem(const char* str);

    std::string getItemString(int index)
    {
        std::string none;

        if (index >= 0 && index < (int)this->str.size())
        {
            return this->str[index];
        }

        return none;
    }

    void setZoom(double zoom)
    {
        this->zoom = zoom;
    }

    void setForeImage(Image *img)
    {
        if (foreImage)
            delete foreImage;

        foreImage = img;
    }

    virtual void act(unsigned int num)
    {
        bindChanged(num);
    }

    virtual void tap(unsigned int num)
    {
        bindTap(num);
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

    Signal<int> bindChanged, bindTap;

protected:
    std::vector<std::string> str;
    std::vector<Image *> image;

private:
    Image *foreImage;
    double zoom;
};

class DemoWidgetWheel : public Wheel
{
public:
    DemoWidgetWheel(const Rect& rect);
    virtual ~DemoWidgetWheel();

    void addWidget(Widget *widget);

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

protected:
    std::vector<Widget *> widget;

private:

};

}
