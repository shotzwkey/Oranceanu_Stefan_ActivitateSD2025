//TEMA2

//Considerati codul de la task - ul precedent.

//Creati in functia main un vector alocat dinamic cu cel putin 5 obiecte de tipul structurii voastre.

//Realizati o functie care va crea un nou vector în care va copia dintr - un vector primit ca parametru obiectele care indeplinesc o anumita conditie.Stabiliti voi conditia in functie de un atribut sau doua atribute.

//Realizati o functie care muta intr - un nou vector obiectele care indeplinesc o alta conditie fata de cerinta precedenta.

//Realizati o functie care concateneaza doi vectori.

//Realizati o functie care afiseaza un vector cu obiecte.

//Apelati toate aceste functii in main().


//Numele meu: Oranceanu Stefan  -> primele litere  O si S -> aleg Articolul Ospatar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ospatar //un articol care să conțină cele două litere, O de la Oranceanu si S de la Stefan
{
    int vechime;
    char* nume;
    float salariu;
};

struct Ospatar initializare(int vechime, const char* nume, float salariu)
{
    struct Ospatar o;
    o.vechime = vechime;
    o.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    if (o.nume != NULL)
    {
        strcpy_s(o.nume, strlen(nume) + 1, nume);
    }
    o.salariu = salariu;
    return o;
}

void afisare(struct Ospatar o) //afișează un obiect de tipul creat
{
    if (o.nume != NULL)
    {
        printf("%d. Ospatarul %s are salariul %5.2f RON\n",
            o.vechime, o.nume, o.salariu);
    }
    else
    {
        printf("%d. Ospatarul are salariul %5.2f RON\n",
            o.vechime, o.salariu);
    }
}


void afisareVector(struct Ospatar* vector, int nrElemente)//afiseaza un vector cu obiecte
{
    for (int i = 0; i < nrElemente; i++)
    {
        afisare(vector[i]);
    }
}

void afisareCuVechime(struct Ospatar o) //afișează un obiect de tipul creat
{
    if (o.nume != NULL)
    {
        printf("%d. Ospatarul %s are vechimea %d ani\n",
            o.vechime, o.nume, o.vechime);
    }
    else
    {
        printf("%d. Ospatarul are salariul %d ani\n",
            o.vechime, o.vechime);
    }
}


void afisareVectorCuVechime(struct Ospatar* vector, int nrElemente)//afiseaza un vector cu obiecte
{
    for (int i = 0; i < nrElemente; i++)
    {
        afisareCuVechime(vector[i]);
    }
}


void dezalocare(struct Ospatar** vector, int* nrElemente)
{

    for (int i = 0; i < (*nrElemente); i++)
    {
        if ((*vector)[i].nume != NULL)
        {
            free((*vector)[i].nume);
        }
        free(*vector);
        *vector = NULL;
        *nrElemente = 0;
    }
}

//functie care va crea un nou vector în care va copia  dintr - un vector 
// primit ca parametru obiectele care indeplinesc conditia sa aiba salariul mare
void copiazaOspatariPriceputi(struct Ospatar* vector, char nrElemente, float salariuMinim, struct Ospatar** vectorNou, int* dimensiune)
{
    *dimensiune = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        if (vector[i].salariu >= salariuMinim)
        {
            (*dimensiune)++;
        }
    }
    if ((*vectorNou) != NULL)
    {
        free(*vectorNou);
    }
    *vectorNou = (struct Ospatar*)malloc(sizeof(struct Ospatar) * (*dimensiune));
    int k = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        if (vector[i].salariu >= salariuMinim)
        {
            (*vectorNou)[k] = vector[i];
            (*vectorNou)[k].nume = (char*)malloc(strlen(vector[i].nume) + 1);
            strcpy_s((*vectorNou)[k].nume, strlen(vector[i].nume) + 1, vector[i].nume);
            k++;
        }

    }

}

//functie care va crea un nou vector în care va muta  dintr - un vector 
// primit ca parametru obiectele care indeplinesc conditia sa aiba vechimea mare
void mutaOspatariVechi(struct Ospatar* vector, char nrElemente, float vechimeMinima, struct Ospatar** vectorNou, int* dimensiune)
{
    *dimensiune = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        if (vector[i].vechime >= vechimeMinima)
        {
            (*dimensiune)++;
        }
    }
    if ((*vectorNou) != NULL)
    {
        free(*vectorNou);
    }
    *vectorNou = (struct Ospatar*)malloc(sizeof(struct Ospatar) * (*dimensiune));
    int k = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        if (vector[i].vechime >= vechimeMinima)
        {
            (*vectorNou)[k] = vector[i];
            (*vectorNou)[k].nume = (char*)malloc(strlen(vector[i].nume) + 1);
            strcpy_s((*vectorNou)[k].nume, strlen(vector[i].nume) + 1, vector[i].nume);
            k++;
        }

    }

}

int main()
{
    struct Ospatar* ospatari = NULL;

    //Creez un vector alocat dinamic cu cel putin 5 obiecte de tipul structurii mele.
    int nrOspatari = 5;
    ospatari = (struct Ospatar*)malloc(sizeof(struct Ospatar) * nrOspatari);
    ospatari[0] = initializare(1, "Ion", 2000);
    ospatari[1] = initializare(2, "Vasile", 3000);
    ospatari[2] = initializare(3, "Marin", 4000);
    ospatari[3] = initializare(4, "Gheorghe", 5000);
    ospatari[4] = initializare(5, "Mihai", 6000);

    afisareVector(ospatari, nrOspatari); //afiseaza un vector cu obiecte

    //functie care va crea un nou vector în care va copia  dintr - un vector 
    // primit ca parametru obiectele care indeplinesc conditia sa aiba salariul mare

    struct Ospatar* OspatariPriceputi = NULL;
    int nrOspatariPriceputi = 0;
    copiazaOspatariPriceputi(ospatari, nrOspatari, 3000, &OspatariPriceputi, &nrOspatariPriceputi);
    printf("\n\n Ospatari de top, bine platiti: \n");
    afisareVector(OspatariPriceputi, nrOspatariPriceputi);
    dezalocare(&OspatariPriceputi, &nrOspatariPriceputi);

    //functie care va crea un nou vector în care va muta  dintr - un vector 
    // primit ca parametru obiectele care indeplinesc conditia sa aiba vechimea mare

    struct Ospatar* OspatariVechi = NULL;
    int nrOspatariVechi = 0;
    mutaOspatariVechi(ospatari, nrOspatari, 3, &OspatariVechi, &nrOspatariVechi);
    printf("\n\n Ospatarii cu vechimea cea mai mare: \n");
    afisareVectorCuVechime(OspatariVechi, nrOspatariVechi);
    dezalocare(&OspatariVechi, &nrOspatariVechi);

    return 0;
}