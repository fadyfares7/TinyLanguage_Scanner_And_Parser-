#include "parser.h"
char token[10];
char string[1000][20];
FILE * pFileIN;
FILE * pFileOut;
int TokenCounter;
int i;
int m,n;
void Scan()
{
char ch;
pFileIN = fopen(InputFile, "r");
TokenCounter=0;
i=0;
while((ch=getc(pFileIN))!=EOF)
{
	if(ch==WhiteSpace||ch=='\n')
	{
		i=0;
		TokenCounter++;
		continue;
	}
	string[TokenCounter][i]=ch;
		i++;
}
fclose(pFileIN);
TokenCounter=0;
program();

//for(m=0;m<100;m++)
//{
//	if(!strcmp(string[m],""))
//		continue;
//		printf("%s\n",string[m]);
//}
}
void match(char x[])
{
	if(!strcmp(x,string[TokenCounter]))
	{
		TokenCounter++;
	}
	else
	{
		void error();
	}
	
}

void error()
{
	printf("error mismatch\n");
	pFileOut=fopen(OutputFile,"a");
	fputs("error mismatch\n", pFileOut);
}
void program()
{
	Stmt_sequence();
	printf("program is found\n");
		pFileOut=fopen(OutputFile,"a");
	fputs("program is found\n", pFileOut);
}
void Stmt_sequence()
{
	Statment();
	while(!strcmp(string[TokenCounter],";"))
	{
		match(";");
		Statment();
	}

}
void Statment()
{
	if(!strcmp(string[TokenCounter],"if"))
		If_Stmt();
	else if(!strcmp(string[TokenCounter],"repeat"))
		Repeat_Stmt();
	else if(!strcmp(string[TokenCounter],"identifier"))
		Assign_Stmt();
	else if(!strcmp(string[TokenCounter],"read"))
		Read_Stmt();
	else if(!strcmp(string[TokenCounter],"write"))
		Write_Stmt();

}
void If_Stmt()
{
	match("if");
	Exp();
	match("then");
	Stmt_sequence();
	if(!strcmp(string[TokenCounter],"else"))
	{
		match("else");
		Statment();
	}
	match("end");
	printf("if Statment is found\n");
	pFileOut=fopen(OutputFile,"a");
	fputs("if Statment is found\n", pFileOut);

}
void Repeat_Stmt()
{
	match("repeat");
	Stmt_sequence();
	match("until");
	Exp();
	printf("Repeat is found\n");
	pFileOut=fopen(OutputFile,"a");
	fputs("Repeat is found\n", pFileOut);
}
void Assign_Stmt()
{
	match("identifier");
	match(":=");
	Exp();
	printf("Assignment is found\n");
	pFileOut=fopen(OutputFile,"a");
	fputs("Assignment is found\n", pFileOut);
}
void Read_Stmt()
{
	match("read");
	match("identifier");
	printf("Read Statment is found\n");
	pFileOut=fopen(OutputFile,"a");
	fputs("Read Statment is found\n", pFileOut);

}
void Write_Stmt()
{
	match("write");
	Exp();
		printf("Write Statment is found\n");
		pFileOut=fopen(OutputFile,"a");
	fputs("Write Statment is found\n", pFileOut);
}
void Exp()
{
	Simple_Exp();
	if((!strcmp(string[TokenCounter],"<"))||(!strcmp(string[TokenCounter],"=")))
	{
		Compare_Op();
		Simple_Exp();
	}
	
}
void Compare_Op()
{
	if(!strcmp(string[TokenCounter],"<"))
	{
		match("<");
	}
	else if(!strcmp(string[TokenCounter],"="))
	{
		match("=");
	}
	printf("Comparison is found\n");
	pFileOut=fopen(OutputFile,"a");
	fputs("Comparison is found\n", pFileOut);
}
void Simple_Exp()
{
	Term();
	while((!strcmp(string[TokenCounter],"+"))||(!strcmp(string[TokenCounter],"-")))
	{
		AddOp();
		Term();
	}

}
void AddOp()
{
	if(!strcmp(string[TokenCounter],"+"))
	{
		match("+");
		printf("Addition operation is found\n");
		pFileOut=fopen(OutputFile,"a");
	fputs("Addition operation is found\n", pFileOut);
	}
	else if(!strcmp(string[TokenCounter],"-"))
	{
		match("-");
		printf("Subtraction operation is found\n");
		pFileOut=fopen(OutputFile,"a");
	fputs("Subtraction operation is found\n", pFileOut);
	}
	

}
void Term()
{
	Factor();
	while(!strcmp(string[TokenCounter],"*"))
	{
		MulOp();
		Factor();
	}
}
void MulOp()
{
	if(!strcmp(string[TokenCounter],"*"))
	{
		match("*");
		printf("Multiplication operation is found\n");
		pFileOut=fopen(OutputFile,"a");
	fputs("Multiplication operation is found\n", pFileOut);
	}
	else if(!strcmp(string[TokenCounter],"/"))
	{
		match("/");
		printf("Division operation is found\n");
		pFileOut=fopen(OutputFile,"a");
	fputs("Division operation is found\n", pFileOut);
	}
}
void Factor()
{
	
	if(!strcmp(string[TokenCounter],"("))
	{
	match("(");
	Exp();
	match(")");
	}
	else if(!strcmp(string[TokenCounter],"number"))
		match("number");
	else if(!strcmp(string[TokenCounter],"identifier"))
		match("identifier");
}
