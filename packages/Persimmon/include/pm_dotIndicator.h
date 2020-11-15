/*
 * File      : pm_dotIndicator.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <pm_widget.h>
#include <pm_image.h>

namespace Persimmon
{

class DotIndicator : public Widget
{
public:
    enum type
    {
        HORIZONTAL = 1 << 0,
        VERTICAL = 1 << 1,
        CYCLE = 1 << 2,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(type);

    DotIndicator();
    DotIndicator(Image *norImg, Image *selImg, int num, int gap = 0);
    virtual ~DotIndicator();

    void setDotImage(Image *norImg, Image *selImg)
    {
        if (norImage) delete norImage;
        if (selImage) delete selImage;

        norImage = norImg;
        selImage = selImg;
    }

    void setDirection(enum type t = HORIZONTAL)
    {
        direction = t;
    }

    void selectDotIndicator(int num)    /* 选中对应编号的点，起始值 0 */
    {
        if (num >= dotIndicatorNum || num < 0)
            return;

        dotIndicatorSelNum = num;
    }

    int getSelectNum(void)  /* 获取当前选中点编号 */
    {
        return dotIndicatorSelNum;
    }

    void setDotIndicatorNum(int num)   /* 设置总共有多少个点 */
    {
        dotIndicatorNum = num;
    }

    void setDotIndicatorGap(int gap)
    {
        dotIndicatorGap = gap;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    enum type direction;
    Image *norImage, *selImage;
    int dotIndicatorNum, dotIndicatorSelNum, dotIndicatorGap;
};

}
