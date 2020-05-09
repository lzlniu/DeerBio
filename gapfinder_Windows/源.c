#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>

/*
author:Zelin Li
date:2020/05/09
platform:Windows
utility:extract gaps position from multi fasta file(already complete the global alignment) and forming multiple circos configuration ".txt".
usage:click gapfinder_Windows.exe and type the input file name such as slimfastaformat.txt (inside it like: >ATGCATTTACAAG.....\n>ATGCATTAACGAG......\n......)
*/

int main() {
    FILE* in, * out;
    char infile[64] = { 0 };
    printf("input slim fasta file name:");
    scanf_s("%s", infile, 64);
    in = fopen(infile, "r");
    if (in == NULL) { printf("cann't open %s!\n", infile); return 0; }
    int i = 0, j = 0, len = 0, num = 0;
    char nucl, s[8];
    while (!feof(in)) {
        nucl = fgetc(in); ++i;
        if (nucl == '>' && num > 0) {
            sprintf(s, "%d.txt", ++num);
            out = fopen(s, "w");
            if (out == NULL) { printf("cann't open %s!\n", s); return 0; }
            i = 0;
        }
        else if (nucl == '>' && num <= 0) {
            sprintf(s, "%d.txt", num = 1);
            out = fopen(s, "w");
            if (out == NULL) { printf("cann't open %s!\n", s); return 0; }
            i = 0;
        }
        if (nucl == '-') {
            if (len <= 0) len = 1;
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
    return 0;
}
