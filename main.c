// faz a conducao do processo de compilacao, aloca e fornece valores iniciais para variaveis globais

#include "globals.h"
#include "scan.c"
#include "util.c"
#include "parse.c"
// Para fazzer apenas o scan, seta TRUE
#define NO_PARSE TRUE

//Para fazer apenas a analise sintatica, seta TRUE
#define NO_ANALYSE FALSE

// Para nao gerar codigo, seta TRUE
#define NO_CODE FALSE

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else 
#include "parse.h"
#if !NO_ANALYSE
#include "analyse.h"
#if !NO_CODE
#include "cden.h"
#endif
#endif
#endif

//alocando variaveis globais
int lineno = 0;
FILE *source;
FILE * listing;
FILE * code;

// ajuste de auxiliares do compilador
int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;


int main (int argc, char * argv[])
{
    TreeNode * syntaxTree;
    char pgm[20]; //armazena o nome do arquivo que contem o codigo fonte
    if(argc != 2)
    {
        fprintf(stderr,"usage: %s <filename>\n",argv[0]);
        exit(1);
    }
    strcpy(pgm,argv[1]);
    if (strchr(pgm,'.') == NULL) strcat(pgm,".tny");

    source = fopen(pgm,"r");

    if (source == NULL)
    {
        fprintf (stderr,"File %s not found\n",pgm);
        exit(1);
    }

    listing = stdout; //envia a lista para a tela

    fprintf(listing,"\n TINY COMPILATION: %s\n",pgm);

    #if NO_PARSE
        while (getToken() != ENDFILE);
    #else
        syntaxTree = parse();
        if (TraceParse)
        {
            fprintf(listing,"\nSyntax tree:\n");
            printTree(syntaxTree);
        }
    #if !NO_ANALYSE
        if(!Error)
        {
            fprintf(listing,"\nbuilding Symbol Table...\n");
            buildSymtab(syntaxTree);
            fprintf(listing,"\nChecking Types...\n");
            typeCheck(syntaxTree);
            fprintf(listing, "\nType Checking Finished\n");
        }
    #if !NO_CODE
        if(!Error)
        {
            char * codefile;
            int fnlen = strcspn(pgm,".");
            codefile = (char *)calloc(fnlen+4,sizeof(char));
            strncpy(codefile,pgm,fnlen);
            strcat(codefile,".tm");
            code = fopen(codefile,"w");
            if(code == NULL)
            {
                printf("Unable to open %s\n",codefile);
                exit(1);
            }
            codeGen(syntaxTree,codefile);
            fclose(code);
        }
    #endif
    #endif
    #endif

    return 0;
}
