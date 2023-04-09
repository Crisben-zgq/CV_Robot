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
 * @file      xml_api.h
 * @brief     api
 * @version   1.0.0
 * @author    Guangquan Zhang
 * @date      2023-04-06
 */

#ifndef __XML_API_H__
#define __XML_API_H__

#include "mxml.h"
#include "crisbot_type.h"
#include "log.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


crisbot_bool xml_load_file(const char *file , mxml_node_t **top_node);

crisbot_bool xml_save_file(const char *file, mxml_node_t *top_node);

crisbot_bool xml_get_str_value(mxml_node_t *node , mxml_node_t *top_node ,\
                               const crisbot_char *name , crisbot_char *value,\
                               crisbot_s32 size);

crisbot_bool xml_set_str_value(mxml_node_t *node , mxml_node_t *top_node ,\
                               const crisbot_char *name , crisbot_char *value);

crisbot_bool xml_get_int_value(mxml_node_t *node , mxml_node_t *top_node ,\
                               const crisbot_char *name , crisbot_s32 *value);

crisbot_bool xml_get_float_value(mxml_node_t *node , mxml_node_t *top_node ,\
                               const crisbot_char *name , crisbot_float *value);



#ifdef __cplusplus
#if __cplusplus
}

#endif
#endif
#endif