// Ionut-Cristian Savu, 312CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char * titlu;
    char * autor;
    int rating;
    int nr_pg;
} TCarte; /*structura de carte, in care voi memora titlul si autorul, de tip char *, si rating-ul si numarul de pagini, de tip intreg*/

#define LUNG_ALFABET (68) /*macro pentru lungimea maxima a alfabetului, avem elemente de la 0 la 67*/
#define LUNG_MAX_AUTOR (40) /*macro pentru lungimea maxima a autorului*/
#define LUNG_MAX_TITLU (50) /*macro pentru lungimea maxima a titlului*/
void FreeCarte (void * ae); /*functie void de eliberare/eliminare elemente de tip TCarte*/
int ConstrCarte (char * date, TCarte ** carte); /*functia care construieste cartea cu elementele 
                                                citite, returneaza 1 pentru succes, 0 pentru insucces*/
int CalcIndex (char c);/*functia care calculeaza indexul literei din titlu/numele autorului, pe care
                        o folosim pentru a putea parcurge arborele Trie in ordinea literelor din alfabetul folosit*/