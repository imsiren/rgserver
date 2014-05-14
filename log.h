/*
 * =====================================================================================
 *
 *       Filename:  log.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/14/2014 01:34:00 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __RGLOG_H__
#define __RGLOG_H__

/* Log Level */

#define LOG_DEBUG   0
#define LOG_INFO    1
#define LOG_NOTICE  2
#define LOG_WARNING 3
#define LOG_ERROR   4

#define LOG_MAX_LENGTH  1024

void rgLog(int loglevel, char *fmt, ...);
void rgLogRaw(int loglevel, char *msg);

#endif
