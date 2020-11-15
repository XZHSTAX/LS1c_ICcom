
#ifndef JS_LCD_H__
#define JS_LCD_H__

#ifdef __cplusplus
extern "C"
{
#endif

void js_set_brightness(double value);
double js_get_brightness(void);
void js_set_screen_on(rt_bool_t screen);

#ifdef __cplusplus
}
#endif

#endif
