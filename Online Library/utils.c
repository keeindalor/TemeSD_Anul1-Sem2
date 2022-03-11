// Ionut-Cristian Savu, 312CB
#include "utils.h"

void AddBook(Trie * T1, Trie * T2, char * info) /*functia care insereaza cartea in T1, autorul in T2*/
{
    TCarte * carte;
    if (ConstrCarte(info, &carte) == 0) /*verificam constructia cartii*/
    {
        free (carte);
        return;
    }
    if (InserareT1(T1, carte, carte->titlu) == 1) /*daca cartea nu este inserata, inseram in T1 si in T2. Altfel, doar in T2*/
        InserareT2(T2, carte->titlu, carte->autor, carte); 
}

void SearchBook(char * titlu, FILE * fout, Trie T1) /*functie care cauta cartea si afiseaza datele despre ea*/
{
    if (Cautare(T1, titlu) == 0) /*caut cartea*/
    {
        fprintf(fout, "Cartea %s nu exista in recomandarile tale.\n", titlu);
        return;
    }
    else
    {   
        int index, nivel, lungime = strlen(titlu);
        Trie temp = T1;

        for (nivel = 0; nivel < lungime; nivel++) /*daca exista, o parcurg pana ajung la sfarsit, unde in campul info am memorat cartea si afisez*/
        {
            index = CalcIndex(titlu[nivel]);
            temp = temp->copii[index];
        }
       
        fprintf(fout,"Informatii recomandare: %s, %s, %d, %d\n", ((TCarte*)(temp->info))->titlu, /*afisare carte in fisier*/
        ((TCarte*)(temp->info))->autor, ((TCarte*)(temp->info))->rating, ((TCarte*)(temp->info))->nr_pg);
    }
}
void ListAuthor(Trie T2, char * autor, FILE * fout) /*cauta in arbore autorul, daca exista, parcurge recursiv arborele de tip T1 asociat
                                                    pentru a afisa toate cartile scrise de acel autor*/
{
    if (Cautare(T2, autor) == 0) /*existenta autorului in T2*/
    {
        fprintf(fout, "Autorul %s nu face parte din recomandarile tale.\n", autor);
        return;
    }
    else
    {
        
        int index, nivel, lungime = strlen(autor);
        Trie temp2 = T2;
        for (nivel = 0; nivel < lungime; nivel++) /*parcurgere arbore tip T2*/
        {
            index = CalcIndex(autor[nivel]);
            temp2 = temp2->copii[index];
        }
        Trie temp1 = (Trie)(temp2->info); /*arbore auxiliar de tip T1, pentru a afisa*/
        char str[LUNG_MAX_TITLU]; /*stringul folosit pentru afisare*/
        nivel = 0;
        Afisare(temp1, str, nivel, fout); /*apelul functiei recursive de afisare*/
    }
}
void CompleteazaNume (Trie T, FILE * fout, int * ok) /*functie recursiva de completare nume*/
{
    /*conditii stop*/
    if (!T)
        return;
    if (*ok == 1)
        return;
    if (T->sfarsit == 1)
    {
        /*daca suntem la sfarsit, afisam numele autorului*/
        fprintf(fout, "%s\n", ((TCarte*)(T->info))->autor);
        *ok = 1;
        return;
    }
    int i;
    for ( i = 0; i < LUNG_ALFABET; i ++)
        CompleteazaNume(T->copii[i], fout, ok); /*apelul functiei recursive de completare cheie Nume pentru toti fiii arborelui*/
}


void AutocompleteAutor (Trie T, FILE * fout, int * count) /*functia care afiseaza recursiv primii 3 autori conform prefixului*/
{
    /*conditii stop*/
    if (!T)
        return;
    if (*count == 3)
        return;
    if (T->sfarsit == 1)
    {   
        /*daca sunt la sfarsit, completez numele titlului din arborele T1 asociat arborelui T2*/
        int OK = 0;
        CompleteazaNume ((Trie)(T->info), fout, &OK);
        (*count)++;
    }
    int i;
    for (i = 0 ; i < LUNG_ALFABET; i ++)
        AutocompleteAutor(T->copii[i], fout, count); /*apelez recursiv functia pentru a afisa primii 3*/
}
void AutocompleteTitlu (Trie T, FILE * fout, int * count) /*functia care afiseaza recursiv primele 3 carti conform prefixului*/
{
    /*conditii stop*/
    if (!T)
        return;
    if (*count == 3)
        return;
    if (T->sfarsit == 1)
    {   
        /*afisez titlul cartii*/
        fprintf(fout,"%s\n", ((TCarte*)(T->info))->titlu);
        (*count)++;
    }
    int i;
    for (i = 0 ; i < LUNG_ALFABET; i ++)
        AutocompleteTitlu(T->copii[i], fout, count); /*recursiv, apelez functia pentru restul fiiilor*/
}


