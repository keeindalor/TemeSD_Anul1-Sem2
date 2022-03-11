// Ionut-Cristian Savu, 312CB
#include "trie.h"


#define LUNG_ALFABET (68)
#define LUNG_MAX_AUTOR (40)
#define LUNG_MAX_TITLU (50)
void AddBook(Trie * T1, Trie * T2, char * info); /*functia care insereaza cartea in T1, autorul in T2*/
void SearchBook(char * titlu, FILE * fout, Trie T1); /*functie care cauta cartea si afiseaza datele despre ea*/
void ListAuthor (Trie T2, char * autor, FILE * fout); /*cauta in arbore autorul, daca exista, parcurge recursiv arborele de tip T1 asociat
                                                      pentru a afisa toate cartile scrise de acel autor*/
void SearchAuthor( Trie T2, char * autor, char * titlu, FILE * fout); /*functia care cauta dupa autor si carte in arbore*/
void CompleteazaNume (Trie T, FILE * fout, int * ok); /*functie recursiva de completare nume*/
void AutocompleteAutor (Trie T, FILE * fout, int * count); /*functia care afiseaza recursiv primii 3 autori conform prefixului*/
void AutocompleteTitlu (Trie T, FILE * fout, int * count); /*functia care afiseaza recursiv primele 3 carti conform prefixului*/
void ListAuthorAC(Trie T2, char * p_autor, FILE * fout); /*functia care cauta  primii 3 autori, folosind prefixul*/
void SearchBookAC(Trie T1, char * p_titlu, FILE * fout);  /*functia care cauta primele 3 carti, folosind prefixul titlului*/
void SearchAuthorAC(Trie T2, char * autor, char * p_titlu, FILE * fout); /*functia de autocomplete pentru autor si carte*/
void DeleteBook(Trie T1, Trie T2, char * titlu, FILE * fout); /*functia de stergere carte din T1 si T2*/