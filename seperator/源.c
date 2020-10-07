#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
author:Zelin Li
date:2020/05/11
utility:generate space between characters
*/

int main() {
	FILE* in,* out;
	char file_name[64] = { 0 }, a[3] = { 0 };
	printf("input file:");
	scanf_s("%s", &file_name, 64);
	in = fopen(file_name, "r");
	if (in == NULL) { printf("cann't open %s\n", file_name); return 0; }
	out = fopen("out.txt", "w");
	if (out == NULL) { printf("cann't open out.txt\n"); return 0; }
	while (!feof(in)) {
		a[0] = fgetc(in);
		if (a[0] != '\n') {
			a[1] = 32;
		}
		fprintf(out, "%s", a);
		memset(a, 0, sizeof(a));
	}
	fclose(in);
	fclose(out);
	return 0;
}
