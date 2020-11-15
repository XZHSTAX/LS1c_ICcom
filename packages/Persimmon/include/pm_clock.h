/*
 * File      : pm_switch.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-29     realthread   the first version
 */

#pragma once

#include <pm_widget.h>
#include <pm_image.h>

namespace Persimmon
{

class Clock : public Widget
{
public:
    Clock();
    virtual ~Clock();

    void setHourImg(Image *img)
    {
        if (hour)
            delete hour;

        hour = img;
    }

    void setMinuteImg(Image *img)
    {
        if (minute)
            delete minute;

        minute = img;
    }

    void setSecondImg(Image *img)
    {
        if (second)
            delete second;

        second = img;
    }

    void setCenterImg(Image *img)
    {
        if (center)
            delete center;

        center = img;
    }

    void setTime(int time)
    {
        if (time < 0 || time >= 24 * 60 * 60)
            timeSec = 0;
        else
            timeSec = time;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    Image *hour, *minute, *second, *center;
    int timeSec;
};

}
