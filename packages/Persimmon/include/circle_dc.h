/*
 * File      : circle_dc.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once

#include <rtgui/rtgui.h>
#include <rtgui/dc.h>

/* for sin/cos etc */
#include <math.h>

void renderCircle(struct rtgui_dc *src, rt_int16_t x, rt_int16_t y, rt_int16_t angle1, rt_int16_t angle2, rt_int16_t r1, rt_int16_t r2, struct rtgui_dc *dest, rtgui_rect_t *rect);
