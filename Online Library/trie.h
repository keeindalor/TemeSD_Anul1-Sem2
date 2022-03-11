// Ionut-Cristian Savu, 312CB
#include "book.h"

typedef struct nod
{
    struct nod * copii[LUNG_ALFABET];
    void * info; /*in care vom stoca structul pentru carte, sau arborele de tip T1 pecific finalului arborelui T2*/
    int sfarsit; /*1 daca suntem la sf de arbore, 0 in caz contrar */
}TNod, *Trie, **ATrie;

#define LUNG_ALFABET (68)
#define LUNG_MAX_AUTOR (40)
#define LUNG_MAX_TITLU (50)

Trie Constr(); /*functie care returneaza un nod proaspat construit din arbore*/
int esteFrunza (Trie t); /*functie care verifica daca este frunza, adica ne aflam la sfarsit sau nu*/
int esteGol (Trie T); /* functie care returneaza 0 daca arborele are elemente, si 1 daca nu are elemente */
int InserareT1(Trie * T1, TCarte * carte, char * titlu); /*functie de inserare in T1, de tip int, pentru a putea insera
                                                            in T2 fara pierderi de memorie*/
void InserareT2(Trie * T2, char * titlu, char * autor, TCarte * carte); /*functie de inserare in T2*/
Trie Gaseste (Trie T, char * info);/*returneaza adresa pozitiei in care o cheie se termina in arbore, daca aceasta exista*/
int Cautare (Trie T, char * info); /*verifica daca o cheie este prezenta in arbore*/
void Afisare(Trie T, char str[], int nivel, FILE * fout); /*afiseaza recursiv chei din arbore*/
Trie Sterge(Trie T, char * info, int nivel); /*sterge cheie de tip info din Trie, returneaza adresa arborelui fara cheia respectiva*/
void DistrT1(Trie * T1, int OK); /*functie eliberare memorie in T1*/
void DistrT2 (Trie * T2); /*functie eliberare memorie in T2*/