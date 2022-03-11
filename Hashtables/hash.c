/* IONUT CRISTIAN SAVU, 312CB, TEMA 1*/
#include "hash.h"

THash * IniTHash(size_t M, TFHash fhash)
{
    THash * hash = (THash *) calloc(sizeof(THash), 1); //alocam spatiul pentru tabela hash
    if (!hash) 
    {
        printf("eroare alocare hash\n");
        return NULL; //nu se poate aloca, returneaza NULL
    }

    hash->v = (TLDG *) calloc(M, sizeof(TLDG)); //alocam vector de pointeri de tip lista dubla inlantuita generic in tabela
    if(!hash->v) 
    {
        printf("eroare alocare vector de pointeri TLDG in hash\n");
        free(hash); //in cazul in care este eroare, eliberam intreaga tabela hash
        return NULL; //apoi returnam null
    }
    //initializam vectorul de liste si descriptorul tabelei
    hash->M = M; 
    hash->fhash = fhash;
    return hash; // returnam adresa tabelei
}
void DistrTHash(THash ** hash, TF fe)
{
	int i;
	for (i = 0; i < (*hash)->M; i++) //parcurgem tabela
	{
		if ( (*hash)->v[i] != NULL ) //daca exista elemente in tabela, distrugem lista de pe pozitia actuala a tabelei
		{
			DistrL((*hash)->v+i, fe);
		}
	}
	free ((*hash)->v); //eliberam spatiul valorii listei
	free (*hash); //eliberam tabela
	*hash = NULL; //setam tabela la NULL
}
	


