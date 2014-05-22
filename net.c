/*
 * =====================================================================================
 *
 *       Filename:  net.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/16/2014 02:10:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  斯人 (www.imsiren.com), imsiren@163.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "net.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>

static int netTcpGenericConnect(char *addr, int port, struct sockaddr *addr, socklen_t *addrlen){
    int s = NET_ERROR, rv;
    struct addrinfo hints, *serverinfo, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((rv = getaddrinfo(addr, port, &hints, &serverinfo )) != 0){
        return NET_ERROR;
    }
    for(p = serverinfo; p != NULL; p = p->ai_next){
        s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(s == -1){
            continue;
        }
        rv = bind(s, p->ai_addr, p->ai_addrlen);
        if(rv == 0){
            break;
        }
        addr = p->ai_addr;
        addr_len = p->addrlen;
        close(s);
    }
    freeaddrinfo(serverinfo);
    return s;
}
static inline int setNonBlocking(int sockfd){
    return fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFL,0)|O_NONBLOCK);
}
static int netListen(int sockfd, int backlog){
    int rv = listen(sockfd, backlog);
    if(rv != 0){
        return NET_ERROR; 
    }
    return NET_OK;
}
static int netTcpConnect(char *addr, int port, struct sockaddr *addr, socklen_t *len){
    int sockfd;
    sockfd = netTcpGenericConnect(addr, port, addr, len);
    if(sockfd == NET_ERROR)
        return NULL;  
    setNonBlocking(sockfd);
    return sockfd;
}
static int netAccept(int sockfd, struct sockaddr *client_addr, socklen_t *addr_len){
    int clientfd;
    while(1){
        clientfd = accept(sockfd,client_addr,addr_len)
        if(clientfd == -1){
            if(errno == EINTR){
                continue;
            }else{
                return NET_ERROR;
            }
        }
        break;     
    }
    return clientfd;
    
}
int netRead(int fd, char *buf, int count){
    int nread, totlen = 0;
    while(1){
        nread = read(fd, buf, count-totlen);
        if(nread == 0) return totlen;
        if(nread == -1) return NET_ERROR;
        buf += nread;
    }
    return nread;
}
