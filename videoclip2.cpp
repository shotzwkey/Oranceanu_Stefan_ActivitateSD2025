#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Telefon
{
    int id;
    int RAM;
    char* producator;
    
        float pret;
    char serie;
};

struct Telefon initializare(int id, int ram, const char* producator, float pret, char serie)
{
    struct Telefon t;
    t.id = id;
    t.RAM = ram;
    t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
    if (t.producator != NULL)
    {
        strcpy_s(t.producator, strlen(producator) + 1, producator);
    }
    t.pret = pret;
    t.serie = serie;
    return t;
}



struct Telefon* CopiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate)
{
    struct Telefon* vectorNou = NULL;
    vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
    for (int i = 0; i < nrElementeCopiate; i++)
    {
        vectorNou[i] = vector[i];
        vectorNou[i].producator = (char*)malloc(strlen(vector[i].producator) + 1);
        strcpy_s(vectorNou[i].producator, strlen(vector[i].producator) + 1, vector[i].producator);
    }
    return vectorNou;
}

void afisare(struct Telefon t)
{
    if (t.producator != NULL)
    {
        printf("%d. Telefonul %s seria %c are %d Gb RAM si costa %5.2f RON\n",
            t.id, t.producator, t.serie, t.RAM, t.pret);
    }
    else
    {
        printf("%d. Telefonul din seria %c are %d Gb RAM si costa %5.2f RON\n",
            t.id, t.serie, t.RAM, t.pret);
    }
}


void afisareVector(struct Telefon* vector, int nrElemente)
{
    for (int i = 0; i < nrElemente; i++)
    {
        afisare(vector[i]);
    }
}

void modificaPret(struct Telefon* t, float noulPret)
{
    if (noulPret > 0)
    {
        t->pret = noulPret;
    }
}

void dezalocare(struct Telefon** vector, int* nrElemente)
{
   
        for (int i = 0; i < (*nrElemente); i++)
        {
            if ((*vector)[i].producator != NULL)
            {
                free((*vector)[i].producator);
            }
            free(*vector);
            *vector = NULL;
            *nrElemente = 0;
   }
}


void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune)
{
    *dimensiune = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        if (vector[i].pret >= pretMinim)
        {
            (*dimensiune)++;
        }
    }
    if ((*vectorNou) != NULL)
    {
        free(*vectorNou);
    }
    *vectorNou= (struct Telefon*)malloc(sizeof(struct Telefon) * (*dimensiune));
    int k = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        if (vector[i].pret >= pretMinim)
        {
            (*vectorNou)[k] = vector[i];
            (*vectorNou)[k].producator = (char*)malloc(strlen(vector[i].producator) + 1);
            strcpy_s((*vectorNou)[k].producator, strlen(vector[i].producator) + 1, vector[i].producator);
            k++;
        }

    }
  
}

int main()
{
    struct Telefon* telefoane = NULL;
    int nrTelefoane=3;
    telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
    telefoane[0] = initializare(1, 256, "Samsung", 2000, 'S');
    telefoane[1] = initializare(2, 256, "Motorola", 2000, 'M');
    telefoane[2] = initializare(3, 256, "Apple", 2000, 'A');

    afisareVector(telefoane, nrTelefoane);

    struct Telefon* primeleTelefoane = NULL;
    int nrPrimeleTelefoane = 2;

    primeleTelefoane = CopiazaPrimeleNElemente(telefoane, nrTelefoane, nrPrimeleTelefoane);
    printf("\n\nPrimele telefoane:\n");
    afisareVector(primeleTelefoane, nrPrimeleTelefoane);
    dezalocare(&primeleTelefoane, &nrPrimeleTelefoane);
    afisareVector(primeleTelefoane, nrPrimeleTelefoane);

    struct Telefon* TelefoaneScumpe = NULL;
    int nrTelefoaneScumpe = 0;
    copiazaTelefoaneScumpe(telefoane, nrTelefoane, 2000, &TelefoaneScumpe, &nrTelefoaneScumpe);
    printf("\n\nTelefoane scumpe\n");
    afisareVector(TelefoaneScumpe, nrTelefoaneScumpe);
    dezalocare(&TelefoaneScumpe, &nrTelefoaneScumpe);
    return 0;
}