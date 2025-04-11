//TEMA 1 SDD
//Se consideră prima literă din numele vostru, și prima literă din prenumele vostru. 
//Sa se construiască un articol care să conțină cele două litere.
//Articolul trebuie să aibă logica.Articolul trebuie sa fie un substantiv.Articolul trebuie sa aibă cel puțin trei atribute, si cel puțin unul să fie alocat dinamic.
//Realizati o functie cu ajutorul careia sa cititi de la tastatura un articol de tipul construit de voi.Funcția returnează obiectul citit.
//Realizati o functie care calculeaza ceva pentru un obiect de tipul implementat de voi. (o medie sau o suma, un maxim, un minim...sau orice altceva)
//Realizati o functie care modifica pentru un obiect primit ca parametru, un anumit camp.noua valoare este primita ca parametru.
//Realizați o funcție care afișează un obiect de tipul creat.Afișarea se face la console, și sunt afișate toate informațiile.

//Numele meu: Oranceanu Stefan  -> primele litere  O si S -> aleg Articolul Ospatar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ospatar //articolul conține cele două litere, O de la Oranceanu si S de la Stefan
{
    int id;
    char* nume;
    float salariu;
};

struct Ospatar initializare(int id, const char* nume, float salariu)
{
    struct Ospatar o;
    o.id = id;
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
            o.id, o.nume, o.salariu);
    }
    else
    {
        printf("%d. Ospatarul are salariul %5.2f RON\n",
            o.id,o.salariu);
    }
}


void modificaSalariu(struct Ospatar* o, float noulSalariu)//modifica pentru un obiect primit ca parametru
{
    if (noulSalariu > 0)
    {
        o->salariu = noulSalariu;
    }
}


void calculeaza_salariu(struct Ospatar* o)//calculeaza noul salariu dupa marirea acestuia
{
    int crestere_salariu;
    printf("Introdu cu cat se mareste salariul:\n");
    printf("cresterea salariului= ");
    scanf_s("%d", &crestere_salariu);
    if (crestere_salariu > 0)
    {
        o->salariu = o->salariu + crestere_salariu;
    }
}

void citeste(struct Ospatar* o)//citeste de la tastatura un articol de tipul construit
{
    int a; //ptr cod
    char nm[50];//ptr nume
    float c; // ptr salariu



    printf("Introdu codul, numele si salariul ospatarului:\n");

    printf("cod = ");
    scanf_s("%d", &a);

    printf("nume = ");
    scanf_s("%s", &nm, 50);

    printf("salariu = ");
    scanf_s("%f", &c);

    printf("Ai introdus: cod = %d, nume = %s, salariu = %f\n", a, nm, c);

    *o = initializare(a, nm, c);// modific structura la care pointează o
}


void dezalocare(struct Ospatar* o)
{
    if (o->nume != NULL)
    {
        free(o->nume);
        o->nume = NULL;
    }
}

int main()
{
    struct Ospatar o;
    citeste(&o);
    printf("In luna ianuarie:    ");
    afisare(o);

    printf("In luna februarie:   ");
    modificaSalariu(&o, 3000);
    afisare(o);

    printf("In luna martie:      ");
    modificaSalariu(&o, 4000);
    afisare(o);

    printf("In luna aprilie:     ");
    calculeaza_salariu(&o);
    afisare(o);

    dezalocare(&o);
  //  afisare(o);

    return 0;
}