/*
 * =====================================================================================
 *
 *       Filename:  event.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2014 10:40:46 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  斯人 (www.imsiren.com), imsiren@163.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __RGEVENT_H__
#define __RGEVENT_H__

#define EV_NONE     0
#define EV_READABLE     1
#define EV_WRITABLE    2

typedef struct eventLoop{
    int maxfd;
    int eventSize;
    void *apidata;
}eventLoop;

eventLoop *createEventLoop(int size);

#endif
