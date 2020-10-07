#include <stdio.h>
#include <stdlib.h>

/*
author:Zelin Li
date:2020/05/09
platform:Linux
utility:combined the gaps
usage:./gapconsensuser.out input.txt
*/

typedef struct node {
    int s, e, len;
    struct node* next;
}node, *list;

list list_init() {
    list head = (list)malloc(sizeof(node));
    if (!head) {
        printf("overflow!");
        //exit(OVERFLOW);
    }
    head->len = 0;
    head->next = NULL;
    //printf("successfully init a list\n");
    return head;
}

void list_read(char file_name[], list L) {
    FILE* in;
    in = fopen(file_name, "r");
    if (in == NULL) {
        printf("cann't open %s\n", file_name);
        return;
    }
    node* pre, * p;
    L->len = 0;
    while (!feof(in)) {
        ++L->len; //input line count
        pre = L;
        p = (list)malloc(sizeof(node));
        fscanf(in,"%d\t%d\t%d",&p->s,&p->e,&p->len);
        while (pre->next != NULL && p->s > pre->next->s) pre = pre->next;
        p->next = pre->next;
        pre->next = p;
    }
    fclose(in);
    return;
}

void destory(list L) {
    node* pre, * p;
    if (L->next != NULL) {
        pre = L->next;
        L->next = NULL;
        while(pre) {
            p = pre->next;
            free(pre);
            pre = p;
        }
    }
    free(L);
    //printf("successfully destory a polynominal LinkList.\n");
    return;
}

void select(list L, int i) {
    node* p;
    if (L->next != NULL) {
        p = L->next;
    }
    if (i <= L->len && i > 0) {
        for (int j = 1; j < i; j++) p = p->next;
        printf("%d\t%d\t%d\n", p->s, p->e, p->len);
    }
    else printf("input number %d is out of range.\n", i);
    return;
}

list list_consensus(list L) {
    node* pre, * p;
    if (L->next != NULL) {
        pre = L;
        p = L->next;
    }
    while (pre) {
        if ((pre->e + 200) >= p->s) {
            pre->e = p->e;
            pre->next = p->next;
            free(p);
            pre = pre->next;
            p = pre->next;
        }
        else {
            pre = pre->next;
            p = p->next;
        }
    }
    return L;
}

int main(int argc, char* argv[]) {
    list A = list_init();
    list_read(argv[1], A);
    printf("list length:%d\n", A->len);
    for (int i = 1; i <= A->len ; i++) {
        select(A, i);
    }
    A = list_consensus(A);
    for (int i = 1; i <= A->len; i++) {
        select(A, i);
    }
    destory(A);
    return 0;
}
