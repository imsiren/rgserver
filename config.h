/*
 * =====================================================================================
 *
 *       Filename:  config.h
 *
 *    Description:  G
 *
 *        Version:  1.0
 *        Created:  05/14/2014 01:25:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __RGCONFIG_H__
#define __RGCONFIG_H__
#include "list.h"

#define RG_LINE_MAX_LEN 1024
#define RG_MAX_CONFIG_LEN   1024<<1

struct rgServer{
    char *logfile;
    char *configfile;
    int loglevel;
    int port;
    int sockfd;
    struct sockaddr* addr;
    socklen_t   *len;
    struct rgServerTitle *rgTitle[10];    
};
struct rgServerTitle{
    char *title;
    list *list;
};

struct serverNode{
    int count;/*client connected num*/
    int port;
    int online;
    char *hostname;
    char *ip;
    char *memo;
};

void initServerConfig();
struct serverNode *serverNodeCreate();
struct rgServerTitle *rgServerTitleCreate(char *title);
void loadConfig(char *filename);
void loadConfigFromConfigString(char *str);
#endif //__RGCONFIG_H__
