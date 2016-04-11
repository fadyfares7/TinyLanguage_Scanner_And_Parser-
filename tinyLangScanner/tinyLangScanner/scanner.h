#ifndef SCANNER_H_
#define SCANNER_H_

#include "process.h"
#include "conio.h"
#include "stdio.h"

#include <string.h>
#define InputFile "tiny_sample_code.txt"
#define OutputFile "parser_input.txt"
#define State_Start 0
#define State_InComment 1
#define State_InNum 2
#define State_InID 3
#define State_InAssign 4
#define WhiteSpace 32
#define Colon 58
#define EqOp 61
#define OpenComment 123
#define CloseComment 125
#define DigitLimitStart 48
#define DigitLimitEnd 57
#define IsDigit(x) x>=DigitLimitStart&& x<=DigitLimitEnd
#define LetterLimitStart 65
#define LetterLimitEnd 122
#define IsLetter(x) x>=LetterLimitStart&& x<=LetterLimitEnd
void scan(void);
void printInfile();
void UpdateState(unsigned char x);
void Done();

#endif