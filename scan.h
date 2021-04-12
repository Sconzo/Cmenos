#include "globals.h"

#ifndef _SCAN_H_
#define _SCAN_H_

// MAXTOKENLEN eh o tamanho maximo de um token
#define MAXTOKENLEN 40

// tokenString armazena o lexema de cada token
extern char tokenString[MAXTOKENLEN + 1];

// getToken retorna o proximo token no arquivo fonte
TokenType getToken(void);




#endif