/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/14/2014 12:07:52 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __RGCLIST_H__
#define __RGCLIST_H__

typedef struct listNode{
   struct listNode *prev;
   struct listNode *next; 
   void *value;
}listNode;

typedef struct list{
    listNode *head;
    listNode *tail;
    unsigned long len; 
}list;

list *listCreate(void);
list *listAddNodeTail(list *list, void *value);
list *listAddNodeHead(list *list, void *value);
list *listDelNode(list *list, listNode *node);
list *listIndex(list *list, long index);
void listRelease(list *list);

#endif //__RGCLIST_H
