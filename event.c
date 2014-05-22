/*
 * =====================================================================================
 *
 *       Filename:  event.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2014 10:56:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  斯人 (www.imsiren.com), imsiren@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "event.h"
#include "ev_epoll.c"
#include <errno.h>
eventLoop *createEventLoop(int size){
    eventLoop *el;
    if((eL = malloc(sizeof(eventLoop))) == NULL) goto err;
    el->maxfd = -1; 
    el->eventSize = size;
    if(apiCreateEvent(el) == -1) goto err; 
    return eL;

err:
    if(el){
        free(el);
    }
    return NULL;
}

int processEvents(eventLoop *el){
    int numevents, j;
    numevents = apiEventWait(el);
    struct epoll_events *events = el->events;
    for(j = 0;j<numevents;j++){
    }
}
