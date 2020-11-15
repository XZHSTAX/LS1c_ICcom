/*
 * File      : pm_page.h
 * COPYRIGHT (C) 2012-2018, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-06     realthread   the first version
 */

#pragma once

#include <pm_window.h>

namespace Persimmon
{

class Page : public Container
{
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

    Page(Window *win);
    virtual ~Page();

    void navigateTo(Page *page);
    void redirectTo(Page *page);
    void doJumpAnimShow(Page *page);
    Page* navigateBack(bool update = true);
    void navigateBack(unsigned int num, bool update = true);
    Page* getCurrentPage(void);
    Page* getLastPage(unsigned int index = 1);
    unsigned int getPageSize(void);
    Window* getPageWin(void);

    void setAnimation(enum AnimType type, rt_uint16_t frames, rt_uint16_t frameInterval, bool fadeOut = false);

protected:

private:
    Window *pWin;
};

}
