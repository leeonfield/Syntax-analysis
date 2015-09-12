#include<stdio.h>
#include<ctype.h>
extern int TESTscan();
extern int TESTparse();
char Scanin[300], Scanout[300];
FILE *fin, *fout;
void main()
{
	int es = 0;
	es = TESTscan();
	if (es > 0)
	{
		printf("Morphology analysis error! \n\n");
	}
	else
	{
		printf("Morphology analysis succeed! \n\n");
	}
	if (es == 0)
	{
		es = TESTparse();
		if (es == 0)
		{
			printf("Grammar analysis succeed!\n\n");
		}
		else
		{
			printf("Grammar analysis error!\n\n");
		}
	}
}