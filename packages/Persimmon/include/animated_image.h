/*
 * File      : animated_image.h
 * COPYRIGHT (C) 2012-2018, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-22     realthread   the first version
 */

#pragma once

#include <vector>
#include <image_box.h>
#include <pm_timer.h>
#include <resource.h>

namespace Persimmon
{

class AnimatedImage : public ImageBox
{
public:
    AnimatedImage();
    AnimatedImage(unsigned int ms);
    virtual ~AnimatedImage();

    void addImage(const char *img);

    void startAnimation(void)
    {
        if (this->imagePath.size() <= 0)
            return;

        this->running = true;
        timer->start();
    }

    void stopAnimation(void)
    {
        this->running = false;
        this->index = 0;
        timer->stop();

        if (this->image[index])
        {
            setProvisionalImage(this->image[index]);

            refresh();
        }
    }

    void pauseAnimation(void)
    {
        this->running = false;
        timer->stop();
    }

    void setLoop(bool loop)
    {
        this->loop = loop;
    }

    bool isRunning(void)
    {
        return this->running;
    }

    bool isLoop(void)
    {
        return this->loop;
    }

    void setInterval(unsigned int ms)
    {
        if (ms > 0)
            timer->setTimeout(rt_tick_from_millisecond(ms));
    }

protected:
    void timeout(void);
    void empty(void);

    Timer *timer;
    unsigned int index;
    std::vector<char *> imagePath;
    std::vector<Image *> image;
    bool running, loop;
};

}
