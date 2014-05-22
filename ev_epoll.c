/*
 * =====================================================================================
 *
 *       Filename:  ev_epoll.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2014 11:03:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  斯人 (www.imsiren.com), imsiren@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "event.h"
#include <sys/epoll.h>
typedef struct eventState{
    int epfd;
    struct epoll_event *events;
}eventState;

int apiCreateEvent(eventLoop *el){
    eventState *state;
    if((state = malloc(sizeof(eventState))) == NULL) return -1;
    state->epfd = epoll_create(1024);
    state->events = malloc(sizeof(struct epoll_event*) * el->eventSize);
    if( !state->events){
        free(state->events);
        free(state);
        return -1;
    }
    el->apidata = (void*)state;
    return 0;
}
int apiEventWait(eventLoop *el){
    eventState *state = (eventState*)el->apidata;
    int numevents, j;
    numevents = epoll_wait(state->epfd,state->events,el->eventSize,100);
    return numevents;
}
static int apiAddEvent(eveltLopp *el, int fd, int mask){
    
}
