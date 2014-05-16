/*
 * =====================================================================================
 *
 *       Filename:  list.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/14/2014 12:18:16 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "list.h"
#include <stdlib.h>

list *listCreate(void){
    list *list;
    if((list = malloc(sizeof(list))) == NULL){
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL; 
    list->len = 0;
    return list;
}

list *listAddNodeHead(list *list,void *value ){
    listNode *node = NULL;
    if(node == (listNode*)malloc(sizeof(listNode))){
        return NULL;
    }
    node->value = value;
    if(list->len == 0){
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    }else{
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->len++;
    return list;
}

list *listAddNodeTail(list *list, void *value){
    listNode *node;
    if((node = (listNode*)malloc(sizeof(node))) ==NULL)
        return NULL;
    node->value = (void*)value;
    if(list->len == 0){
        list->head = list->tail = node; 
        node->prev = node->next = NULL;
    }else{
        node->prev = list->tail;
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
    }
    list->len++;
    return list;
}

list *listDelNode(list *list, listNode *node){
    if(node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;
    if(node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;
    free(node);
    return list;
}

list *listIndex(list *list, long index){
    listNode *node;
    if(index<0){
        index = (-index)-1;
        node = list->head;
        while(index-- && node) node = node->prev;
    }else{
        node = list->tail;
        while(index-- && node) node = node->next; 
    }
    return list;
}

void listRelease(list *list){
    unsigned long len;
    listNode *current, *next; 
    current = list->head;
    len = list->len;
    while(len--){
        next = current->next;
        free(current);
        current = next;
    } 
    free(list);
}
