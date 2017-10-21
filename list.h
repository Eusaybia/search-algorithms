/*
    list.h - Interface to a list of strings

    -------------------------------------------------------------
    UNSW COMP2521 17s2 Assignment 2 - Yaggle
    (http://www.cse.unsw.edu.au/~cs2521/17s2/ass/ass02/Ass2.html)
    ass2grp (Yaggle) members:
    - Rahil Agrawal (z5165505) rahil.agrawal@student.unsw.edu.au
    - Dennis Gann (z5164328) d.gann@unsw.edu.au
    - Kongwei Ying (z5014882) k.ying@student.unsw.edu.au
    -------------------------------------------------------------

*/


#ifndef LIST_H
#define LIST_H
#define ALL_NODES -1

#include "headers.h"

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
int cmptfidf(const void *p1, const void *p2);
int cmpPagerankValues(const void *p1, const void *p2);

#endif
