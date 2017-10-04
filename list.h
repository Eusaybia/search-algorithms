// list.h - Interface to a list of strings
// Written by Kongwei Ying, September 2017

#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct ListRep *List;

List newList();
void dropList(List l);
int isEmpty(List l);
void appendList(List l, char *str);
int deleteFromList(List l, char *str);
int cmpStr(const void *p1, const void *p2);
int cmpPagerank(const void *p1, const void *p2);
void sortList(List l, int (*compar)(const void *, const void *));
void showList(List l, FILE *fp, char delimiter);

#endif