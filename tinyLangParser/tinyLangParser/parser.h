#ifndef PARSER_H_
#define PARSER_H_
#include "process.h"
#include "conio.h"
#include "stdio.h"
#include <string.h>
#define InputFile "parser_input.txt"
#define OutputFile "parser_output.txt"
#define WhiteSpace 32
void Scan();
void match(char x[]);
void error();
void program();
void Stmt_sequence();
void Statment();
void If_Stmt();
void Repeat_Stmt();
void Assign_Stmt();
void Read_Stmt();
void Write_Stmt();
void Exp();
void Compare_Op();
void Simple_Exp();
void AddOp();
void Term();
void MulOp();
void Factor();
#endif