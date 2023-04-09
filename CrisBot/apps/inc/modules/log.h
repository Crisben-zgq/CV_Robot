/*
 * @Descripttion: 
 * @version: 
 * @Author: B000214
 * @Date: 2022-04-12 16:29:47
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-05-04 11:14:31
 */
#ifndef __LOG_H__
#define __LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>


#ifndef APP_TAG
#define APP_TAG ""
#endif



/* color log macro define */
#define NONE         "\033[m"
#define RED          "\033[0;32;31m"
#define LIGHT_RED    "\033[1;31m"
#define GREEN        "\033[0;32;32m"
#define LIGHT_GREEN  "\033[1;32m"
#define BLUE         "\033[0;32;34m"
#define LIGHT_BLUE   "\033[1;34m"
#define DARY_GRAY    "\033[1;30m"
#define CYAN         "\033[0;36m"
#define LIGHT_CYAN   "\033[1;36m"
#define PURPLE       "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN        "\033[0;33m"
#define YELLOW       "\033[1;33m"
#define LIGHT_GRAY   "\033[0;37m"
#define WHITE        "\033[1;37m"


typedef enum {
	CLLOG_OPTS_OFF = 0x0,
	CLLOG_OPTS_TO_CONSOLE = 0x01,
	CLLOG_OPTS_TO_FILE = 0x02
}CLLOG_OPT;


/* log level define */
typedef enum {
	CLLOG_LEVEL_OFF,		/* 关闭所有日志 */
    CLLOG_LEVEL_FATAL, 	/* action must be taken immediately */
    CLLOG_LEVEL_ERROR,     /* error conditions */
	CLLOG_LEVEL_PRINT, 	/* print directly */
    CLLOG_LEVEL_WARNING,   /* warning conditions */
    CLLOG_LEVEL_INFO,      /* informational */
    CLLOG_LEVEL_DEBUG,     /* debug-level */
    CLLOG_LEVEL_TRACE,
	CLLOG_LEVEL_BUTT,
    CLLOG_LEVEL_APPEND = 0x8000
} CLLOG_Level;

void CLLOG_Init(int opts, int logWithTime, const char *path, int max_file_size);

void CLLOG_SetLevel(int level);

int CLLOG_GetLevel(void);

void CLLOG_Print(int level, const char *module, const char *func, unsigned int line,
    const char *format, ...) __attribute__((format(printf, 5, 6)));

void CLLOG_SetOpts(int opts, const char *path, int max_file_size/*bytes*/);

void CLLOG_FileClose();


#define DEBUG

#ifdef DEBUG
#define mlogt(fmt, args...) do {  CLLOG_Print(CLLOG_LEVEL_TRACE, APP_TAG, __func__, __LINE__, fmt, ##args); } while(0)
#define mlogd(fmt, args...) do {  CLLOG_Print(CLLOG_LEVEL_DEBUG, APP_TAG, __func__, __LINE__, fmt, ##args); } while(0)
#define mlogi(fmt, args...) do {  CLLOG_Print(CLLOG_LEVEL_INFO, APP_TAG, __func__, __LINE__, fmt, ##args); } while(0)
#define mlogw(fmt, args...) do {  CLLOG_Print(CLLOG_LEVEL_WARNING, APP_TAG, __func__, __LINE__, fmt, ##args); } while(0)
#define mloge(fmt, args...) do { CLLOG_Print(CLLOG_LEVEL_ERROR, APP_TAG, __func__, __LINE__, fmt, ##args); } while(0)
#define mlogp(fmt, args...) do { CLLOG_Print(CLLOG_LEVEL_PRINT, APP_TAG, __func__, __LINE__, fmt, ##args); } while(0)
#define mlogf(fmt, args...) do { CLLOG_Print(CLLOG_LEVEL_FATAL, APP_TAG, __func__, __LINE__, fmt, ##args); } while(0)
#define mloga(fmt, args...) do { CLLOG_Print(CLLOG_LEVEL_APPEND, APP_TAG, __func__, __LINE__, fmt, ##args); } while(0)

#else
#define mlogt(fmt, args...)
#define mlogd(fmt, args...)
#define mlogi(fmt, args...)
#define mlogw(fmt, args...)
#define mloge(fmt, args...)
#define mlogp(fmt, args...) 
#define mlogf(fmt, args...)
#define mloga(fmt, args...)

#endif

#ifdef __cplusplus
}
#endif

#endif

