/* IONUT CRISTIAN SAVU, 312CB, TEMA 1*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

void ElibAdd(void * ae) //functie de eliberare element generic
{
	TAddress * a = (TAddress*) ae;
	free(a->key);
	free(a->value);
	free(a);
}

int CodHash (void * element, size_t M) //functia de hashing, returneaza restul impartirii sumei caracterelor cheii la marimea tabelei hash
{
	
	char * key = (char*)element;
	
	int s = 0, i;
	for (i = 0; i < strlen (key) ; i ++)
		s += key[i];
	
	return s%M;
}

int comparaValue (void * e1, void * e2) //functie de comparat elementele value din lista
{
	TAddress * a1 = (TAddress *) e1;
	TAddress * a2 = (TAddress *) e2;
	
	return strcmp(a1->value, a2->value);
}
int comparaKey (void * e1, void * e2) //functie folosita pentru adaugare ordonata
{
	TAddress * a1 = (TAddress *) e1;
	TAddress * a2 = (TAddress *) e2;
	
	return strcmp(a1->key, a2->key);
}
int compara (void * e1, void * e2) //functie folosita pentru eliminare
{
	TAddress * a1 = (TAddress *) e1;
	char * key = (char*) e2;
	
	return strcmp (a1->key, key);
}
	
void put (THash * hash, char * key, char * value) //functia de inserarea in tabela hash, a cheii si a valorii cheii (DNS)
{
	int cod = hash->fhash(key, hash->M);
	
	TAddress * DNS = malloc(sizeof(TAddress));//
	DNS->key = malloc(MAX * sizeof(char)); //alocarea elementului de tip TAddress
	DNS->value = malloc(MAX * sizeof(char));//

	strcpy (DNS->key, key);
	strcpy (DNS->value, value);
	
	Insert (hash->v+cod, DNS, comparaKey); //inserarea acestuia prin functia de inserare ordonata in lista
}

	
void get (THash * hash, char * key, FILE * out) //functia care intoarce valoarea cheii din lista, sau NULL daca aceasta nu exista
{
	int cod = hash->fhash(key, hash->M);
	TLDG temp = hash->v[cod], aux;
	if (temp == NULL)
	{
		fprintf(out, "NULL\n");
		return;
	}
	else if (strcmp (((TAddress*)(temp->info))->key, key) == 0)
	{
		fprintf(out, "%s\n", ((TAddress*)(temp->info))->value); //verificarea daca primul element e cel cautat
		return;
	}
	else
	{
		for (aux = temp->urm; aux != temp; aux = aux->urm) //parcurgerea listei
		{
			if (strcmp (((TAddress*)(aux->info))->key, key) == 0)
			{
				fprintf(out, "%s\n", ((TAddress*)(aux->info))->value);
				return;
			}
		}
	}
	fprintf(out, "NULL\n");
	
	return;
}
void removee (THash * hash, char * key) //functia de eliminare din tabela hash
{
	int cod = hash->fhash(key, hash->M);
	Remove(hash->v+cod, key, compara, ElibAdd);
}

void print (THash * hash, FILE * out) //functia de afisare a tabelei hash
{
	TLDG temp, aux;
	int i;
	for (i = 0; i < hash->M; i++)
	{
		temp = hash->v[i];
		if (temp != NULL)
		{
			//afisam primul element
			fprintf(out, "%d: ", i);
			fprintf(out, "%s ", ((TAddress*)(temp->info))->value);
			
			for (aux = temp->urm; aux != temp; aux = aux->urm) //parcurgerea listei
				fprintf(out, "%s ", ((TAddress*)(aux->info))->value); //afisam urmatoarele elemente
			
			fprintf(out, "\n");
		}
	}
}

void print_bucket(THash * hash, int bucket, FILE * out) //functia de afisare a unui bucket specificat al tabelei hash
{
	if (bucket >= hash->M) //bucketul dat functiei depaseste dim. tabelei
		return;
	
	TLDG aux, temp = hash->v[bucket];
	if (temp != NULL)
	{
		fprintf(out, "%s ", ((TAddress*)(temp->info))->value); //idem print
			
		for (aux = temp->urm; aux != temp; aux = aux->urm)
			fprintf(out, "%s ", ((TAddress*)(aux->info))->value); //idem print
		
		fprintf(out, "\n");
	}
	else
		fprintf(out, "VIDA\n");
}

void find (THash * hash, char * key, FILE * out) //functia care verifica daca un element se afla in lista, intoarce True sau False
{
	int cod = hash->fhash(key, hash->M);
	TLDG temp = hash->v[cod], aux;
	
	if (temp == NULL) //lista vida
	{
		fprintf(out, "False\n");
		return;
	}
	
	if (strcmp (((TAddress*)(temp->info))->key, key) == 0) //vf primului element
	{
		fprintf(out, "True\n");
		return;
	}
	else
	{
		//parcurgem lista
		for (aux = temp->urm; aux != temp; aux = aux->urm)
		{
			if (strcmp (((TAddress*)(aux->info))->key, key) == 0)
			{
				fprintf(out, "True\n");
				return;
			}
		}
	}
	fprintf(out, "False\n");
}
	

int main(int argc, char * argv[])
{
	char * input, * output;
	THash * hash = NULL;
	
	
	int M = atoi (argv[1]); //numarul de elemente din tabela hash
	hash = IniTHash(M, CodHash); 


	FILE * in;
	in = fopen(argv[2], "rt");
	if (in == NULL)
		return -1; //nu s-a putut deschide fisierul de input
		
	FILE * out;
	out = fopen (argv[3], "wt");
	if (out == NULL)
		return -1;//nu s-a putut deschide fisierul de output
	
	char * line = NULL;
	line = malloc(MAX);
	if (line == NULL)
		return -1; //eroare la alocare
	
	while (fgets(line, MAX, in))
	{
		
		if (line [ strlen (line) - 1 ] == '\n') //eliminam caracterul endline
			line [ strlen (line) - 1 ] ='\0';
		
		
		char * function = strtok(line, " "); //vom folosi primul cuvant din fisierul de input de pe fiecare linie pentru a afla ce functie folosim
		
		if (strcmp(function, "put") == 0)
		{	
			char * key = strtok(NULL, " "); //copiem cheia
			char * value = strtok(NULL, " ");//copiem valoarea
			
			if (key[ strlen (key) - 1 ] == '\n')//eliminam caracterul endline
				key[ strlen (key) - 1 ] = '\0';
			
			if (value[ strlen (value) - 1 ] == '\n')//eliminam caracterul endline
				value[ strlen (value) - 1 ] = '\0';
			
			put(hash, key, value); //inseram in tabela
		}
		if (strcmp(function, "get") == 0)
		{
			char * key = strtok(NULL, " ");//copiem cheia
			get(hash, key, out);//primim valoarea cheii daca exista
		}
		if (strcmp(function, "remove") == 0)
		{
			char * key = strtok(NULL, " ");//copiem cheia
			removee(hash, key);//eliminam perechea cheie-valoare daca exista
		}
		
			
		if (strcmp(function, "find") == 0)
		{
			char * key = strtok(NULL, " ");//copiem cheia
			find(hash, key, out);//vf daca exista cheia in tabela hash
		}
		if (strcmp(function, "print") == 0)
		{
			print(hash, out);//printam tabela hash
		}
		
		if (strcmp (function, "print_bucket") == 0)
		{
			char * index = strtok(NULL, " ");
			int i = atoi(index); //indexul bucketului
			print_bucket(hash, i, out);	//printam un bucket anume al tabelei
		}
		
	}
	//dezalocari
	free(line);
	fclose(in);
	fclose(out);
	DistrTHash(&hash, ElibAdd);
		
	return 0;
}
