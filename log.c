/*
 * =====================================================================================
 *
 *       Filename:  log.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/14/2014 01:37:13 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include "log.h"
#include "config.h"
extern struct rgServer server;
void rgLog(int loglevel, char *fmt, ...){
    char buf[LOG_MAX_LENGTH];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(fmt), fmt, ap);
    va_end(ap);
    
    rgLogRaw(loglevel, buf);
}

void rgLogRaw(int loglevel, char *msg){
    const int loglevelMap[] = {LOG_DEBUG, LOG_INFO, LOG_NOTICE, LOG_WARNING, LOG_ERROR};
    char *c[] = {"DEBUG", "INFO", "NOTICE", "WARNING", "ERROR"}; 
    int log_to_out = server.logfile == NULL;
    FILE *fp;
    fp = log_to_out ? stdout : fopen(server.logfile, "w");
    if( !fp){
        return ;
    }
    char time[LOG_MAX_LENGTH];
    struct timeval tv;    
    gettimeofday(&tv, NULL);
    strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", localtime(&tv.tv_sec));
    fprintf(fp, "RgServer:[%d] %s %s %s\n",(int)getpid(), time, c[loglevel], msg);
    if(log_to_out)
        fclose(fp);
    fflush(fp);
}
