#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

#include "log.h"


typedef struct {
	int inited;
	int loglevel;
	int withTime;
	int opts;
	int maxFileSize;
	char path[64];
	FILE *fpLog;
	pthread_mutex_t lock;
}LOG_Ctx_t;

static LOG_Ctx_t gLogCtx = {
	.inited = 0,
	.loglevel = CLLOG_LEVEL_INFO,
	.withTime = 1,
	.opts = CLLOG_OPTS_TO_CONSOLE,
	.maxFileSize = 0,
	.fpLog = NULL,
	.lock = PTHREAD_MUTEX_INITIALIZER,
};

#define LOCKF pthread_mutex_lock(&gLogCtx.lock)
#define UNLOCKF pthread_mutex_unlock(&gLogCtx.lock)


static FILE *_fpLog = NULL; //log file
static int _opts = CLLOG_OPTS_TO_CONSOLE/*default, don't touch*/;


#define BUFFER_SIZE 1024


const char *logColorStr[CLLOG_LEVEL_BUTT] = {
	"",
	LIGHT_PURPLE "FATAL" NONE,
	LIGHT_RED "ERROR" NONE,
	"",
	YELLOW "WARN" NONE,
	LIGHT_BLUE "INFO" NONE,
	BROWN "DEBUG"  NONE,
	"TRACE",
};


const char *logStr[CLLOG_LEVEL_BUTT] = {
	"",
	"FATAL",
	"ERROR",
	"",
	"WARN",
	"INFO",
	"DEBUG",
	"TRACE",
};

static int _copy_file(const char *srcFile, const char *desFile)
{
	if(!srcFile || !desFile)
	{
		printf("%s, input file is null\n", __func__);
		return -1;
	}
	FILE *sfp = fopen(srcFile, "rb");
	if(!sfp)
	{
		printf("open file %s fail \n", srcFile);
		return -1;
	}
	FILE *dfp = fopen(desFile, "a+");
	if(!dfp)
	{
		printf("open file %s, fail \n", srcFile);
		fclose(sfp);
		return -1;
	}
	char buffer[BUFFER_SIZE];
	int readlen = 0, filesize = 0;
	while ((readlen = fread(buffer, 1, BUFFER_SIZE, sfp)) > 0)
	{
		filesize += readlen;
		fwrite(buffer, 1, readlen, dfp);
	}
	fclose(sfp);
	fclose(dfp);
	return filesize;
}


static void getTime(char *strTime)
{
	char sf[16];
	struct timeval tv;
	struct tm _tm;
	gettimeofday(&tv, NULL);
	localtime_r(&tv.tv_sec, &_tm);
	sprintf(sf, "%.03f", tv.tv_usec/1000000.0);
	sprintf(strTime, "%02d-%02d %02d:%02d:%02d.%s", _tm.tm_mon+1, _tm.tm_mday, _tm.tm_hour, _tm.tm_min, _tm.tm_sec, sf+2);
}

static void scrollLog()
{
    if(_fpLog && gLogCtx.maxFileSize)
    {
        int flen = ftell(_fpLog);
        if(flen > gLogCtx.maxFileSize)
        {
            off_t off_w = 0, off_r;
            
            fseek(_fpLog, off_r = (gLogCtx.maxFileSize >> 1), SEEK_SET);

            int rlen;
            char *buff = (char*)malloc(8*1024);
            while( (rlen = fread(buff, 1, 8*1024, _fpLog)) > 0)
            {
                off_r += rlen;
                fseek(_fpLog, off_w, SEEK_SET);
                fwrite(buff, 1, rlen, _fpLog);
                off_w += rlen;
                fseek(_fpLog, off_r, SEEK_SET);
            }
            if(rlen < 0) perror("read");
            free(buff);
            fflush(_fpLog);
            ftruncate(fileno(_fpLog), off_w);
            fseek(_fpLog, 0, SEEK_END);
        }
    }
}

void CLLOG_SetLevel(int lvl) 
{ 
	gLogCtx.loglevel = lvl;
}

int CLLOG_GetLevel(void)
{ 
	return gLogCtx.loglevel ;
}


int CLLOG_GetMaxFileSize() 
{ 
	if(_fpLog) 
		return gLogCtx.maxFileSize; 
	return 0; 
}

void CLLOG_Init(int opts, int logWithTime, const char *path, int max_file_size/*bytes*/)
{
    if(!(opts & CLLOG_OPTS_TO_FILE) && (_opts & CLLOG_OPTS_TO_FILE) )
    {
        LOCKF;
        if(_fpLog) 
        {
            fclose(_fpLog);
            _fpLog = NULL;
        }
        UNLOCKF;
    }

    if((opts & CLLOG_OPTS_TO_FILE)) {
    	int fdLog = -1;
    	if(path) {
			fdLog = open(path, O_RDWR|O_CREAT, 0664);
    	}
        if(fdLog > 0)
        {
			_fpLog = fdopen(fdLog, "r+");
			fseek(_fpLog, 0, SEEK_END);
			strncpy(gLogCtx.path, path, sizeof(gLogCtx.path));
        }
        else
        {
        	perror("CLLOG_Init");
        	printf(RED "CLLOG_Init open file %s failed\n" NONE, path);
        }
    }
    _opts = opts;
    gLogCtx.withTime = logWithTime;
	gLogCtx.maxFileSize = max_file_size;
}

