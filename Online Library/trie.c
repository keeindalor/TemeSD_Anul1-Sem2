// Ionut-Cristian Savu, 312CB
#include "trie.h"

Trie Constr()
{
    int index;
    Trie temp = malloc(sizeof(TNod)); /*declar un arbore temporar
                                      in care voi face alocarile*/
    if (!temp) /*verificam alocarea*/
    {
        printf("eroare la alocare\n");
        return NULL;
    }
   
    /*initializare campuri*/
    temp->info = NULL;
    temp->sfarsit = 0;
    for (index = 0; index < LUNG_ALFABET; index ++) /*parcurgerea celor 67 de posibili fii*/
        temp->copii[index] = NULL;
    
    return temp;
}

int esteFrunza(Trie t)
{
    return t->sfarsit != 0; /*daca nu este la sfarsit de arbore, este 1. altfel, 0*/
}
int esteGol (Trie T) /* functie care returneaza 0 daca arborele are elemente, si 1 daca nu are elemente */
{
    int i;
    for (i = 0; i < LUNG_ALFABET; i ++) /*parcurgere arbore*/
        if (T->copii[i])
            return 0;
    return 1;
}

int InserareT1(ATrie  T1, TCarte * carte, char * titlu) /*functie de inserare in arbore de tip T1*/
{
    int index, nivel, lungime = strlen(titlu);
    Trie temp = * T1, aux; /*declaram un arbore temporar care e pozitionat la adresa lui T1, si unul auxiliar, pe care il folosim la alocari*/
    for (nivel = 0; nivel < lungime; nivel++)
    {
        index = CalcIndex(titlu[nivel]);
        if (!temp->copii[index]) /*daca nu are copii, ii creez*/
        {
            aux = Constr();
            if (!aux) /*verificam alocarea*/
            {
                printf("eroare la alocare\n");
                return -1;
            }
            temp->copii[index] = aux; /*ne plasam pe pozitia celulei auxiliare*/
        }
        temp = temp->copii[index]; /*avans in trie*/
    }

    /*cream legatura cu structura si marcam sf arborelui*/
    if (temp->info != NULL) /*daca exista o carte inserata deja in Trie, o dezalocam si returnam 0 pentru a nu pierde memorie*/
    {
        FreeCarte(carte);
        return 0;
    }    
    temp->info = carte; /*legatura pt carte*/
    temp->sfarsit = 1; /*marcam sfarsitul*/
    return 1;
}

void InserareT2(ATrie  T2, char * titlu, char * autor, TCarte * carte)
{

    /*inserarea este asemanatoare cu T1, dar difera la campul Info*/
    int index, nivel, lungime = strlen(autor);
    Trie temp = *T2, aux;
    for (nivel = 0; nivel < lungime; nivel++)
    {
        index = CalcIndex(autor[nivel]);
        if (!temp->copii[index])
        {
            aux = Constr();
            if (!aux)
            {
                printf("eroare la alocare\n");
                return;
            }
            temp->copii[index] = aux;
        }
        temp = temp->copii[index];
    }


    /*marcam sf arborelui*/
    temp->sfarsit = 1;

    /*cream legatura cu un arbore de tip T1*/
    if (temp->info == NULL)
    {   
        /*daca celula e goala, construim una si inseram la adresa acesteia*/
        aux = Constr();
        InserareT1(&aux,carte, titlu);
        temp->info = aux;
        
    }
    else
    {
        /*dca nu e goala, doar inseram la adresa acesteia*/
        aux = (Trie)temp->info;
        InserareT1(&aux,carte, titlu);      
    }    
    
}
Trie Gaseste (Trie T, char * info) /*functie care returneaza adresa celulei care respecta parcurgerea*/
{
    
    int index, nivel, lungime = strlen(info);
    Trie temp = T;
    for (nivel = 0; nivel < lungime; nivel++) /*parcurgere*/
    {
        index = CalcIndex(info[nivel]);
        if (!temp->copii[index])
        {
            return NULL;
        }    
        temp = temp->copii[index];
    }
   
    return temp;
}
int Cautare (Trie T, char * info) /*fuctie care verifica existenta unui string in trie, returneaza 1 sau 0 */
{
    int index, nivel, lungime = strlen(info);
    Trie temp = T;

    for (nivel = 0; nivel < lungime; nivel++)
    {
        index = CalcIndex(info[nivel]);
        if (!temp->copii[index])
            return 0;
        temp = temp->copii[index];
    }
    return (temp != NULL && temp->sfarsit);
}

