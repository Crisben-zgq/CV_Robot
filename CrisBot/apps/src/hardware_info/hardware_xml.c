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

#include <stdio.h>
#include <string.h>
#include "xml_api.h"
#include "hardware_xml.h"
static crisbot_hardware_info g_crisbot_hardware_info = {0};

static crisbot_bool crisbot_hardware_xml_get_value()
{
    mxml_node_t *top_node = NULL;
    CRISBOT_S32 ret = 0;
    ret = xml_load_file(HARD_WARE_XML_PATH,&top_node);
    if(!ret)
    {
        mloge("hardware_xml_load_file failed\n");
        return CRISBOT_FALSE;
    }
    ret = xml_get_str_value(top_node,top_node,"device_name",g_crisbot_hardware_info.device_name,sizeof(g_crisbot_hardware_info.device_name));
    if(!ret)
    {
        mloge("xml_get_str_value device_name failed\n");
        return CRISBOT_FALSE;
    }
    ret = xml_get_int_value(top_node,top_node,"device_value",&g_crisbot_hardware_info.device_value);
    if(!ret)
    {
        mloge("xml_get_int_value device_value failed\n");
        return CRISBOT_FALSE;
    }
    ret = xml_get_float_value(top_node,top_node,"device_float",&g_crisbot_hardware_info.device_float);
    if(!ret)
    {
        mloge("xml_get_float_value device_float failed\n");
        return CRISBOT_FALSE;
    }
    mxmlDelete(top_node);
    return CRISBOT_TRUE;

}

static crisbot_bool crisbot_hardware_xml_set_value(crisbot_char *hardware_set_info)
{
    mxml_node_t *top_node = NULL;
    CRISBOT_S32 ret = 0;
    ret = xml_load_file(HARD_WARE_XML_PATH,&top_node);
    if(!ret)
    {
        mloge("hardware_xml_load_file failed\n");
        return CRISBOT_FALSE;
    }
    ret = xml_set_str_value(top_node,top_node,"hardware_info/device_name",hardware_set_info);
    if(!ret)
    {
        mloge("xml_set_str_value device_name failed\n");
    }
    ret = xml_save_file(HARD_WARE_XML_PATH,top_node);
    if(!ret)
    {
        mloge("hardware_xml_load_file failed\n");
        return CRISBOT_FALSE;
    }
    return CRISBOT_TRUE;
}

crisbot_bool crisbot_hardware_xml_init()
{
    CRISBOT_S32 ret = 0;
    ret = crisbot_hardware_xml_get_value();
    if(!ret)
    {
        mloge("crisbot_hardware_xml_get_value failed\n");
    }
    return CRISBOT_TRUE;
}

crisbot_char *crisbot_get_device_name()
{
    return g_crisbot_hardware_info.device_name;
}

crisbot_s32 crisbot_get_device_value()
{
    return g_crisbot_hardware_info.device_value;
}

crisbot_float crisbot_get_device_float()
{
    return g_crisbot_hardware_info.device_float;
}

crisbot_bool cirsbot_set_device_name(crisbot_char* set_device_name)
{
    return crisbot_hardware_xml_set_value(set_device_name);
}