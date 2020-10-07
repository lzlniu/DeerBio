#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>

typedef struct node {
    int s, e;
    struct node* next;
}node, * list;

list list_init() {
    list head = (list)malloc(sizeof(node));
    if (!head) {
        printf("overflow!");
        exit(0);
    }
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
    struct node* pre, * p;
    int i = 0;
    while (!feof(in)) {
        pre = L->next;
        p = (list)malloc(sizeof(node));
        if (!p) {
            printf("overflow!");
            return;
            //exit(0);
        }
        fscanf_s(in, "%d\t%d", &p->s, &p->e);
        //while (pre->next != NULL && p->s > pre->next->s) pre = pre->next; //第一列升序插入
        if (pre != NULL) {
            if (p->e > pre->e&& p->s == pre->s) {
                //printf("%d>%d,free %d\n", p->e, pre->next->e, p->e);
                p->next = pre->next;
                L->next = p;
                free(pre);
            }
            else if (p->s > pre->s&& p->e == pre->e) {
                free(p);
            }
            else if ((pre->e + range) >= p->s && pre->e <= p->e) {
                pre->e = p->e;
                free(p);
                ++i;
            }
            else if (pre->e > p->e) {
                free(p);
            }
            else {
                p->next = L->next;
                L->next = p;
            }
        } //当第一列相等时只插入最长的，第一列不相等也插入
        else {
            p->next = L->next;
            L->next = p;
        }
    }
    printf("combined %d\n", i);
    fclose(in);
    return;
}

void list_sort(list L) {
    struct node* cur, * p = NULL, * q = NULL;
    cur = L->next;
    int s = 0, curs = 0;
    if (cur == NULL || cur->next == NULL) return;
    while (cur) {
        p = cur->next;
        q = cur->next;
        s = cur->s;
        curs = s;
        while (p) {
            if (curs > p->s) {
                curs = p->s;
                q = p;
            }
            p = p->next;
        }
        if (s != curs) {
            q->s = s;
            cur->s = curs;
            int tempe = cur->e;
            cur->e = q->e;
            q->e = tempe;
        }
        cur = cur->next;
    }
}

void list_write(list L) {
    FILE* out;
    out = fopen("all13combined.txt", "w");
    if (out == NULL) { printf("cann't open output file\n"); return; }
    struct node* p;
    if (L->next != NULL) {
        p = L->next;
        while (p) {
            fprintf(out, "%d\t%d\n", p->s, p->e);
            p = p->next;
        }
    }
    fclose(out);
    printf("successfully write a list to file\n");
    return;
}

void list_destory(list L) {
    struct node* pre, * p;
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

void list_count(list L) {
    int genome = 40117, window = 500, halfwindow, i, s, e, count;
    halfwindow = (int)(window / 2);
    struct node* p;
    FILE* out;
    out = fopen("all13out.txt", "w");
    if (!out) { printf("can't open output file\n"); return; }
    if (L->next != NULL) {
        p = L->next;
        for (i = 0; i <= genome - window; i++) {
            count = 0;
            s = i;
            e = i + window;
            p = L->next;
            while (p != NULL && p->e < s) p = p->next;
            while (p != NULL && p->e <= e) {
                //printf("%d\t%d\t%d\t%d\n", s, e, p->s, p->e); //用于排查bug
                if (p->s >= p->e) count++;
                else if (p->s < p->e) {
                    if (p->s >= s) count = count + (p->e - p->s + 1);
                    else if (p->s < s) count = count + (p->e - s + 1);
                }
                p = p->next;
            }
            if (s + halfwindow <= genome) fprintf(out, "chr1\t%d\t%d\t%d\n", s + halfwindow, s + halfwindow, count);
        }
        if (i > genome - window && i < genome) {
            for (; i <= genome; i++) {
                count = 0;
                s = i;
                e = i + window - genome;
                p = L->next;
                while (p != NULL && p->e <= e) {
                    if (p->s >= p->e) count++;
                    else if (p->s < p->e) {
                        if (p->s >= 0) count = count + (p->e - p->s + 1);
                        else if (p->s < 0) count = count + (p->e - s + 1);
                    }
                    p = p->next;
                }
                while (p != NULL && p->e < s) p = p->next;
                while (p != NULL) {
                    //printf("%d\t%d\t%d\t%d\n", s, e, p->s, p->e); //用于排查bug
                    if (p->s >= p->e) count++;
                    else if (p->s < p->e) {
                        if (p->s >= s) count = count + (p->e - p->s + 1);
                        else if (p->s < s) count = count + (p->e - s + 1);
                    }
                    p = p->next;
                }
                if (s + halfwindow <= genome) fprintf(out, "chr1\t%d\t%d\t%d\n", s + halfwindow, s + halfwindow, count);
                else if (s + halfwindow > genome) fprintf(out, "chr1\t%d\t%d\t%d\n", s + halfwindow - genome, s + halfwindow - genome, count);
            }
        }
    }
    fclose(out);
    return;
}

int main() {
    FILE* in;
    char file_name[64] = { 0 };
    printf("input file name:");
    scanf_s("%s", &file_name, 64);
    list A = list_init();
    //list B = list_init();
    list_readandcombined(file_name, A, 0);
    list_sort(A);
    //list_write(A);
    list_count(A);
    //printf("type all13out.txt:");
    //scanf_s("%s", &file_name, 64);
    //list_readandcombined(file_name, B, 0); //all13out.txt
    //list_sort(B);
    list_destory(A);
    //list_destory(B);
    /*
    int genome = 40117, window = 200, i, s, e, fs, fe, count;
    FILE* out;
    out = fopen("all13out.txt", "w");
    if (!out) { printf("can't open output file\n"); return 0; }
    if (out != NULL) {
        for (i = 0; i <= genome - window; i++) {
            count = 0;
            s = i;
            e = i + window;
            in = fopen("all13combined.txt", "r");
            if (!in) { printf("can't open input file\n"); return 0; }
            fscanf_s(in, "%d\t%d", &fs, &fe);
            while (fs<=s) fscanf_s(in, "%d\t%d", &fs, &fe);
            while (fs >= s && fe <= e) {
                //printf("%d\t%d\t%d\t%d\n", s, e, fs, fe); //用于排查bug
                if (fs >= fe) {
                    count++;
                }
                else if (fs < fe) {
                    count = count + (fe - fs + 1);
                }
                fscanf_s(in, "%d\t%d", &fs, &fe);
            }
            fclose(in);
            fprintf(out, "%d\n", count);
        }
    }
    fclose(out);
    */
	/*
	if (i > genome - window && i < genome) {
		while (i < genome) {
			s = i;
			e = i + window - genome;
			in = fopen("all13.txt", "r");
			fscanf_s(in, "%d\t%d", &fs, &fe);
			while (fs > s&& fe < e) {
				if (fs >= fe) {
					;
				}
				else if (fs < fe) {
					;
				}
				fscanf_s(in, "%d\t%d", &fs, &fe);
			}
			i++;
		}
	}
    */
	return 0;
}
