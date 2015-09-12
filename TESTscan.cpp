#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define sum 8

char doubleword[10] = "!><=";
char singleword[50] = "+-*(){};";
char *keyword[sum] = { "if", "else", "for", "while", "do", "int", "read", "write" };

extern FILE *fin, *fout;
extern char Scanin[300], Scanout[300];
int TESTscan()
{
	char ch, Buff[40];
	int flag = 0, n, line = 1;
	int m = 0;

	printf("Name of  Scanin:  ");
	scanf("%s", Scanin);
	printf("Name of Scanout:  ");
	scanf("%s", Scanout);
	if ((fin = fopen(Scanin, "r")) == NULL)
	{
		printf("\nPro file open error!\n");
		return (1);
	}
	if ((fout = fopen(Scanout, "w")) == NULL)
	{
		printf("\nOutfile open error!\n");
		return (2);
	}

	ch = getc(fin);
	while (ch != EOF)
	{
		m = 0;
		memset(Buff, 0, 40);

		while (ch == ' ' || ch == '\n' || ch == '\t')
		{
			if (ch == '\n')
			{
				line++;
			}
			ch = getc(fin);
		}
		//字母进入
		if (isalpha(ch))
		{
			while (isalpha(ch) || isdigit(ch))
			{
				Buff[m] = ch;
				m++;
				ch = getc(fin);
			}
			n = 0;
			while ((n < sum) && strcmp(Buff, keyword[n]))
			{
				n++;
			}
			if (n < sum)
			{
				fprintf(fout, "%s\t%s %d\n", Buff, Buff,line);
			}
			else
			{
				fprintf(fout, "%s\t%s %d\n", "ID", Buff,line);
			}
		}
		//数字进入
		else if (isdigit(ch))
		{
			if (ch == '0')
			{
				Buff[0] = '0';
				Buff[1] = '\0';
				fprintf(fout, "%s\t%s %d\n", "NUM", Buff,line);
				ch = getc(fin);
			}
			else
			{
				while (isdigit(ch))
				{
					Buff[m] = ch;
					m++;
					ch = getc(fin);
				}
				Buff[m] = '\0';
				fprintf(fout, "%s\t%s %d\n", "NUM", Buff,line);
			}
		}
		else if (strchr(singleword, ch) > 0)
		{
			Buff[0] = ch;
			Buff[1] = '\0';
			ch = getc(fin);
			fprintf(fout, "%s\t%s %d\n", Buff, Buff,line);
		}
		else if (strchr(doubleword, ch) > 0)
		{
			Buff[0] = ch;
			ch = getc(fin);
			if (ch == '=')
			{
				Buff[1] = ch;
				Buff[2] = '\0';
				ch = getc(fin);
				fprintf(fout, "%s\t%s %d\n", Buff, Buff,line);
			}
			else
			{
				Buff[1] = '\0';
				if (Buff[0] == '!')
				{
					printf("Line %d\t%s\t%s\n", line, "ERROR:", Buff);
				}
				else
				{
					fprintf(fout, "%s\t%s %d\n", Buff, Buff,line);
				}
			}
		}
		else if (ch == '/')
		{
			ch = getc(fin);
			if (ch == '*')
			{
				char ch1;
				ch1 = getc(fin);
				while (true)
				{
					if (ch1 == EOF)
					{
						printf("Line %d\t%s\tNote does't match!\n", line, "ERROR:");

						break;
					}
					ch = ch1;
					ch1 = getc(fin);
					if (ch == '*'&&ch1 == '/')
					{
						break;
					}
				}
				ch = getc(fin);
			}
			else
			{
				Buff[0] = '/';
				Buff[1] = '\0';
				fprintf(fout, "%s\t%s %d\n", Buff, Buff,line);
			}
		}
		else
		{
			Buff[0] = ch;
			Buff[1] = '\0';
			ch = getc(fin);
			flag = 3;
			printf("Line %d\t%s\t%s\n", line, "ERROR:", Buff);
		}
	}
	fclose(fin);
	fclose(fout);
	return(flag);
}
