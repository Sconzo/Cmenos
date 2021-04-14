// Contem as definicoes de tipos de dados e de variaveis globais usadas em todo o compilador

#ifndef _GLOBALS_H_
#define _GLOBALS_H_


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

// MAXRESERVED representa a quantidade de palavras reservadas
// Para a linguagem Cmenos esse valor eh 6
#define MAXRESERVED 6


typedef enum
    //tokens de controle
    {ENDFILE,ERROR,
    //palavras reservadas
    ELSE,IF,INT,RETURN,VOID,WHILE,
    //token multicaracteres
    ID,NUM,
    //simbolos especiais
    PLUS,MINUS,TIMES,OVER,LT,LTE,GT,GTE,EQ,DIFF,ASSIGN,SEMI,COMMA,
    LPAREN,RPAREN,LBRACKET,RBRACKET,LCURLY,RCURLY
    }TokenType;

//arquivo de texto do codigo fonte
extern FILE* source;

//arquivo de texto da listagem de saida
extern FILE* listing;

//arquivo de texto de codigo para o simulador TM
extern FILE* code;

//enumeracao das linhas da fonte na listagem
extern int lineno;


//*********************************
//Arvore sintatica para analise sintatica
//********************************

typedef enum{StmtK,ExpK}NodeKind;
typedef enum{IfK,RepeatK,AssignK,ReadK,WriteK}StmtKind;
typedef enum{OpK,ConstK,IdK}ExpKind;

//ExpType eh usada para a verificacao de tipos
typedef enum{Void,Integer,Boolean}ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
{
    struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    int lineno;
    NodeKind nodekind;
    union {StmtKind stmt;ExpKind exp;}kind;
    union 
    {
        TokenType op;
        int val;
        char * name;
    }attr;
    // para verificar os tipos de expressoes
    ExpType type;
}TreeNode;


//*********************************
// Auxiliares para acompanhar a execucao
//********************************

//EchoSource = TRUE ecoa o programa fonte no arquivo de listagem com enumeracao de linhas
//durante a analise sintatica
extern int EchoSource;

//traceScan = TRUE imprime informacoes de tokens no arquivo de listagem quando cada token eh 
// reconhecido pelo sistema de varredura
extern int TraceScan;

// TraceParse = TRUE imprime a arvore sintatica no arquivo de listagem em forma linearizada
// com identificadores para os filhos
extern int traceParse;

//TraceAnalyze = TRUE coloca no arquivo de listagem as insercoes e buscas na tabela de simbolos
extern int TraceAnalyze;

//TraceCode = TRUE escreve comentarios no arquivo de codigo TM a medida que o codigo eh gerado
extern int TraceCode;

//Error = TRUE impede novas passadas se ocorrer um erro
extern int Error;

#endif