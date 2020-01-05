#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 64

/*
Author:Zelin Li
Date:2020-01-05
utility:extract the AGCT from a file.
usage:click to open the transfasta.exe, then type in the input and output files' FilePath. 
*/

int main()
{
	FILE * in, * out;
	char nucl, infile[MAX_LENGTH] = { 0 }, outfile[MAX_LENGTH] = { 0 };
	int i = 0;
	printf("input file name:");
	scanf("%s", infile, MAX_LENGTH);
	printf("output file name:");
	scanf("%s", outfile, MAX_LENGTH);
	if ((in = fopen(infile, "r")) == NULL)
	{
		printf("cann't open this file\n");
		exit(0);
	}
	if ((out = fopen(outfile, "w")) == NULL)
	{
		printf("cann't open this file\n");
		exit(0);
	}
	while (!feof(in))
	{
		nucl = fgetc(in);
		if (nucl == 'A' || nucl ==  'C' || nucl ==  'G' || nucl ==  'T')
		{
			fputc(nucl, out);
		}
		i = i++;
	}
	putchar(10);
	printf("total count: %d\n",i);
	fclose(in);
	fclose(out);
	return 0;
}
