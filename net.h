/*
 * =====================================================================================
 *
 *       Filename:  net.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/2014 02:11:02 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  斯人 (www.imsiren.com), imsiren@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __RGNET_H__

#define NET_ERROR   -1
#define NET_OK  1

int netTcpConnect(char *addr, int port);

static int netListen(int sockfd, int backlog);
static int netAccept(int sockfd, struct sockaddr *addr, socklen_t *len);


#endif //__RGNET_H__
