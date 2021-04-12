#include "globals.h"

#ifndef _UTIL_H_
#define _UTIL_H_



//Procedimento para printar o Token e o seu lexema
void printToken(TokenType,const char*);

//Procedimento para criar novo nó de declaracao na construcao da arv sintatica
TreeNode * newStmtNode(StmtKind);

//Procediemnto para criar um novo noh de expressao para a contrucao da arv sintatica
TreeNode * newExpNode(ExpKind);

//Procedimento que aloca e cria no copia de uma cadeia existente
char * copyString(char *);

//procedimento que imprime a arv sintatica usando tabulacao
void printTree(TreeNode*);

#endif