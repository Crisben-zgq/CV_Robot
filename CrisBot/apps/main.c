#include <stdio.h>
#include "log.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include "hardware_xml.h"
#undef APP_TAG
#define APP_TAG "LOG_TEST"

int main(int argc,char *argv[])
{
    crisbot_hardware_xml_init();
    char *ch = NULL;
    char ch2[32] = {0};
    ch = crisbot_get_device_name();
    memcpy(ch2,ch,sizeof(ch2));
    char ch1[32] = "HELLO";
    cirsbot_set_device_name(ch1);
    mlogp("%s\n",ch2);
    return 0;
}