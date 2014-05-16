/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/14/2014 01:58:27 AM
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
#include <string.h>
#include <sys/types.h>

#include "list.h"
#include "log.h"
#include "config.h"

extern struct rgServer server;

void usage(){
    fprintf(stderr, ""
        "-c(--config) configfile\n"
        "-h(--help) help\n" 
        "\r\n"
    );
    exit(0);
}
void version(){
    exit(0);
}
void rgMonitor(){

}
int main(int argc, char **argv){
    initServerConfig();
    if(argc<2){
        usage();
    }
    if(strcmp(argv[1], "-v") ==0 || strcmp(argv[1], "--version") == 0){
        version();
    } 
    if(strcmp(argv[1], "-h") ==0 || strcmp(argv[1], "--help") == 0){
        usage();
    } 
    if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--config") == 0){
        if(argv[2] == NULL){
            usage();
        }
        server.configfile = argv[2];
    }
    loadConfig(server.configfile);
    while(1);
}
