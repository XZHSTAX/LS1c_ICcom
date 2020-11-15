
#ifndef JS_OTA_H__
#define JS_OTA_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

int js_ota_start(void);
int js_ota_update(const void * buffer, rt_size_t size);
int js_ota_done(void);
const char *js_get_version(const char *type);

#ifdef __cplusplus
}
#endif

#endif
