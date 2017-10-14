// list.h - Interface to a list of strings
// Written by Kongwei Ying, September 2017

#ifndef LIST_H
#define LIST_H
#define ALL_NODES -1

#include <stdio.h>
#define MAX_CHAR 256

typedef struct ListRep *List;

List newList();
void dropList(List l);
int isEmpty(List l);
void appendList(List l, char *str, double val, int terms);
int deleteFromList(List l, char *str);
int cmpNum(const void *p1, const void *p2);
int cmpStr(const void *p1, const void *p2);
int cmpPagerank(const void *p1, const void *p2);
void sortList(List l, int (*compar)(const void *, const void *));
void showList(List l, FILE *fp, char delimiter, int *nNodes);
void addTfIdf(List l, char *str, double val, int terms);
void showTfIdfList(List l, FILE *fp, int nUrls);
void listToArray(List l, char sortedlist[][MAX_CHAR]);
#endif