void ListAuthorAC(Trie T2, char * p_autor, FILE * fout) /*functia care cauta  primii 3 autori, folosind prefixul*/
{
    
    Trie temp2 = Gaseste(T2, p_autor); /*verific existenta prefixului*/
    
    if (temp2 == NULL)
    {   
        fprintf(fout, "Niciun autor gasit.\n");
        return;
    }
    
    int count = 0, i;
    if (temp2->sfarsit == 1) /*daca exista si prefix == nume intreg, il afisez si cresc contorul*/
    {
        fprintf(fout, "%s\n", p_autor);
        count++;
    }
    for (i = 0; i < LUNG_ALFABET && count < 3; i ++) /* apelez functia de autocomplete autor pentru toti fiii*/
    {   
        if (temp2->copii[i] != NULL)
        {   
            AutocompleteAutor(temp2->copii[i],  fout, &count);
        }
    }
}
void SearchBookAC(Trie T1, char * p_titlu, FILE * fout) /*functia care cauta primele 3 carti, folosind prefixul titlului*/
{
    Trie temp1 = Gaseste(T1, p_titlu);/*verific existenta prefixului*/
    if (temp1 == NULL)
    {  
        fprintf(fout, "Nicio carte gasita.\n");
        return;
    }

    int count = 0, i;
    for (i = 0; i < LUNG_ALFABET && count < 3; i ++) /*parcurgere toti fiii, pentru a apela functia de autocompletare titlu*/
    {
        
        if (temp1->copii[i] != NULL)
        {
            AutocompleteTitlu(temp1->copii[i], fout, &count);
        }
    }
}
void SearchAuthor(Trie T2, char * autor, char * titlu, FILE * fout) /*functia care cauta dupa autor si carte in arbore*/
{
    
    if (Cautare(T2, autor) == 0) /*daca nu exista*/
    {   
        fprintf(fout, "Autorul %s nu face parte din recomandarile tale.\n", autor);
        return;
    }
    else
    {
        /*parcurgere arbore tip T2*/

        int index, nivel, lungime = strlen(autor);
        Trie temp2 = T2;
       
        for (nivel = 0; nivel < lungime; nivel++)
        {
            index = CalcIndex(autor[nivel]);
            temp2 = temp2->copii[index];
        }
       
        
        /*parcurgere arbore tip T1*/

        Trie temp1 = (Trie)(temp2->info); /*verific existenta titlului in arborele T1 asociat lui T2*/
        if (Cautare(temp1, titlu) == 0)
        {
            fprintf(fout, "Cartea %s nu exista in recomandarile tale.\n", titlu);
            return;
        }

        lungime = strlen(titlu);
        for (nivel = 0; nivel < lungime; nivel++)
        {
            index = CalcIndex(titlu[nivel]);
            temp1 = temp1->copii[index];
        }

        if (temp1->sfarsit == 1) /*daca dupa parcurgere sunt la sfarsit de cheie, afisez*/
        {
            fprintf(fout,"Informatii recomandare: %s, %s, %d, %d\n", ((TCarte*)(temp1->info))->titlu,
        ((TCarte*)(temp1->info))->autor, ((TCarte*)(temp1->info))->rating, ((TCarte*)(temp1->info))->nr_pg);
        }   
        
    }
}
void SearchAuthorAC(Trie T2, char * autor, char * p_titlu, FILE * fout) /*functia de autocomplete pentru autor si carte*/
{
    if (Cautare(T2, autor) == 0) /*verific existenta prefixului*/
    {
        fprintf(fout, "Autorul %s nu face parte din recomandarile tale.\n", autor);
        return;
    }

    /* parcurgere arbore T2*/
    int index, nivel, lungime = strlen(autor);
        Trie temp2 = T2;
       
        for (nivel = 0; nivel < lungime; nivel++)
        {
            index = CalcIndex(autor[nivel]);
            temp2 = temp2->copii[index];
        }
    
    Trie temp1 = (Trie)(temp2->info); /*declaram arborele T1*/
    SearchBookAC(temp1, p_titlu, fout); /*apelez functia de cautare carte cu prefix*/

}

void DeleteBook(Trie T1, Trie T2, char * titlu, FILE * fout) /*functia de stergere carte din T1 si T2*/
{
  

    if (Cautare(T1, titlu) == 0) /*daca nu exista titlul in T1, iesim din functie*/
    {
        fprintf(fout, "Cartea %s nu exista in recomandarile tale.\n", titlu);
        return;
    }
    Trie temp1 = T1; /*arbore temporar pt T1*/
    int nivel, lungime = strlen(titlu), index;
    char * autor;

    /*daca exista, parcurgem arborele*/
    for (nivel = 0; nivel < lungime; nivel++)
    {
        index = CalcIndex(titlu[nivel]);
        temp1 = temp1->copii[index];
    }

    if (temp1->sfarsit == 1) /*daca suntem la sfarsit de T1, copiem autorul, stergem cartea si parcurgem T2-ul*/
    {
        autor = malloc (LUNG_MAX_AUTOR * sizeof(char));
        if (!autor) /*vf alocare*/
        {
            printf("eroare la alocare\n");
            return;
        }
        strcpy(autor, ((TCarte*)(temp1->info))->autor);
        
        FreeCarte((TCarte*)(temp1->info));
        temp1->info = NULL;

        Trie temp2 = T2; //arbore temporar, pentru T2*/
        lungime = strlen(autor);
        for (nivel = 0; nivel < lungime; nivel++) /*parcurgere T2*/
        {
            index = CalcIndex(autor[nivel]);
            temp2 = temp2->copii[index];
        }

        Trie temp3 = (Trie)(temp2->info);    /*arbore temporar pentru T1-le din T2*/  
        temp3 = Sterge(temp3, titlu, 0); /*stergem cartea din T1-le din T2*/
        if (!temp3)
        {
            free(temp3);
            T2 = Sterge(T2, autor, 0); /*stergem autorul din T2*/
        }

        T1 = Sterge(T1, titlu, 0); /*stergem titlul din T1*/
        free(autor);
    }
    else
    {
        fprintf(fout, "Cartea %s nu exista in recomandarile tale.\n", titlu);
        return;
    }

}
