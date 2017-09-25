// list.h - Interface to a list of strings
// Written by Kongwei Ying, September 2017

#ifndef LIST_H
#define LIST_H

typedef struct ListRep *List;

List newList();
void dropList(List l);
int isEmpty(List l);
void appendList(List l, char *str);
int deleteFromList(List l, char *str);
void sortList(List l);
void showList(List l);

#endif