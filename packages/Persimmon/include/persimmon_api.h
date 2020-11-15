/*
* File      : persimmon_api.h
* COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
*
* Change Logs:
* Date             Author          Notes
* 2018-01-06       XY              the first version
*/


/*
    class Button : public Widget
    按钮类，从控件类派生；

    Button(const char *text, Image *imgNor, Image *imgDown);
    函数功能：构造一个按钮。
    参数描述：text 按钮上显示的文本内容；imgNor 按钮正常显示的图片；imgDown 按钮按下状态时显示的图片。

    Button(Image *imgNor, Image *imgDown);
    函数功能：构造一个按钮。
    参数描述：imgNor 按钮正常显示的图片；imgDown 按钮按下状态时显示的图片。

    void setText(const char *text);
    函数功能：设置按钮显示的字符串文本内容。
    参数描述：text 字符串文本内容。

    const char* getText(void);
    函数功能：获取按钮显示的字符串文本内容。

    void setNorImage(Image *imgNor);
    函数功能：设置按钮正常显示的图片。
    参数描述：imgNor 图片。

    Image* getNorImage(void);
    函数功能：获取按钮正常显示的图片。

    void setDownImage(Image *imgDown);
    函数功能：设置按钮按下状态时显示的图片。
    参数描述：imgDown 图片。

    Image* getDownImage(void);
    函数功能：获取按钮按下状态时显示的图片。

    void setShadowImage(Image *imgShadow);
    函数功能：设置按钮按下状态时按钮表面覆盖显示的图片。
    参数描述：imgShadow 图片。

    Image* getShadowImage(void);
    函数功能：获取按钮按下状态时按钮表面覆盖显示的图片。

    Signal<int> clicked;
    信号：当按钮点击成功时触发，信号触发后会调用和这个信号关联的函数；
          信号可传递一个 int 类型参数，即开关按钮的编号；
*/

/*
    class Label : public Widget
    标签类，从控件类派生；

    Label(const char* label);
    函数功能：构造一个标签。
    参数描述：label 标签内容字符串。

    Label(const char* label, const Rect& rect);
    函数功能：构造一个标签。
    参数描述：label 标签内容字符串；rect 标签的位置大小。

    Label(const char *label, struct rtgui_font* font);
    函数功能：构造一个标签。
    参数描述：label 标签内容字符串；font 标签显示字体。

    Label(const char *label, struct rtgui_font* font, const Rect& rect);
    函数功能：构造一个标签。
    参数描述：label 标签内容字符串；font 标签显示字体；rect 标签的位置大小。

    void setLabel(const char* label);
    函数功能：设置标签显示内容。
    参数描述：label 标签内容字符串。

    void setLabel(int number);
    函数功能：设置标签内容。
    参数描述：number 标签内容数字。

    void setLabel(char* fmt, ...);
    函数功能：设置标签内容。
    参数描述：可变参数。

    char* getLabel(void);
    函数功能：获取标签内容。
    返 回 值：返回标签内容，字符串指针。

	void clearLabel(void);
    函数功能：清除标签内容。
*/

/*
    class ImageBox : public Widget
    图片盒类，从控件类派生；

    ImageBox(Image *image);
    函数功能：构造一个图片盒。
    参数描述：image 图片。

    void setImage(Image *image);
    函数功能：设置图片盒中的图片。
    参数描述：image 图片。

    Image* getImage(void);
    函数功能：获取图片盒中的图片。
    返 回 值：图片盒中的图片，图片类指针。
*/

/*
    class Switch : public Widget
    开关按钮类，从控件类派生；

    Switch(Image* offBgImg, Image* onBgImg, bool status = false);
    函数功能：构造一个开关按钮。
    参数描述：offBgImg 开关 off 状态时背景图片；onBgImg 开关 on 状态时背景图片；status 开关初始状态值。

    void setBgImage(Image* offBgImg, Image* onBgImg);
    函数功能：设置开关按钮背景图片。
    参数描述：offBgImg 开关 off 状态时背景图片；onBgImg 开关 on 状态时背景图片。

    void setFgImage(Image* offFgImg, Image* onFgImg);
    函数功能：设置开关按钮前景图片。
    参数描述：offFgImg 开关 off 状态时前景图片；onFgImg 开关 on 状态时前景图片。

    void setStatus(bool on);
    函数功能：设置开关按钮的状态。
    参数描述：on 开关按钮的状态值 bool 类型。

    bool getStatus(void);
    函数功能：获取开关按钮的状态。
    返 回 值：开关按钮的状态值 bool 类型。

    Signal<int, bool> changed;
    信号：当开关按钮状态变更时触发，信号触发后会调用和这个信号关联的函数；
          信号可传递一个 int 类型参数，即开关按钮的编号；
          和一个 bool 类型参数，即开关按钮的状态；
*/
