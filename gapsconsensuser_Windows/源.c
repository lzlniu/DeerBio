#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
author:Zelin Li
date:2020/05/10
platform:Linux
utility:combined the gaps
usage:./gapconsensuser.out input.txt
*/

typedef struct node {
    int s, e, len;
    struct node* next;
}node, * list;

list list_init() {
    list head = (list)malloc(sizeof(node));
    if (!head) {
        printf("overflow!");
        exit(0);
    }
    head->len = 0;
    head->next = NULL;
    //printf("successfully init a list\n");
    return head;
}

void list_readandcombined(char file_name[], list L, int range) {
    FILE* in;
    in = fopen(file_name, "r");
    if (in == NULL) {
        printf("cann't open %s\n", file_name);
        return;
    }
    node* pre, * p;
    L->len = 0; int i=0;
    while (!feof(in)) {
        pre = L->next;
        p = (list)malloc(sizeof(node));
        if (!p) {
            printf("overflow!");
            return;
            //exit(0);
        }
        fscanf_s(in, "%d\t%d\t%d", &p->s, &p->e, &p->len);
        //while (pre->next != NULL && p->s > pre->next->s) pre = pre->next; //第一列升序插入
        if (pre != NULL) {
            if (p->e > pre->e && p->s == pre->s) {
                //printf("%d>%d,free %d\n", p->e, pre->next->e, p->e);
                p->next = pre->next;
                L->next = p;
                free(pre);
            }
            else if (p->s > pre->s && p->e == pre->e) {
                free(p);
            }
            else if ((pre->e + range) >= p->s && pre->e <= p->e) {
                pre->e = p->e;
                pre->len = p->e - pre->s + 1;
                free(p);
                ++i;
            }
            else if (pre->e > p->e) {
                free(p);
            }
            else {
                p->next = L->next;
                L->next = p;
                ++L->len; //input line count
            }
        } //当第一列相等时只插入最长的，第一列不相等也插入
        else {
            p->next = L->next;
            L->next = p;
            ++L->len; //input line count
        }
    }
    printf("combined %d\n", i);
    fclose(in);
    return;
}

void list_write(list L) {
    FILE* out;
    out = fopen("consensusgaps.txt", "w");
    if (out == NULL) { printf("cann't open output file\n"); return; }
    node* p;
    if (L->next != NULL) {
        p = L->next;
        while (p) {
            fprintf(out, "%d\t%d\t%d\n", p->s, p->e, p->len);
            p = p->next;
        }
    }
    fclose(out);
    printf("successfully write a list to file\n");
    return;
}

void destory(list L) {
    node* pre, * p;
    if (L->next != NULL) {
        pre = L->next;
        L->next = NULL;
        while (pre) {
            p = pre->next;
            free(pre);
            pre = p;
        }
    }
    free(L);
    printf("successfully destory a list\n");
    return;
}

void select(list L, int i) {
    struct node* p;
    if (L->next != NULL) {
        p = L->next;
        if (i <= L->len && i > 0) {
            for (int j = 1; j < i; j++) p = p->next;
            printf("%d\t%d\t%d\n", p->s, p->e, p->len);
        }
        else printf("input number %d is out of range.\n", i);
    }
    return;
}

int chnum(char str[]) {
    int i, num = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + str[i] - '0';
        }
    }
    return num;
}

int main(int argc, char* argv[]) {
    list A = list_init();
    printf("range is %d\n", chnum(argv[2]));
    list_readandcombined(argv[1], A, chnum(argv[2]));
    
    for (int i = 1; i <= A->len; i++) {
        select(A, i);
    }
    
    printf("list length:%d\n", A->len);
    list_write(A);
    destory(A);
    return 0;
}