void CLLOG_SetOpts(int opts, const char *path, int max_file_size/*bytes*/)
{
	if(_opts & CLLOG_OPTS_TO_FILE)
	{
        LOCKF;
        if(_fpLog) 
        {
        	fflush(_fpLog);
        	fsync(fileno(_fpLog));
            fclose(_fpLog);
            _fpLog = NULL;
        }
        UNLOCKF;
		if(path && (strcmp(path, gLogCtx.path) != 0))
		{
			_copy_file(gLogCtx.path, path);
			remove(gLogCtx.path);
			strncpy(gLogCtx.path, path, sizeof(gLogCtx.path));
		}
		LOCKF;
		int fdLog = open(path, O_RDWR|O_CREAT, 0664);
		if(fdLog > 0)
		{
			_fpLog = fdopen(fdLog, "r+");
			fseek(_fpLog, 0, SEEK_END);
		}
		else
		{
			perror("CLLOG_SetOpts");
		}
		UNLOCKF;
	}
	_opts = opts;
	gLogCtx.maxFileSize = max_file_size;
}

void CLLOG_FileClose()
{
    if(_fpLog)
    {
    	mlogf("close log file\n\n");
    	LOCKF;
        fflush(_fpLog);
        fsync(fileno(_fpLog));    
        fclose(_fpLog);
        _fpLog = NULL;
        UNLOCKF;
    }
}

void CLLOG_Print(int level, const char *module, const char *func, unsigned int line, const char *format, ...)
{
	if(level > gLogCtx.loglevel) return;

	int i;
	FILE *fpLog = stdout;
	if(_opts == CLLOG_OPTS_OFF) {
		CLLOG_FileClose();
		return ;
	}
	else if(_opts & CLLOG_OPTS_TO_CONSOLE) {
		fpLog = fpLog?fpLog:stdout;
	}
	else
		fpLog = NULL;
	
	FILE *fps[2] = { _fpLog, fpLog };

	for(i=0; i<2; i++)
	{
		FILE *fp = fps[i];
		if(fp)
		{
			if(fp == _fpLog) LOCKF;

			if(!(level & CLLOG_LEVEL_APPEND) && (CLLOG_LEVEL_PRINT != level)) {
				if(gLogCtx.withTime) {
					char strTime[30];
					getTime(strTime);
					if(fp != _fpLog)
						fprintf(fp, "[%s %s-%s]:%s[%u]:", strTime, logColorStr[level], module, func, line);
					else
						fprintf(fp, "[%s %s-%s]:%s[%u]:", strTime, logStr[level], module, func, line);
				}
				else {
					if(fp != _fpLog)
						fprintf(fp, "[%s-%s]:%s:[%u]:", logColorStr[level], module, func, line);
					else
						fprintf(fp, "[%s-%s]:%s:[%u]:", logStr[level], module, func, line);
				}
			}

			va_list va;
			va_start(va, format);
			vfprintf(fp, format, va);
			va_end(va);

			fflush(fp);
			if(fp == _fpLog) {
				scrollLog();
				UNLOCKF;
			}
			// printf("\n");
		}
	}
}


//#define LOGF_MAIN
#ifdef LOGF_MAIN
int main(int argc, char **argv)
{
    CLLOG_Init(CLLOG_OPTS_TO_CONSOLE|CLLOG_OPTS_TO_FILE, 1, "111111.log", 20480);
    int i;
    for(i = 0; i < 3; i++)
    {
    	mlogt("LOG TRACE %d\n", i);
    	mlogd("LOG DEBUG %d\n", i);
    	mlogi("LOG INFO %d\n", i);
    	mlogw("LOG WARNING %d\n", i);
    	mloge("LOG ERROR %d\n", i);
    	mlogf("LOG FATAL %d\n", i);
    	//if(i == 5) CLLOG_Init(CLLOG_OPTS_OFF, 1, "test.log", 20480);
        usleep(1000*1000);
    }
    CLLOG_SetOpts(CLLOG_OPTS_TO_CONSOLE|CLLOG_OPTS_TO_FILE, "222222.log", 20480);
    mlogd("CLLOG_SetOpts:");

	char buffer[16] = "hello world";
	for(i = 0; i < sizeof(buffer); i++)
	{
		mlogi("%s -- %d\r", buffer, i);
		usleep(400*1000);
	}
	mlogp("\n");
    
    CLLOG_FileClose();
    return 0;
}
#endif

