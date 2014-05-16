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
#include <sys/types.h>
#include <sys/socket.h>

#define NET_ERROR   -1
#define NET_OK  1

int netTcpConnect(char *addr, int port);


#endif //__RGNET_H__
