#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
int A();
int B();
int C();
int D();
int E();
int TESTparse();
int program();
int statement();
int statement_list();
int expression();
int expression_stat();
int declaration_stat();
int declaration_list();
int if_stat();
int for_stat();
int read_stat();
int write_stat();
int while_stat();
int compound_stat();
int term();
int factor();
int bool_expr();
int additive_expr();
int line;

char ch;
FILE *fp;//用于指向输入文件的指针
extern char Scanout[300];//保存词法分析输出文件名
char token[20], token1[40];//token保存单词符号，token1保存单词值


int TESTparse()
{
	int es = 0;
	if ((fp = fopen(Scanout, "r")) == NULL)
	{
		printf("\n Open %s error !\n", Scanout);
		es = 1;
	}
	printf("=========Result!=========\n\n");

	if (es == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = program();
	}
	fclose(fp);
	return (es);
}


int program()
{
	int es = 0;
	if (strcmp(token, "{"))
	{
		printf("ERROR: Line %d   Lack  {    \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	es = declaration_list();
	if (es > 0)
	{
		return 1;
	}
	es = statement_list();
	if (es > 0)
	{
		return 1;
	}
	if (strcmp(token, "}"))
	{
		printf("ERROR: Line %d   Lack  }    \n", line);
		return 1;
	}

	ch = getc(fp);
	while (ch != EOF)
	{
		if (ch != ' '&&ch != '\n'&&ch != '\t')
		{
			printf("ERROR: Line %d   Programma error!!   \n", line);
			return (es = 1);
		}
		ch = getc(fp);
	}
	return (es);
}


int declaration_list()
{
	int es = 0;
	if (strcmp(token1, "int") == 0)
	{
		es = A();
		return es;
	}
	else
	{
		printf("ERROR: Line %d   Lack int \n", line);
		return 1;
	}
}


int A()
{
	int es = 0;
	if (strcmp(token1, "int") == 0)
	{
		es = declaration_stat();
		if (es > 0)
		{
			return 1;
		}
		es = A();
		return (es);
	}
	else if
		(
		strcmp(token1, "if") == 0 ||
		strcmp(token1, "while") == 0 ||
		strcmp(token1, "for") == 0 ||
		strcmp(token1, "read") == 0 ||
		strcmp(token1, "write") == 0 ||
		strcmp(token1, "{") == 0 ||
		strcmp(token1, ";") == 0 ||
		strcmp(token1, "ID") == 0 ||
		strcmp(token1, "(") == 0||
		strcmp(token1, "NUM") == 0 ||
		strcmp(token1, "}") == 0
		)
	{
		return 0;
	}
	else
	{
		printf("ERROR: Line %d   Lack int||if||while||for||read||write||{||;||ID||(||NUM||} \n", line);
		return 1;
	}
}


int  declaration_stat()
{
	if (strcmp(token, "int"))
	{
		printf("ERROR: Line %d   Lack   int    \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	if (strcmp(token, "ID"))
	{
		printf("ERROR: Line %d   Lack   ID    \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	if (strcmp(token, ";"))
	{
		printf("ERROR: Line %d   Lack   ;   \n", line);
		return  1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	return 0;
}


int statement_list()
{
	int es = 0;
	if (
		strcmp(token, "if") == 0 || strcmp(token, "while") == 0 ||
		strcmp(token, "for") == 0 || strcmp(token, "read") == 0 ||
		strcmp(token, "write") == 0 || strcmp(token, "ID") == 0 ||
		strcmp(token, "{") == 0 || strcmp(token, ";") == 0 ||
		strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0 
		)
	{
		es = B();
		return es;
	}
	else
	{
		printf("ERROR: Line %d   Lack  if||while||for||read||write||{||;||ID||NUM||(   \n", line);
		return 1;
	}
}


int B()
{
	int es = 0;
	if (strcmp(token, "if") == 0 || strcmp(token, "while") == 0 ||
		strcmp(token, "for") == 0 || strcmp(token, "read") == 0 ||
		strcmp(token, "write") == 0 || strcmp(token, "ID") == 0 ||
		strcmp(token, "{") == 0 || strcmp(token, ";") == 0 ||
		strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)
	{
		es = statement();
		if (es > 0)
		{
			return 1;
		}
		es = B();
		return (es);
	}
	else if (strcmp(token, "}") == 0)
	{
		return 0;
	}
	else
	{
		printf("ERROR: Line %d   Lack  if||while||for||read||write||{||;||ID||NUM||( ||}  \n", line);
		return 1;
	}
}

int statement()
{
	int es = 0;
	if (es == 0 && strcmp(token, "if") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = if_stat();
	}
	else if (es == 0 && strcmp(token, "while") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = while_stat();
	}
	else if (es == 0 && strcmp(token, "for") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = for_stat();
	}
	else if (es == 0 && strcmp(token, "read") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = read_stat();
	}
	else if (es == 0 && strcmp(token, "write") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = write_stat();
	}
	else if (es == 0 && strcmp(token, "{") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = compound_stat();						//复合语句
	}
	else if (es == 0 && strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0 || strcmp(token, ";") == 0)
	{
		es = expression_stat();
	}
	else
	{
		printf("ERROR: Line %d   Lack  if||while||for||read||write||{||;||ID||NUM||(   \n", line);
		return 1;
	}
	return (es);
}


int if_stat()
{
	int es = 0;
	if (strcmp(token, "("))
	{
		printf("ERROR: Line %d   Lack  ( \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//	printf("%s	%s\n", token, token1);
	es = expression();
	if (es > 0)
	{
		return 1;
	}
	if (strcmp(token, ")"))
	{
		printf("ERROR: Line %d   Lack  ) \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//	printf("%s	%s\n", token, token1);
	es = statement();
	if (es > 0)
	{
		return 1;
	}
	if (strcmp(token, "else") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		//		printf("%s	%s\n", token, token1);
		es = statement();
	}
	return (es);
}


int while_stat()
{
	int es = 0;
	if (strcmp(token, "("))
	{
		printf("ERROR: Line %d   Lack   (   \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//	printf("%s	%s\n", token, token1);
	es = expression();
	if (es > 0)
	{
		return 1;
	}
	if (strcmp(token, ")"))
	{
		printf("ERROR: Line %d   Lack   )   \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//	printf("%s	%s\n", token, token1);
	es = statement();
	return (es);
}


int for_stat()
{
	int es = 0;
	if (strcmp(token, "("))
	{
		printf("ERROR: Line %d   Lack   (   \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//printf("%s	%s\n", token, token1);
	es = expression();
	if (es > 0)
	{
		return 1;
	}
	if (strcmp(token, ";"))
	{
		printf("ERROR: Line %d   Lack   ;   \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//	printf("%s	%s\n", token, token1);
	es = expression();
	if (es > 0)
	{
		return 1;
	}
	if (strcmp(token, ";"))
	{
		printf("ERROR: Line %d   Lack   ;  \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//printf("%s	%s\n", token, token1);
	es = expression();
	if (es > 0)
	{
		return 1;
	}
	if (strcmp(token, ")"))
	{
		printf("ERROR: Line %d   Lack   )  \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//	printf("%s	%s\n", token, token1);
	es = statement();
	return (es);
}


int write_stat()
{
	int es = 0;
	es = expression();
	if (es > 0)
	{
		return 1;
	}
	if (strcmp(token, ";"))
	{
		printf("ERROR: Line %d   Lack   ;  \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//	printf("%s	%s\n", token, token1);
	return 0;
}


int read_stat()
{
	int es = 0;
	if (strcmp(token, "ID"))
	{
		printf("ERROR: Line %d   Lack   ID  \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//	printf("%s	%s\n", token, token1);
	if (strcmp(token, ";"))
	{
		printf("ERROR: Line %d   Lack   ;   \n", line);
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
	//	printf("%s	%s\n", token, token1);
	return 0;
}


int compound_stat()
{
	int es = 0;
	es = statement_list();
	if (es > 0)
	{
		return 1;
	}
	if (strcmp(token, "}"))
	{
		return 1;
	}
	fscanf(fp, "%s%s%d\n", &token, &token1, &line);
//	printf("%s	%s %d\n", token, token1, line);

	return 0;
}


int expression_stat()
{
	int es = 0;
	if (strcmp(token, ";") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		return 0;
	}
	else if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)
	{
		es = expression();
		if (es > 0)
		{
			return 1;
		}
		if (strcmp(token, ";") == 0)
		{
			fscanf(fp, "%s%s%d\n", &token, &token1, &line);
			return 0;
		}
		else
		{
			printf("ERROR: Line %d   Lack   ;   \n", line);
			return 1;
		}
	}
	else
	{
		printf("ERROR: Line %d   Lack   ;||ID||NUM||(   \n", line);
	}
	return 0;
}


int expression()
{
	int es = 0, fileadd;
	char token2[20], token3[40];
	if (strcmp(token, "ID") == 0)
	{
		fileadd = ftell(fp);//记住当前文件位置
		fscanf(fp, "%s%s%d\n", &token2, &token3, &line);

		if (strcmp(token2, "=") == 0)
		{
			fscanf(fp, "%s%s%d\n", &token, &token1, &line);
			es = bool_expr();
			if (es > 0)
			{
				return 1;
			}
		}
		else
		{
			fseek(fp, fileadd, 0);//若非‘=’，则文件指针回到'='前的标识符
			es = bool_expr();
			if (es > 0)
			{
				return 1;
			}
		}
	}
	else
	{
		es = bool_expr();
		if (es > 0)
		{
			return 1;
		}
	}
	return 0;
}


int bool_expr()
{
	int es = 0;
	if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "("))
	{
		es = additive_expr();
		if (es > 0)
		{
			return 1;
		}
		es = C();
		return (es);
	}
	else
	{
		printf("ERROR: Line %d   Lack  ID||NUM||(    \n", line);
		return 1;
	}
}


int C()
{
	int es = 0;
	if (
		strcmp(token, ">") == 0 ||
		strcmp(token, ">=") == 0 ||
		strcmp(token, "<") == 0 ||
		strcmp(token, "<=") == 0 ||
		strcmp(token, "==") == 0 ||
		strcmp(token, "!=") == 0
		)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = additive_expr();
		if (es > 0)
		{
			return 1;
		}
		return 0;
	}
	else if (strcmp(token, ";") == 0 || strcmp(token, ")") == 0)
	{
		return 0;
	}
	else
	{
		printf("ERROR: Line %d   Lack )||>||<||>=||<==||==||!=||;    \n", line);
		return 1;
	}
}


int additive_expr()
{
	int es = 0;
	if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)
	{
		es = term();
		if (es > 0)
		{
			return 1;
		}
		es = D();
		return (es);
	}
	else
	{
		printf("ERROR: Line %d   Lack  ID||NUM||(   \n", line);
		return 1;
	}
}


int D()
{
	int es = 0;
	if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = term();
		if (es > 0)
		{
			return 1;
		}
		es = D();
		return (es);
	}
	else if
		(
		strcmp(token, ";") == 0 || strcmp(token, ")") == 0 ||
		strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 ||
		strcmp(token, "<") == 0 || strcmp(token, "<=") == 0 ||
		strcmp(token, "==") == 0 || strcmp(token, "!=") == 0
		)
	{
		return 0;
	}
	else
	{
		printf("ERROR: Line %d   Lack   +||-||;||)||<||>||<=||>=||==||!=    \n", line);
		return 1;
	}
}


int term()
{
	int es = 0;
	if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0 || strcmp(token, "(") == 0)
	{
		es = factor();
		if (es > 0)
		{
			return 1;
		}
		es = E();
		return (es);
	}
	else
	{
		printf("ERROR: Line %d   Lack  ID||NUM||(   \n", line);
		return 1;
	}
}


int E()
{
	int es = 0;
	if (strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = factor();
		if (es > 0)
		{
			return 1;
		}
		es = E();
		return (es);
	}
	else if
		(
		strcmp(token, ";") == 0 || strcmp(token, ")") == 0 ||
		strcmp(token, "+") == 0 || strcmp(token, "-") == 0 ||
		strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 ||
		strcmp(token, "<") == 0 || strcmp(token, "<=") == 0 ||
		strcmp(token, "==") == 0 || strcmp(token, "!=") == 0
		)
	{
		return 0;
	}
	else
	{
		printf("ERROR: Line %d   Lack   *||/||;||)||>||<||==||!=||>=||<=  \n", line);
		return 1;
	}
}


int factor()
{
	int es = 0;
	if (strcmp(token, "(") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		es = expression();
		if (es > 0)
		{
			return 1;
		}
		if (strcmp(token, ")"))
		{
			printf("ERROR: Line %d   )   \n", line);
			return 1;
		}
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		return 0;
	}
	else if (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0)
	{
		fscanf(fp, "%s%s%d\n", &token, &token1, &line);
		return 0;
	}
	else
	{
		printf("ERROR: Line %d   ( || ID || NUM    \n", line);
		return 1;
	}
}