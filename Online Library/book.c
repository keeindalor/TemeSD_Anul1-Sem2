// Ionut-Cristian Savu, 312CB
#include "book.h"

void FreeCarte (void * ae)
{
    TCarte * carte = (TCarte*) ae;
    free (carte->autor);
    free (carte->titlu);
    free (carte);
}

int ConstrCarte (char * date, TCarte ** carte) /*construieste struct pentru TCarte, 0 insucces, 1 succes*/
{
    *carte = malloc(sizeof(TCarte)); /*alocam element de tip TCarte*/
    if (!(*carte)) /*verificam alocarea*/
    {
        printf("eroare la alocare\n");
        return 0;
    }

    (*carte)->titlu = malloc (LUNG_MAX_TITLU * sizeof(char));  /*alocare titlu*/
    if (!((*carte)->titlu)) /*verificam alocarea*/
    {
         printf("eroare la alocare\n");
         free(*carte);
         return 0; /*exit code insucces*/
    }

    (*carte)->autor = malloc (LUNG_MAX_AUTOR * sizeof(char));
    if (!((*carte)->autor)) /*verificam alocarea*/
    {
         printf("eroare la alocare\n");
         free((*carte)->titlu);
         free(*carte);
         return 0; /*exit code insucces*/
    }

    /*inseram datele citite intr-o structura TCarte*/
    strcpy( (*carte)->titlu, strtok(date, ":")); 
    strcpy( (*carte)->autor, strtok(NULL, ":"));
    (*carte)->rating = atoi(strtok(NULL, ":"));
    (*carte)->nr_pg = atoi(strtok(NULL, ":"));
    
    return 1; /*exit code succes*/
}

int CalcIndex (char c)
{
    /* pentru a calcula indexul fiecarui caracter,
    ma voi folosi de codul ASCII */

    /* verific intai daca este caracter nonliterar */
   // printf("tralala");
    if (c == '.')
        return 62;
    else if (c == '-')
        return 63;
    else if (c == '\'')
        return 64;
    else if (c == '?')
        return 65;
    else if (c == '!')
        return 66;
    else if (c == ' ')
        return 67;
    /*verific ce litera este si ii calculez indexul*/

    if (c > 96 && c < 123) /*pentru litere mici*/
        return c - 'a';
    if (c > 64 && c < 91) /*pentru majuscule*/
        return c - 'A' + 26;
    
    /*calculez indexul pentru cifre*/
    if (c > 47 && c < 58)
        return c - '0' + 52;
    return 0;
}
