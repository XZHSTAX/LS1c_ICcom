#ifndef JS_EVENT_H__
#define JS_EVENT_H__

#include <rtgui/event.h>

#define PM_CMD_JS_CALLBACK     0x10000

#ifdef __cplusplus
extern "C" {
#endif

struct JsCallback
{
    struct rtgui_event_win parent;
    /* command type */
    rt_int32_t type;
    void *parameter;
};

int js_set_app(struct rtgui_app *app);
struct rtgui_app *js_get_app(void);
rt_bool_t js_do_callback(void *parameter);
int js_handle_callback(struct rtgui_event_command* event);

#ifdef __cplusplus
}
#endif

#endif
