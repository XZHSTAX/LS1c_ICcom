/*
 * File      : pm_qrcode.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-21     realthread   the first version
 */

#pragma once

#include <pm_widget.h>

namespace Persimmon
{

class QRCode : public Widget
{
public:
    QRCode();
    virtual ~QRCode();

    int setQRCode(int version, const char *source, int size);

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    struct rtgui_dc *qrcode_dc;
};

}
