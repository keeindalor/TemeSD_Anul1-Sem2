/* IONUT CRISTIAN SAVU, 312CB, TEMA 1*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "liste.h"


typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */
typedef int (*TFHash)(void*, size_t);

typedef struct /*structura specifica tabelei hash*/
{
    size_t M; //nr elemente din tabela hash
    TFHash fhash; //functia de hashing
    TLDG *v; //vectorul de liste
} THash;


/* functii tabela hash */
THash* IniTHash(size_t M, TFHash fh); /*initializare tabela hash*/
void DistrTHash(THash** hash, TF fe); /*distruge tabela hash*/




