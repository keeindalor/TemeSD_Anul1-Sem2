/* IONUT CRISTIAN-SAVU, 312CB, TEMA 1 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#define MAX 256

typedef struct celula2
{
  void *info;              /* adresa element extern */
  struct celula2 *pre, *urm;  /* legaturi spre celulele vecine */
} TCelula2, *TLDG;

typedef struct
{
	char *key;
	char *value;
} TAddress;

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TFF)(void *); /*functie de eliminare*/

void Insert (TLDG* l, void * ae, TFCmp fct); /*functie de inserare in lista, inserarea se face ordonata*/
void Remove (TLDG* l, void * ae, TFCmp fct, TFF fc); /*functie de eliminare din lista*/
void DistrL(TLDG * l, TFF fe); /*functia de distrugere lista*/


