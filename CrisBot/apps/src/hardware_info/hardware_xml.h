/**
 * Copyright (c) 2023 - present LibDriver All rights reserved
 * 
 * The Personal License (Personal)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      hardware_xml.h
 * @brief     api
 * @version   1.0.0
 * @author    Guangquan Zhang
 * @date      2023-04-06
 */

#ifndef __HARDWARE_XML_H__
#define __HARDWARE_XML_H__

#include "crisbot_type.h"
#include "log.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define HARD_WARE_XML_PATH "/home/zgq/CrisBot/apps/crisbot_xml/hardware.xml"

typedef struct 
{
    crisbot_char device_name[32];
    crisbot_s32 device_value;
    crisbot_float device_float;
}crisbot_hardware_info;


crisbot_bool crisbot_hardware_xml_init();
crisbot_char *crisbot_get_device_name();
crisbot_bool cirsbot_set_device_name(crisbot_char* set_device_name);
crisbot_s32 crisbot_get_device_value();
crisbot_float crisbot_get_device_float();






#ifdef __cplusplus
#if __cplusplus
}




#endif
#endif
#endif