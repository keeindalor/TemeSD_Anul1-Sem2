// Ionut-Cristian Savu, 312CB
#include "utils.h"

int main(int argc, char ** argv)
{
   /*declarari*/
    Trie T1, T2;
    FILE * fin, * fout;

    fin = fopen(argv[1], "r");
    if (!fin)
    {
        printf("eroare deschidere fisier\n");
        return -1;
    }

    fout = fopen(argv[2], "w");
    if (!fout)
    {
        fclose(fin);
        printf("eroare la deschidere fisier de iesire\n");
        return -1;
    }

    T1 = Constr();
    T2 = Constr();
    char * line = NULL;
    line = malloc(256 * sizeof(char));

    
    while (fgets(line, 256, fin)) /*citire din fisier*/
    {
        if (line [ strlen (line) - 1 ] == '\n')
			line [ strlen (line) - 1 ] ='\0';
       
        char * functie = strtok(line, " "); /*extragere nume functie pentru a aplica functiile din fisier*/
       
        int lung = strlen(functie);
        if (functie[lung - 1] == '\n')
            functie[lung - 1] = '\0';
       
        if (strcmp(functie, "add_book") == 0)
        {
            char * date_carte = strtok(NULL, "");
         
            AddBook(&T1, &T2, date_carte);
        }
        if (strcmp(functie, "search_book") == 0)
        {
            char * titlu = strtok(NULL, "");
            int len = strlen(titlu);
            if (titlu[len - 1] == '~')
            {
                titlu = strtok(titlu, "~");
                SearchBookAC(T1, titlu, fout);
            }
            else
            {
                SearchBook(titlu, fout, T1);
            }
        }
        if (strcmp(functie, "list_author") == 0)
        {
            char * autor = strtok(NULL, "");
            int len = strlen(autor);
            if (autor[len - 1] == '~')
            {
                autor = strtok(autor, "~");
                ListAuthorAC(T2, autor, fout);
            }    
            else
            {
                ListAuthor(T2,autor, fout);
            }
        }
        if (strcmp(functie, "search_by_author") == 0)
        {

            char * autor = strtok(NULL, ":");
            char * titlu = strtok(NULL, "");
            
            if (titlu == NULL)
            {
                autor = strtok(autor, "~");
                ListAuthorAC(T2, autor, fout);
            }
            else if (titlu[strlen(titlu) - 1] == '~')
            {
                titlu = strtok(titlu, "~");
                SearchAuthorAC(T2, autor, titlu, fout);
            }
            else
            {
                SearchAuthor(T2, autor, titlu, fout);
            }
        }
        if (strcmp(functie, "delete_book") == 0)
        {
            char * titlu = strtok(NULL, "");
            DeleteBook(T1, T2, titlu, fout);
        }
    }
   
    /*dezalocari*/
    free(line);
    fclose(fout);
    fclose(fin);
    DistrT1(&T1, 1);
    DistrT2(&T2);
    
    return 0;
}