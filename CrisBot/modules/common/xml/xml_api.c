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
 * @file      xml_api.c
 * @brief     api
 * @version   1.0.0
 * @author    Guangquan Zhang
 * @date      2023-04-06
*/

#include <stdio.h>
#include <string.h>
#include "xml_api.h"
#undef APP_TAG 
#define APP_TAG "Crisbot_XML"

crisbot_bool xml_load_file(const char *file , mxml_node_t **top_node)
{
    FILE *fp = fopen(file,"r");
    if(!fp)
    {
        mloge("fopen %s failed by %s", file, strerror(errno));
        return CRISBOT_FALSE;
    }

    *top_node = mxmlLoadFile(NULL,fp,MXML_OPAQUE_CALLBACK);
    fclose(fp);
    
    return CRISBOT_TRUE;
}

crisbot_bool xml_save_file(const char *file, mxml_node_t *top_node)
{
    FILE *fp = fopen(file,"w+");
    if(!fp)
    {
        mloge("fopen %s failed by %s", file, strerror(errno));
        return CRISBOT_FALSE;
    }
    mxmlSaveFile(top_node,fp,MXML_NO_CALLBACK);
    fclose(fp);
    return CRISBOT_TRUE;
}

crisbot_bool xml_get_str_value(mxml_node_t *node , mxml_node_t *top_node ,\
                               const crisbot_char *name , crisbot_char *value ,\
                               crisbot_s32 size)
{
    mxml_node_t *str_node = NULL;
    str_node = mxmlFindElement(node,top_node,name,NULL,NULL,MXML_DESCEND);
    const crisbot_char *get_value = NULL;
    if(str_node)
    {
       get_value = mxmlGetOpaque(str_node);
       strncpy(value,get_value,size);
       mlogt("%s >> %s\n",name,value);
    }
    else
    {
        mloge("xml_get_str_value is null\n");
        return CRISBOT_FALSE;
    }

    return CRISBOT_TRUE;
}

crisbot_bool xml_set_str_value(mxml_node_t *node , mxml_node_t *top_node ,\
                               const crisbot_char *name , crisbot_char *value)
{
    mxml_node_t *str_node = NULL;
    crisbot_s32 ret = 0;
    str_node = mxmlFindPath(node,(const char *)name);
    if(str_node)
    {
       ret = mxmlSetOpaque(str_node,(const char *)value);
       if(ret!=0)
       {
            mloge("xml_set_srt_value failed %d\n",ret);
       }
       mlogt("%s >> %s\n",name,value);
       mlogt("%d\n",ret);
    }
    else
    {
        mloge("xml_set_str_value is null\n");
        return CRISBOT_FALSE;
    }

    return CRISBOT_TRUE;
}
crisbot_bool xml_get_int_value(mxml_node_t *node , mxml_node_t *top_node ,\
                               const crisbot_char *name , crisbot_s32 *value)
{
    char buffer[32]={0};
    crisbot_s32 ret = 0;
    ret = xml_get_str_value(node,top_node,name,buffer,sizeof(buffer));
    if(!ret)
    {
        mloge("xml_get_str_value failed\n");
        return CRISBOT_FALSE;
    }
    *value = atoi(buffer);

    return CRISBOT_TRUE;
}

crisbot_bool xml_get_float_value(mxml_node_t *node , mxml_node_t *top_node ,\
                               const crisbot_char *name , crisbot_float *value)
{
    char buffer[32]={0};
    crisbot_bool ret = 0;
    ret = xml_get_str_value(node,top_node,name,buffer,sizeof(buffer));
    if(!ret)
    {
        mloge("xml_get_str_value failed\n");
    }
    *value = atof(buffer);

    return CRISBOT_TRUE;
}

