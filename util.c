#include "globals.h"
#include "util.h"

//Procedimento para printar o Token e o seu lexema
void printToken(TokenType token ,const char* tokenString)
{
    switch (token)
    {
        case IF:
        case ELSE:
        case INT:
        case RETURN:
        case VOID:
        case WHILE:
            fprintf(listing, "reserved word: %s\n",tokenString);
            break;


        case PLUS: fprintf(listing,"+\n");break;
        case MINUS: fprintf(listing,"-\n");break;
        case TIMES: fprintf(listing,"*\n");break;
        case OVER: fprintf(listing,"/\n");break;
        case LT: fprintf(listing,"<\n");break;
        case LTE: fprintf(listing,"<=\n");break;
        case GT: fprintf(listing,">\n");break;
        case GTE: fprintf(listing,">=\n");break;
        case EQ: fprintf(listing,"==\n");break;
        case DIFF: fprintf(listing,"!=\n");break;
        case ASSIGN: fprintf(listing,"=\n");break;
        case SEMI: fprintf(listing,";\n");break;
        case COMMA: fprintf(listing,",\n");break;
        case LPAREN: fprintf(listing,"(\n");break;
        case RPAREN: fprintf(listing,")\n");break;
        case LBRACKET: fprintf(listing,"[\n");break;
        case RBRACKET: fprintf(listing,"]\n");break;
        case LCURLY: fprintf(listing,"{\n");break;
        case RCURLY: fprintf(listing,"}\n");break;

        case ENDFILE: fprintf(listing,"EOF\n");break;
        case NUM:
            fprintf(listing,"NUM, val= %s\n",tokenString);
            break;
        case ID:
            fprintf(listing,"ID, name= %s\n",tokenString);
            break;
        case ERROR:
            fprintf(listing,"ERROR: %s\n",tokenString);
            break;
        //Nunca devemos chegar no caso default
        default:
            fprintf(listing,"Unknown token: %d\n",token); 
    }
}

//Procedimento para criar novo nó de declaracao na construcao da arv sintatica
TreeNode * newStmtNode(StmtKind kind)
{
    TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;
    if(t==NULL) fprintf(listing,"Out of memory error at line %d\n",lineno);
    else
    {
        for(i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = StmtK;
        t->kind.stmt = kind;
        t->lineno = lineno;
    }
    return t;
}

//Procediemnto para criar um novo noh de expressao para a contrucao da arv sintatica
TreeNode * newExpNode(ExpKind kind)
{
    TreeNode * t = (TreeNode *)malloc(sizeof(TreeNode));
    int i;
    if(t==NULL) fprintf(listing,"Out of memory error at line %d\n",lineno);
    else
    {
        for(i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodekind = ExpK;
        t->kind.exp = kind;
        t->lineno = lineno;
    }
    return t;
}

//Procedimento que aloca e cria no copia de uma cadeia existente
char * copyString(char * s)
{
    int n;
    char * t;
    if(s == NULL) return NULL;
    n = strlen(s) + 1;
    t = malloc(n);
    if(t == NULL) fprintf(listing, "Out of memory error at line %d\n",lineno);
    else strcpy(t,s);
    return t;
}


//Variavel indentno usada por printTree para armazenar a quantidade corrente de espacos para tabular
static int indentno = 0;

//Macros para aumentar/diminuir a identacao
#define INDENT indentno+=2
#define UNINDENT indentno-=2

// Tabula por espacos de impressao
static void printSpaces (void)
{
    int i;
    for (i=0;i<indentno;i++) fprintf(listing," ");
}




//procedimento que imprime a arv sintatica usando tabulacao
void printTree(TreeNode * tree)
{
    int i;
    INDENT;
    while(tree != NULL)
    {
        printSpaces();
        if(tree->nodekind == StmtK)
        {
            switch (tree->kind.stmt)
            {
                case IfK: fprintf(listing,"If\n");break;
                case RepeatK: fprintf(listing,"Repeat\n");break;
                case AssignK: fprintf(listing,"Assign to: %s\n",tree->attr.name);break;
                case ReadK: fprintf(listing,"Read: %s\n",tree->attr.name);break;   
                case WriteK: fprintf(listing,"Write\n");break;
                default: fprintf(listing,"Unknown StmtNode kind\n");
            }
        }
        else if (tree->nodekind == ExpK)
        {
            switch(tree->kind.exp)
            {
                case OpK:
                    fprintf(listing,"Op: ");
                    printToken(tree->attr.op,"\0");
                    break;
                case ConstK:
                    fprintf(listing,"const: %d\n", tree->attr.val);
                    break;
                case IdK:
                    fprintf(listing,"Id: %s\n", tree->attr.name);
                    break;
                default:
                    fprintf(listing,"Unknown ExpNode kind\n");
            }
        }
        else fprintf(listing, "Uknown node kind\n");
        for(i=0;i<MAXCHILDREN;i++) printTree(tree->child[i]);
        tree = tree->sibling;
    }
    UNINDENT;
}





