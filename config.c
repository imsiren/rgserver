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

struct rgServer server;

char ** strsplit(const char *str, char *delim){
    char *temp[RG_MAX_CONFIG_LEN];
    char org[RG_MAX_CONFIG_LEN];
    char *result;
    memcpy(org, str, strlen(str));
    result = strtok(org, delim);
    int it = 0;
    while(result != NULL){
       temp = result; 
       result = strtok(NULL, delim);
    }
    return temp;
}
void initServerConfig(){
    server.configfile= "/etc/rg.cnf";
    server.logfile = "";
    server.loglevel = LOG_ERROR;
    server.list = listCreate(); 
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
    char **arrConfig;
    arrConfig = strsplit(str, "\n"); 
}
