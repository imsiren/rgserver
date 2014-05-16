/*
 * =====================================================================================
 *
 *       Filename:  config.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/14/2014 01:29:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "config.h"
#include "log.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

struct rgServer server;
void trimspace(char *result){
    char *p = result;
    while(*p){
        if( !isspace(*p)){
           *result++ = *p; 
        }
        p++;
    }
    *result = '\0';
}
/*
void strsplit(char **desc, char *str, char *delim){
    //char *org = NULL;//[RG_MAX_CONFIG_LEN] ;
    char *result = NULL;
    //memcpy(org, str, strlen(str));
    result = strtok(str, delim);
    while(result != NULL){
       *desc++ = result; 
       result = strtok(NULL, delim);
    }
}
*/
char **strsplit(char *str, char *delim){
    static char *desc[128];
    char *result;
    result = strtok(str, delim);
    int it = 0;
    while(result != NULL){
        desc[it++] = result;
        result = strtok(NULL, delim);
    }
    return desc;
}
/*
* str = [redis]
* char *start = '[';
* char *end   = ']';
* desc = redis
*/
void strparse(char *desc , const char *str, char start, char end){
    int len = strlen(str);
    if(*str == '\0' || *str != start || str[len-1] != end) {
        desc == NULL; 
        return ;
    }
    char *p = NULL;
    while(str++ != NULL){
        if(*str == start) continue;
        if(*str == end) break;
        *desc++ = *str;
    }
    *desc = '\0';
}
struct rgServerTitle *rgServerTitleCreate(char *title){
    assert(title != NULL);
    struct rgServerTitle *tl ;
    tl = malloc(sizeof(struct rgServerTitle)); 
    if(tl == NULL){
        rgLog(LOG_ERROR, "out of memory"); 
    }
    tl->title = title;
    tl->list = listCreate();
    return tl;
}
struct serverNode *serverNodeCreate(){
    struct serverNode *node;
    node = malloc(sizeof(struct serverNode));
    if(node == NULL){
        rgLog(LOG_ERROR, "Out of memory");
    }
    node->count = 0;
    node->port = 0;
    node->online = 0;
    node->hostname = "";
    node->ip = "";
    node->memo = "";
    return node;
}
void initServerConfig(){
    server.configfile= "/etc/rg.cnf";
    server.logfile = "";
    server.loglevel= LOG_ERROR;
    server.port =9833;
    //server.list = listCreate(); 
}
void loadConfig(char *configfile){
    if( !configfile){
       rgLog(LOG_ERROR, "Can not find configfile :%s", configfile);
       exit(-1);
    }
    FILE *fp;
    fp = fopen(configfile, "r");
    if( !fp){
        rgLog(LOG_ERROR, "Can not open configfile %s", configfile);
        exit(-1);
    }
    char buf[RG_LINE_MAX_LEN];
    char org_config[RG_MAX_CONFIG_LEN];
    while(fgets(buf, RG_LINE_MAX_LEN, fp)){
        strcat(buf, "\n");
        strcat(org_config, buf);
    }
    if(fp) fclose(fp);
    loadConfigFromConfigString(org_config);
}
void loadConfigFromConfigString(char *str){
    if(str == NULL) return;
    int iterator = 0;
    char *line;
    //char *arrConfig[RG_MAX_CONFIG_LEN];
    char **arrConfig;
    arrConfig = strsplit( str, "\n"); 
    line = arrConfig[iterator];
    char title[128] ;
    memset(title, 0, sizeof(char)*128);
    struct rgServerTitle *pTitle;
    struct serverNode *srvNode;
    char **arrData;
    int titleTotal = 0;
    while((line = arrConfig[iterator]) != NULL){
        //trimspace(line);
        if(line[0] == '#') goto loop; 
        if(line[0] == '['){
            strparse(title, line, '[', ']');
            if(title  != NULL){
                pTitle = rgServerTitleCreate(title);
                titleTotal ++;
            }
        }
        if(strncmp(line, "port", 4) == 0){
            arrData = strsplit(line, " = ");
            trimspace(arrData[1]);
            server.port = atoi(arrData[1]);
        }
        if(strncmp(line, "server", 6) == 0){
            arrData = strsplit(line, " ");
            srvNode = serverNodeCreate(); 
            srvNode->count = 0;
            srvNode->hostname = arrData[1];
            srvNode->ip = arrData[2];
            srvNode->port = atoi(arrData[3]);
            srvNode->online = atoi(arrData[4]);
            srvNode->memo = arrData[5];
            pTitle->list = listAddNodeTail(pTitle->list, (void*)srvNode);
        }
        server.rgTitle[titleTotal] = pTitle;
        if(strncmp(line, "logfile", 7) == 0){
            arrData = strsplit(line, "="); 
            if(arrData[1] != NULL){
                server.logfile = arrData[1]; 
            }
        }
        if(strncmp(line, "arrData", 8) == 0){
            arrData= strsplit(line, "="); 
            if(arrData[1] != NULL){
                if(strcmp(arrData[1], "LOG_DEBUG") == 0){
                        server.loglevel= LOG_DEBUG;
                }else if(strcmp(arrData[1], "LOG_INFO") == 0){
                        server.loglevel= LOG_INFO;
                }else if(strcmp(arrData[1], "LOG_NOTICE") == 0){
                        server.loglevel= LOG_NOTICE;
                }else if(strcmp(arrData[1], "LOG_WARNING") == 0){
                        server.loglevel= LOG_WARNING;
                }else {
                        server.loglevel= LOG_ERROR;
                }
            }
        }
loop:
        iterator++;
        continue;
    }
}
