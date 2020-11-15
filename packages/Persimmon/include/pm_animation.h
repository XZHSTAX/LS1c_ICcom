/*
 * File      : pm_animation.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <pm_widget.h>
#include <pm_timer.h>
#include <vector>

namespace Persimmon
{

enum
{
    ANIM_TICK_RANGE = 1024,
};

class AnimAbstractInterpolator
{
public:
    virtual ~AnimAbstractInterpolator() {}
    virtual int interpolate(int cur, int max)
    {
        return cur * ANIM_TICK_RANGE / max;
    }
};

class AnimLinearInterpolator : public AnimAbstractInterpolator
{
public:
    virtual ~AnimLinearInterpolator() {}
    virtual int interpolate(int cur, int max)
    {
        return cur * ANIM_TICK_RANGE / max;
    }
};

class AnimInsquareInterpolator : public AnimAbstractInterpolator
{
public:
    virtual ~AnimInsquareInterpolator() {}
    virtual int interpolate(int cur, int max)
    {
        /* Care about integer overflow. tick can within 0~(4G/RTGUI_ANIM_TICK_RANGE). */
        return cur * ANIM_TICK_RANGE / max * cur / max;
    }
};

class AnimOutsquareInterpolator : public AnimAbstractInterpolator
{
public:
    virtual ~AnimOutsquareInterpolator() {}
    virtual int interpolate(int cur, int max)
    {
        /* Care about integer overflow. tick can within 0~(4G/RTGUI_ANIM_TICK_RANGE). */
        cur = max - cur;
        return ANIM_TICK_RANGE - (cur * ANIM_TICK_RANGE / max * cur / max);
    }
};


class AnimAbstractAnimator
{
public:
    AnimAbstractAnimator(struct rtgui_dc *b) : buffer(b), wgt(NULL), animInterplator(AnimLinearInterpolator()) {}
    AnimAbstractAnimator(Widget &w) : buffer(NULL), wgt(&w), animInterplator(AnimLinearInterpolator()) {}

    virtual ~AnimAbstractAnimator()
    {
        if (wgt && buffer)
            rtgui_dc_destory(buffer);
    }

    void setInterpolator(AnimAbstractInterpolator &inter)
    {
        animInterplator = inter;
    }

    void setProgress(rt_uint16_t start, rt_uint16_t end)
    {
        if (start > end)
            return;

        proStart = start;
        proEnd = end;
    }

    virtual void act(struct rtgui_dc* dest_dc,
                     int progress, int frames) = 0;
protected:
    struct rtgui_dc *buffer;
    Widget *wgt;
    AnimAbstractInterpolator animInterplator;
    rt_uint16_t proStart, proEnd;
};


class AnimFadeAnimator: public AnimAbstractAnimator
{
    typedef AnimAbstractAnimator super;

public:
    AnimFadeAnimator(struct rtgui_dc *buffer,
                     bool is_fade_out,
                     const Point &start_pt);
    AnimFadeAnimator(Widget &wgt,
                     bool is_fade_out,
                     const Point &start_pt);

    virtual ~AnimFadeAnimator();

    void setFade(rt_uint8_t min = 0, rt_uint8_t max = 255)
    {
        if (min > max)
            return;

        a_min = min;
        a_max = max;
    }

    virtual void act(struct rtgui_dc *dest_dc, int progress, int frames);

protected:
    Point start_pt;
    bool is_fade_out;
    rt_uint8_t a_min, a_max;
};


class AnimMoveAnimator: public AnimAbstractAnimator
{
    typedef AnimAbstractAnimator super;

public:
    AnimMoveAnimator(struct rtgui_dc *buffer,
                     const Point &start_pt,
                     const Point &stop_pt);
    AnimMoveAnimator(Widget &wgt,
                     const Point &start_pt,
                     const Point &stop_pt);

    virtual ~AnimMoveAnimator();

    void setFade(bool is_fade_out, rt_uint8_t min = 0, rt_uint8_t max = 255)
    {
        this->is_fade_out = is_fade_out;

        if (min > max)
            return;

        a_min = min;
        a_max = max;
    }

    void enableFade(bool is_fade = true)
    {
        this->is_fade = is_fade;
    }

    virtual void act(struct rtgui_dc *dest_dc, int progress, int frames);

protected:
    Point start_pt, stop_pt;
    bool is_fade, is_fade_out;
    rt_uint8_t a_min, a_max;
};


class Animation: private utils::noncopyable<Animation>
{
public:
    Animation(Widget &w);
    ~Animation();

    Animation *setBGbuffer(struct rtgui_dc *dc)
    {
        m_bg = dc;
        return this;
    }
    struct rtgui_dc *getBGbuffer(void)
    {
        return m_bg;
    }
    Animation *setFrameInterval(int tick)
    {
        if (tick > 0)
            frameInterval = tick;
        return this;
    }
    Animation *setAnimFrames(int frames)
    {
        if (frames > 0)
            this->frames = frames;
        return this;
    }

    Animation *addAnimator(AnimAbstractAnimator *anim)
    {
        m_animators.push_back(anim);
        return this;
    }

    Signal<struct rtgui_dc *> signalAct;
    Signal<void> signalEnd;

    void start(bool is_modal=true);
    void stop();
    void exit();

private:
    Widget *m_owner;
    Timer *m_timer;
    struct rtgui_dc *m_bg, *saveDc;
    unsigned int frameInterval, frames, progress;

    std::vector<AnimAbstractAnimator*> m_animators;

    enum stat
    {
        ANIM_ST_NONE  = 0,
        ANIM_ST_MODAL = (1 << 0),
        ANIM_ST_STOP  = (0 << 1),
        ANIM_ST_RUN   = (1 << 1),
    } m_stat;

    void drawframeInitial(void);
    void drawframes(void);
};

}
