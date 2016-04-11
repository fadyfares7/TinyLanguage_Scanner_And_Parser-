#include "scanner.h"

static unsigned char State=State_Start;
static unsigned char NextState;
static char token[10];
static unsigned char tokenCounter=0;
static unsigned char otherChar='\0';
static unsigned char NumFlag=0;
static unsigned char LetterFlag=0;
FILE * pFileIN;
FILE * pFileOut;
#define NumOfResWords 8
#define NumOfSymbols 10
const char ReservedWords[][10]={
	{"if"},
	{"then"},
	{"else"},
	{"end"},
	{"repeat"},
	{"until"},
	{"read"},
	{"write"}
};


const char Symbols[][3]={
	{"+"},
	{"-"},
	{"*"},
	{"/"},
	{"="},
	{"<"},
	{"("},
	{")"},
	{";"},
	{":="}
};

void scan(void)
{

char ch;
pFileIN = fopen(InputFile, "r");
remove(OutputFile); //remove previous output file

while((ch=getc(pFileIN))!=EOF)
{
	UpdateState(ch);
if(otherChar!='\0')
	{
		char temp=otherChar;
		otherChar='\0';
		UpdateState(temp);
	}
}
fclose(pFileIN);
}
void UpdateState(char x)
{
	char tempChar=x;
	switch(State)
	{
	case State_Start:{
					 if(tempChar==WhiteSpace)
						 NextState=State_Start;
					 else if(tempChar=='\n')
						 NextState=State_Start;
					 else if(tempChar==OpenComment)
						 NextState=State_InComment;
					 else if(IsDigit(tempChar))
					 {
						 NextState=State_InNum;
						 token[tokenCounter]=tempChar;
						tokenCounter++;
						NumFlag=1;
					 }
					 else if(IsLetter(tempChar))
					 {
						 NextState=State_InID;
						 token[tokenCounter]=tempChar;
						tokenCounter++;
						LetterFlag=1;

					 }
					 else if(tempChar==Colon)
					 {
						 NextState=State_InAssign;
						 token[tokenCounter]=tempChar;
						tokenCounter++;
					 }
					 else
					 {
						 //NextState=State_Done;
						 token[tokenCounter]=tempChar;
						tokenCounter++;
						Done();
					 }

					 }
					 break;
	case State_InComment:{
					if(tempChar==CloseComment)
						 NextState=State_Start;
					else
						NextState=State_InComment;
					 break;
						 }
	case State_InNum:{
					if(IsDigit(tempChar))
					{
						NextState=State_InNum;
						token[tokenCounter]=tempChar;
						tokenCounter++;
						
					}
					else
					{
						//NextState=State_Done;
						otherChar=tempChar; //keeping the remaining char
					Done();
					}
					 
					 
					 }
					 break;
	case State_InID:{
					if(IsLetter(tempChar))
					{
						 NextState=State_InID;
						token[tokenCounter]=tempChar;
						tokenCounter++;
						
					}
					else
					{
						//NextState=State_Done;
						otherChar=tempChar; //keeping the remaining char
					Done();
					}
					
					}
					 break;
	case State_InAssign:{
						if(tempChar==EqOp)
					{
						//NextState=State_Done;
						token[tokenCounter]=tempChar;
						tokenCounter++;
						Done();
					}
					else
					{
						//NextState=State_Done;
						otherChar=tempChar; //keeping the remaining char
					Done();
					}
						}
					 break;

	}
	State=NextState;
}
void Done()
{
		printInfile();
		tokenCounter=0;
		NextState=State_Start;
		memset(&token[0], 0, sizeof(token));
}

void printInfile()
{
	
	char string[30];
	int i=0,j=0;
	strcpy(string,token);
	//strcat(string," is a ");
	if(NumFlag)
	{
		//strcat(string,"number");
			printf("number ");
			pFileOut=fopen(OutputFile,"a");
			fputs("number ", pFileOut);
			//fputs("\n", pFileOut);
			NumFlag=0;
	}
	
	else
	{
	for(i=0;i<NumOfResWords;i++)//check for reserved words
	{
		if(!strcmp(token,ReservedWords[i]))
		{
			//strcat(string,"reserved word");
			printf("%s ",string);
			pFileOut=fopen(OutputFile,"a");
			fputs(string, pFileOut);
		fputs(" ", pFileOut);
			LetterFlag=0; //set the flag of letter to 0 because it's a reserved word and no need to get into the idetifiers check
			
		}
		
	}
	for(i=0;i<NumOfSymbols;i++)//check for symbols
	{
		if(!strcmp(token,Symbols[i]))
		{
			//strcat(string,"special symbol");
			printf("%s ",string);
			pFileOut=fopen(OutputFile,"a");
			fputs(string, pFileOut);
			fputs(" ", pFileOut);

		}

	}
	}
	
	if(LetterFlag)//check for idetifiers
	{
		//strcat(string,"identifier");
			printf("identifier ");
			pFileOut=fopen(OutputFile,"a");
			fputs("identifier ", pFileOut);
			//fputs("\n", pFileOut);
			LetterFlag=0;
	}
	

}
