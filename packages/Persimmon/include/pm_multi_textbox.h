/*
 * File      : pm_multi_textbox.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <pm_widget.h>
#include <vector>

namespace Persimmon
{

class MultiTextBox : public Widget
{
public:
    MultiTextBox();
    MultiTextBox(const Rect& rect);
    MultiTextBox(struct rtgui_font* font, const Rect& rect);
    virtual ~MultiTextBox();

    void addText(const char* text);
    void addText(char text);
    void addText(int num);


    char *getText(void);
    int getCurrentLines(void)
    {
        return textLinesPtr.size();
    }

    char *getLineText(int index);

    void cutText(void);
    void clearText(void);

    void setRowHeight(int h)
    {
        rowHeight = h;
    }

    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

private:
    void updateText(const char* fmt, ...);
    void branch(void);
    std::vector<char *> textLinesPtr;

    char *text;
    int rowHeight, currentLine;
    int textTotalLen;
};

}
