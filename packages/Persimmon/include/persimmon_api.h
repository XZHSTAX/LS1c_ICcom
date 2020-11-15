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
    ��ť�࣬�ӿؼ���������

    Button(const char *text, Image *imgNor, Image *imgDown);
    �������ܣ�����һ����ť��
    ����������text ��ť����ʾ���ı����ݣ�imgNor ��ť������ʾ��ͼƬ��imgDown ��ť����״̬ʱ��ʾ��ͼƬ��

    Button(Image *imgNor, Image *imgDown);
    �������ܣ�����һ����ť��
    ����������imgNor ��ť������ʾ��ͼƬ��imgDown ��ť����״̬ʱ��ʾ��ͼƬ��

    void setText(const char *text);
    �������ܣ����ð�ť��ʾ���ַ����ı����ݡ�
    ����������text �ַ����ı����ݡ�

    const char* getText(void);
    �������ܣ���ȡ��ť��ʾ���ַ����ı����ݡ�

    void setNorImage(Image *imgNor);
    �������ܣ����ð�ť������ʾ��ͼƬ��
    ����������imgNor ͼƬ��

    Image* getNorImage(void);
    �������ܣ���ȡ��ť������ʾ��ͼƬ��

    void setDownImage(Image *imgDown);
    �������ܣ����ð�ť����״̬ʱ��ʾ��ͼƬ��
    ����������imgDown ͼƬ��

    Image* getDownImage(void);
    �������ܣ���ȡ��ť����״̬ʱ��ʾ��ͼƬ��

    void setShadowImage(Image *imgShadow);
    �������ܣ����ð�ť����״̬ʱ��ť���渲����ʾ��ͼƬ��
    ����������imgShadow ͼƬ��

    Image* getShadowImage(void);
    �������ܣ���ȡ��ť����״̬ʱ��ť���渲����ʾ��ͼƬ��

    Signal<int> clicked;
    �źţ�����ť����ɹ�ʱ�������źŴ��������ú�����źŹ����ĺ�����
          �źſɴ���һ�� int ���Ͳ����������ذ�ť�ı�ţ�
*/

/*
    class Label : public Widget
    ��ǩ�࣬�ӿؼ���������

    Label(const char* label);
    �������ܣ�����һ����ǩ��
    ����������label ��ǩ�����ַ�����

    Label(const char* label, const Rect& rect);
    �������ܣ�����һ����ǩ��
    ����������label ��ǩ�����ַ�����rect ��ǩ��λ�ô�С��

    Label(const char *label, struct rtgui_font* font);
    �������ܣ�����һ����ǩ��
    ����������label ��ǩ�����ַ�����font ��ǩ��ʾ���塣

    Label(const char *label, struct rtgui_font* font, const Rect& rect);
    �������ܣ�����һ����ǩ��
    ����������label ��ǩ�����ַ�����font ��ǩ��ʾ���壻rect ��ǩ��λ�ô�С��

    void setLabel(const char* label);
    �������ܣ����ñ�ǩ��ʾ���ݡ�
    ����������label ��ǩ�����ַ�����

    void setLabel(int number);
    �������ܣ����ñ�ǩ���ݡ�
    ����������number ��ǩ�������֡�

    void setLabel(char* fmt, ...);
    �������ܣ����ñ�ǩ���ݡ�
    �����������ɱ������

    char* getLabel(void);
    �������ܣ���ȡ��ǩ���ݡ�
    �� �� ֵ�����ر�ǩ���ݣ��ַ���ָ�롣

	void clearLabel(void);
    �������ܣ������ǩ���ݡ�
*/

/*
    class ImageBox : public Widget
    ͼƬ���࣬�ӿؼ���������

    ImageBox(Image *image);
    �������ܣ�����һ��ͼƬ�С�
    ����������image ͼƬ��

    void setImage(Image *image);
    �������ܣ�����ͼƬ���е�ͼƬ��
    ����������image ͼƬ��

    Image* getImage(void);
    �������ܣ���ȡͼƬ���е�ͼƬ��
    �� �� ֵ��ͼƬ���е�ͼƬ��ͼƬ��ָ�롣
*/

/*
    class Switch : public Widget
    ���ذ�ť�࣬�ӿؼ���������

    Switch(Image* offBgImg, Image* onBgImg, bool status = false);
    �������ܣ�����һ�����ذ�ť��
    ����������offBgImg ���� off ״̬ʱ����ͼƬ��onBgImg ���� on ״̬ʱ����ͼƬ��status ���س�ʼ״ֵ̬��

    void setBgImage(Image* offBgImg, Image* onBgImg);
    �������ܣ����ÿ��ذ�ť����ͼƬ��
    ����������offBgImg ���� off ״̬ʱ����ͼƬ��onBgImg ���� on ״̬ʱ����ͼƬ��

    void setFgImage(Image* offFgImg, Image* onFgImg);
    �������ܣ����ÿ��ذ�ťǰ��ͼƬ��
    ����������offFgImg ���� off ״̬ʱǰ��ͼƬ��onFgImg ���� on ״̬ʱǰ��ͼƬ��

    void setStatus(bool on);
    �������ܣ����ÿ��ذ�ť��״̬��
    ����������on ���ذ�ť��״ֵ̬ bool ���͡�

    bool getStatus(void);
    �������ܣ���ȡ���ذ�ť��״̬��
    �� �� ֵ�����ذ�ť��״ֵ̬ bool ���͡�

    Signal<int, bool> changed;
    �źţ������ذ�ť״̬���ʱ�������źŴ��������ú�����źŹ����ĺ�����
          �źſɴ���һ�� int ���Ͳ����������ذ�ť�ı�ţ�
          ��һ�� bool ���Ͳ����������ذ�ť��״̬��
*/
