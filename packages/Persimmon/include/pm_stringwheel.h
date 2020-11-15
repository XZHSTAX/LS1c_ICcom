/*
 * File      : pm_stringwheel.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <vector>
#include <pm_widget.h>
#include <sigslot.h>
#include <pm_timer.h>

namespace Persimmon
{

class StringWheel : public Widget
{
public:
    enum type
    {
        HORIZONTAL = 1 << 0,
        VERTICAL = 1 << 1,
        CYCLE = 1 << 2,
    };
    DEFINE_CLASS_ENUM_FLAG_OPERATORS(type);

    StringWheel(const Rect& rect, int norSize, int selSize, enum type tp = HORIZONTAL);
    virtual ~StringWheel();

    Signal<int> clicked;

    void updateStrSize(void)
    {
        if (mtype & HORIZONTAL)
        {
            strWidth = norExtentSize;
            strHeight = getRect().getHeight();
        }
        else
        {
            strWidth = getRect().getWidth();
            strHeight = norExtentSize;
        }
    }

    void addStr(const char *text);
    void addStr(char *fmt, ...);
    void emptyStringWheel(void)
    {
        int size = str.size();

        for (int i = 0; i < size; i++)
        {
            if (str[i])
                rt_free(str[i]);
        }
        str.clear();
        extent.clear();

        number.clear();

        cycleEnable = 0;
        selItemNum = -1;
        currentItemNum = -1;
        itemMovePitch = 0;
        oldPitch = 0;
        _progress = 10;
    }

    void cycleMandatoryEnable(void)
    {
        int wWidth, size = str.size();

        cycleEnable = 1;
        mtype = mtype | CYCLE;

        if (mtype & HORIZONTAL)
        {
            wWidth = getRect().getWidth();
        }
        else
        {
            wWidth = getRect().getHeight();
        }

        do
        {
            cycleEnable ++;

            for (int i = 0; i < size; i++)
            {
                if (str[i])
                {
                    str.push_back(rt_strdup(str[i]));
                    extent.push_back(extent[i]);
                    number.push_back(str.size() - 1);
                }
            }
        }
        while(wWidth > selExtentSize + ((int)str.size() - 2) * norExtentSize);
    }

    void setSlideType(enum type tp = HORIZONTAL)
    {
        mtype = tp;

        if (mtype & HORIZONTAL)
            setInterestGesture(RTGUI_GESTURE_TAP | RTGUI_GESTURE_LONGPRESS | RTGUI_GESTURE_DRAG_HORIZONTAL);
        else
            setInterestGesture(RTGUI_GESTURE_TAP | RTGUI_GESTURE_LONGPRESS | RTGUI_GESTURE_DRAG_VERTICAL);
    }

    void fixItemExtent(int itemNum, bool ref);

    int getSelItemNum(void)
    {
        return selItemNum;
    }

    void setAdjustSpeed(int value)	//�����������ƽ����󣬿ؼ������������ٶȣ�������
    {
        if (value >= 0)
            adjustSpeed = value;
    }

    void animationEnable(bool enable = true)
    {
        animEnable = enable;
    }

    void tapSelEnable(bool enable = true)
    {
        tapEnable = enable;
    }

    virtual bool handleGestureEvent(struct rtgui_event_gesture *gev,
                                    const struct rtgui_gesture *gest);
    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
                        const Rect &srcRect = Rect(),
                        RenderFlag flags = DrawNormal);

protected:
    std::vector<char *> str;
    std::vector<Rect> extent;
    std::vector<int> number;
    int norExtentSize, selExtentSize;
    int strWidth, strHeight;
    int selItemNum, currentItemNum, selProgress;

private:
    void moveItem(bool ref);
    void filterSelItem(void);		    //ɸѡ����ǰѡ����

    void animationStart(void);		   	//��ʼ����
    void onAnimation(void);			    //����ˢ��

    enum type mtype;			       	//�������� ˮƽ��ֱ
    int cycleEnable;

    int itemMovePitch, oldPitch, adjustSpeed;

    Timer *animationTimer;		//����Ч��ʹ�õĶ�ʱ��
    bool animationMoving, animEnable, tapEnable;		//true ��Ϊ��������ʱ  false ���
    int animationMovePitch, _progress;	   	//�ֱ�Ϊδѡ�����ѡ��������ƶ����ܾ���
    int animationPitch, animationProgress;	//�ֱ�Ϊδѡ�����ѡ������е�ǰ�ƶ��ľ��룬�Լ� animationProgress ��������
};



//class StringWheelOne : public StringWheel
//{
//public:
//    StringWheelOne(const Rect& rect, int norSize, int selSize, enum type tp = VERTICAL);
//    virtual ~StringWheelOne();

//    void setItemFontSizeBoundary(int max, int mini)
//    {
//        selItemFontSize = max;
//        norItemFontSize = mini;
//    }

//    void setItemFontColor(rtgui_color_t selColor, rtgui_color_t norColor)
//    {
//        selItemFontColor = selColor;
//        norItemFontColor = norColor;
//        setForeground(norColor);
//    }

//    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
//                        const Rect &srcRect = Rect(),
//                        RenderFlag flags = DrawNormal);

//private:
//    int norItemFontSize, selItemFontSize;
//    rtgui_color_t norItemFontColor, selItemFontColor;
//};



//class StringWheelTwo : public StringWheel
//{
//public:
//    StringWheelTwo(const Rect& rect, int norSize, int selSize, enum type tp = VERTICAL);
//    virtual ~StringWheelTwo();

//    void setItemFontSizeBoundary(int max, int mini)
//    {
//        selItemFontSize = max;
//        norItemFontSize = mini;
//    }

//    void setImage(Image *img, Point point, const Rect& rect, rtgui_color_t fore, rtgui_color_t back)
//    {
//		if (_image)
//			delete _image;

//        _image = img;
//        _point = point;
//        selRect = rect;
//        strRect = Rect(rect.left() + img->getWidth(), 0, rect.getWidth() - img->getWidth(), rect.getHeight());

//        foreColor = fore;
//        backColor = back;

//        if (selDc)
//        {
//            rtgui_dc_destory(selDc);
//            selDc = RT_NULL;
//        }

//        if (selDc == RT_NULL)
//        {
//            selDc = rtgui_dc_buffer_create_pixformat(RTGRAPHIC_PIXEL_FORMAT_RGB565, selRect.getWidth(), selRect.getHeight());
//            if (selDc)
//            {
//                rtgui_gc_t *gc = rtgui_dc_get_gc(selDc);

//                gc->background = backColor;
//                gc->foreground = foreColor;
//                gc->font = getFont();
//                gc->textalign = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_CENTER_VERTICAL;
//            }
//        }
//    }

//    virtual void render(struct rtgui_dc* dc, const Point &dcPoint = Point(),
//                        const Rect &srcRect = Rect(),
//                        RenderFlag flags = DrawNormal);

//private:
//    int norItemFontSize, selItemFontSize;

//    Image *_image;			//ѡ�п���ߵ�ͼƬ
//    Point _point;			//ͼƬ��ʾ�����ѡ�п�������ʼ��
//    Rect selRect, strRect;	//ѡ�п��ַ�����ʾ��������Ӧ����
//    rtgui_color_t foreColor, backColor;		//ѡ�п��ǰ��ɫ�ͱ���ɫ������ɫ��ؼ�����ɫһ��
//    struct rtgui_dc *selDc;		//ѡ�п� dc
//};

}
