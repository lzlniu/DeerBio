#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
//#define NAME_LENGTH 60
//#define MAX_SEQ_READ_LENGTH 4096000

/*
author:Zelin Li
date:2020/05/09
platform:Linux
utility:extract gaps position from multi fasta file(already complete the global alignment) and forming multiple circos configuration ".txt".
usage:./gapfinder.out slimfastaformat.txt (like: >ATGCATTTACAAG.....\n>ATGCATTAACGAG......\n......)
*/

/*
typedef struct fasta {
    char seq_name[NAME_LENGTH];
    char seq[MAX_SEQ_READ_LENGTH];
    struct fasta* next;
}fasta, *fasta_list;

fasta_list fasta_Init() {
    fasta_list L = (fasta_list)malloc(sizeof(fasta));
    if (!L) { 
        printf("overflow!");
        //exit(OVERFLOW);
    }
    L->next = NULL;
    //printf("successfully init a fasta list\n");
    return L;
}

void fasta_read(char file_name[], fasta_list L) {
    int i = 0;
    struct fasta* pre, *p;
    FILE* in;
    in = fopen(file_name, "r");
    if (in == NULL) { printf("cann't open %s!\n", file_name); return; }
    while (!feof(in)) {
        ++i;
        pre = L;
        p = (fasta_list)malloc(sizeof(fasta));
        if (!p) { 
            printf("overflow!\n");
            return; 
            //exit(OVERFLOW);
        }
        fscanf(in, ">%s,%s", &p->seq_name, &p->seq);
        printf("input %s\n", p->seq_name);
        p->next = pre->next; pre->next = p; //fasta格式序列不断插入
    }
    printf("successfully struct the aligned_multi_fasta from %s including %d fasta\n",file_name, i);
    fclose(in);
    return;
}

void fasta_destory(fasta_list L) {
    fasta* pre, * p;
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
    //printf("successfully destory a fasta list\n");
    return;
}

int main(int argc, char *argv[]) {
    fasta_list aligned_multi_fasta = fasta_Init();
    printf("gapfinder alpha1.0\n");
    fasta_read(argv[1], aligned_multi_fasta);
    fasta_destory(aligned_multi_fasta);
    return 0;
}
*/

int main(int argc, char* argv[]) {
    FILE* in, * out;
    in = fopen(argv[1],"r");
    if (in == NULL) { printf("cann't open %s!\n", argv[1]); return 0; }
    int i = 0, j=0, len=0, num=0;
    char nucl, s[8];
    while (!feof(in)) {
        nucl = fgetc(in); ++i;
        if (nucl == '>' && num > 0) {
            sprintf(s, "%d.txt", ++num);
            out = fopen(s, "w");
            i = 0;
        }
        else if (nucl == '>' && num <= 0) {
            sprintf(s, "%d.txt", num=1);
            out = fopen(s, "w");
            i = 0;
        }
        if (nucl == '-') {
            if (len <= 0) len=1;
            else if (len > 0 && i == j + 1) {
                ++len;
                j = i;
                continue;
            }
            j = i;
        }
        if (nucl != '-' && len > 1) {
            fprintf(out, "chr1\t%d\t%d\tfill_color=yellow\n", i - len, j);
            len = 0;
        }
        else if (nucl != '-' && len == 1) {
            fprintf(out, "chr1\t%d\t%d\tfill_color=yellow\n", j, j);
            len = 0;
        }
    }
    fclose(in);
    return 1;
}
