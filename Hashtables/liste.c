/* IONUT CRISTIAN SAVU, 312CB, TEMA 1*/
#include "liste.h"

void Insert (TLDG* l, void * ae, TFCmp fct) //functia de inserare
{
	TLDG aux = malloc(sizeof(TCelula2));//lista auxiliara, contine un singur element
	TLDG temp; //lista auxiliara pentru parcurgerea listei initiale
	if (!aux) //vf alocare
		return;
	aux->pre = aux->urm = aux; //cream legaturile lui aux
	aux->info = ae;
	
	//lista este vida
	if ( *l == NULL)
	{	
		
		*l = aux;
		return;
	}
	//lista nu este vida, continuam cu alte cazuri
	
	//inseare la inceput
	if (fct ( (*l)->info, ae) == 0) //elementul exista deja in tabela, deci dezalocam
	{	
		TAddress * p = ((TAddress*)(aux->info));
		free(p->key);
		free(p->value);
		free(p);
		free(aux);
		return;
	}
	
	if (fct ( (*l)->info, ae) > 0)
	{
		aux->pre = (*l)->pre;
		(*l)->pre->urm = aux;
		aux->urm = *l;
		(*l)->pre = aux;
		*l = aux;
		return;
	}
	//inserare inainte de element
	
	for (temp = (*l)->urm; temp != *l; temp = temp->urm)
	{
		if(fct (temp->info, ae) == 0) //elementul exista deja in tabela, deci dezalocam
		{
			TAddress * p = ((TAddress*)(aux->info));
			free(p->key);
			free(p->value);
			free(p);
			free(aux);
			return;
		}
		
		if (fct (temp->info, ae) > 0) //inserare inainte de elementul curent
		{	

			aux->urm = temp;
			aux->pre = temp->pre;
			temp->pre->urm = aux;			
			temp->pre = aux;
			return;
		}
		
	}
	if (fct (temp->info, ae) != 0) //inserare la sfarsit
	{
		aux->pre = (*l)->pre;
		(*l)->pre->urm = aux;
		aux->urm = *l;
		(*l)->pre = aux;
		return;
	}
	return;
}

void Remove (TLDG* l, void * ae, TFCmp fct, TFF fc) //functia de eliminare
{
	TLDG temp = *l, aux; //declaram o lista auxiliara si una temporara
	
	if (temp == NULL) //lista noastra este nula
		return;
		
	if (temp == temp->urm) //lista noastra are un singur element
	{
		if (fct (temp->info, ae) == 0)
		{
			//eliminare
			fc(temp->info);
			free(temp);
			*l = NULL;
			return;
		}
	}
	else //lista are mai multe elemente
	{
		//eliminare la inceput
		if (fct (temp->info, ae) == 0)
		{
			//eliminare
			temp->urm->pre = temp->pre;
			temp->pre->urm = temp->urm;
			*l = temp->urm;
			fc(temp->info);
			free(temp);
			return;
		}
		else //eliminare in interiorul listei
		{
			for (aux = temp->urm; aux != temp; aux = aux->urm) //parcurgerea listei
			{
				if (fct (aux->info, ae) == 0)
				{
					//eliminare
					aux->pre->urm = aux->urm;
					aux->urm->pre = aux->pre;
					fc(aux->info);
					free(aux);
					return;
				}
			}
		}
	}
}
		
void DistrL(TLDG * l, TFF fe) //functie de distrugere lista
{
	TLDG temp = (*l)->urm;
	for (; temp != (*l);) //parcurgem lista
	{
		//dezalocam
		TLDG aux = temp;
		temp = temp->urm;
		fe(aux->info);
		free(aux);
	}
	//dezalocam si setam valoarea listei cu NULL
	fe( (*l)->info );
	free( *l );
	*l = NULL;
}	
	
		
	