void Afisare(Trie T, char str[], int nivel, FILE * fout) /*functie recursiva de afisare*/
{
    if (esteFrunza(T)) /*daca ne aflam la sfarsit de arbore, afisam stringul construit*/
    {
        str[nivel] = '\0';
        fprintf(fout, "%s\n", str);
    }

    int index;
    for (index = 0; index < LUNG_ALFABET; index++) /*parcurgere in toate caile posibile pe lungimea alfabetului*/
    {
        if (T->copii[index])
        {   
            /*extragerea caracterului folosind indexul*/
            if (index == 62)
                str[nivel] = '.';
            else if (index == 63)
                str[nivel] = '-';
            else if (index == 64)
                str[nivel] = '\'';
            else if (index == 65)
                str[nivel] = '?';
            else if (index == 66)
                str[nivel] = '!';
            else if (index == 67)
                str[nivel] = ' ';
            
            if (index < 26)
                str[nivel] = index + 'a';
            if (index >= 26 && index < 52)
                str[nivel] = index + 'A' - 26;
            if (index >= 52 && index < 62)
                str[nivel] = index + '0' - 52;
           
            Afisare(T->copii[index], str, nivel + 1, fout); /*apelarea recursiva a functiei*/
        }
    }

}

Trie Sterge(Trie T, char * info, int nivel) /*functie care sterge o cheie de tip char * din arbore. functie recursiva*/
{
    if (!T) /*arbore gol*/
        return NULL;
   
    Trie temp = T;
   
    if (nivel == strlen(info)) /*sfarsit de cuvant*/
    {
        if (temp->sfarsit == 1)
            temp->sfarsit = 0;
      
        if (esteGol(temp)) /*verificam daca este gol arborele*/
        {
            free(temp); /*dezalocari*/
            temp = NULL;
        }

        return temp;
    }
    int index = CalcIndex(info[nivel]);
    temp->copii[index] = Sterge(temp->copii[index], info, nivel + 1);
    /* s-a apelat recursiv o functie pentru a sterge in continuare legaturile pentru cheia data*/
   
    if (esteGol(temp) && temp->sfarsit == 0)
    {
        free(temp); /*dezalocari*/
        temp = NULL;
    }
    return temp;
}

void DistrT1(Trie * T1, int OK) /*functie eliberare memorie in T1*/
{
    Trie temp = *T1;
    if (!temp)
        return; /*arbore vid*/
   
    int i;
    for (i = 0; i < LUNG_ALFABET; i++)
    {
        DistrT1(&temp->copii[i], OK); /*parcurgere recursiva*/
    }

    if (temp->sfarsit == 1 && OK == 1) /*daca ne aflam la sfarsit, ne folosim de OK pentru a nu intampina double free-uri pentru elementele
                                        de tip TCarte din campul info al trie-ului*/
    {
        if (temp->info != NULL)
        {
            TCarte * carte = (TCarte*)(temp->info); /*dezalocari*/
            FreeCarte(carte);
            carte = NULL;
            (*T1)->info = NULL;
        }
    }
  
    free(temp); /*dezalocari*/
    *T1 = NULL;
}

void DistrT2 (Trie * T2) /*functie eliberare memorie in T2*/
{
    Trie temp = *T2;
    
    if (!(*T2))
        return;/*arbore vid*/
    
    int i;
    for (i = 0; i < LUNG_ALFABET; i ++)
    {
        DistrT2(&temp->copii[i]); /*parcurgere recursiva*/
    }

    
    if (temp->sfarsit == 1)
    {
        Trie temp3 = (Trie)(temp->info); /*dezalocari*/
        DistrT1(&temp3, 0);
        (*T2)->info = NULL; 
    }    
   
    free(temp); /*dezalocari*/
    *T2 = NULL;
}