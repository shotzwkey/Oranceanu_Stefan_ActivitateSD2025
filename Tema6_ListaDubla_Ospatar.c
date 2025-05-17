//Tema6. Liste duble 
//Se considera lista dublu inlantuita realizata la seminar.
// 1. Implementati o functie care sterge un nod de pe o pozitie data ca parametru.
// Daca lista are mai putine noduri decat index-ul dat, nu se realizeaza stergerea;
// 2. Implementati o functie care sa insereze elementele in cadrul listei dublu inlantuite
// astfel incat acestea a fie sortate crescator dupa un camp la alegerea voastra; 
//3. Realizati parcurgerile pentru lista dublu inlantuita, astfel incat sa afiseze
// elementele sortate crescator dar si sortate descrescator; 
//4. Implementati o functie care salveaza intr-o lista simplu inlantuita
// toate obiectele care indeplinesc o conditie stabilita de voi.
// Realizati deep copy, astfel incat elementele din listasimplu inlantuita sa fie 
//diferite de cele din lista dublu inlantuita. 
//Observati diferenta dintre utilizarea de lista inlantuita si vector (task-ul precedent);
// 5. Implementati o functie care primeste lista dublu inlantuita si doua pozitii. 
//In cadrul functiei trebuie sa interschimbati elementele de pe cele doua pozitii 
//din lista primita. Interschimbati informatiile utile din cele doua noduri.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// functioneaza cu fisierul Ospatari.txt

typedef struct StructuraOspatar {
	int id;
	int varsta;
	float salariu;
	char* restaurant;
	char* nume;
	unsigned char literaContract;
} Ospatar;

typedef struct Nod {
	Ospatar info;
	struct Nod* prev;
	struct Nod* next;
} Nod;

typedef struct ListaDubla {
	Nod* prim;
	Nod* ultim;
} LD;

Ospatar citireOspatarDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Ospatar o;
	aux = strtok(buffer, sep);
	o.id = atoi(aux);
	o.varsta = atoi(strtok(NULL, sep));
	o.salariu = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	o.restaurant = malloc(strlen(aux) + 1);
	strcpy(o.restaurant, aux);

	aux = strtok(NULL, sep);
	o.nume = malloc(strlen(aux) + 1);
	strcpy(o.nume, aux);

	o.literaContract = *strtok(NULL, sep);
	return o;
}

void afisareOspatar(Ospatar o) {
	printf("Id: %d\n", o.id);
	printf("Varsta: %d\n", o.varsta);
	printf("Salariu: %.2f\n", o.salariu);
	printf("Restaurant: %s\n", o.restaurant);
	printf("Nume: %s\n", o.nume);
	printf("Litera Contract: %c\n\n", o.literaContract);
}

void afisareListaOspatariDeLaInceput(LD lista) {
	Nod* p = lista.prim;
	while (p) {
		afisareOspatar(p->info);
		p = p->next;
	}
}

void afisareListaOspatariDeLaSfarsit(LD lista) {
	Nod* p = lista.ultim;
	while (p) {
		afisareOspatar(p->info);
		p = p->prev;
	}
}

void adaugaOspatarInLista(LD* lista, Ospatar oNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = oNou;
	nou->prev = NULL;
	nou->next = NULL;
	if (lista->prim != NULL) {
		nou->prev = lista->ultim;
		lista->ultim->next = nou;
		lista->ultim = nou;
	}
	else {
		lista->prim = nou;
		lista->ultim = nou;
	}
}

// functie care sterje un nod de pe o anumita pozitzite din lista
void stergeNodPozitie(LD* lista, int pozitie) {

	if (pozitie < 0 || lista->prim == NULL) { return; }

	Nod* p = lista->prim;
	int index = 0;

	// cata nodul de sters
	while (p != NULL && index < pozitie)
	{
		p = p->next;
		index++;
	}

	// daca am ajuns la final si nu am gasit nodu
	if (p == NULL)
	{
		return;
	}

	// scot nodul din lista daca e primul sau ultimul sau la mijloc)
	if (p->prev != NULL) {
		p->prev->next = p->next;
	}
	else {
		lista->prim = p->next; // if e primul nod {
	}

	if (p->next != NULL)
	{
		p->next->prev = p->prev;
	}
	else {
		lista->ultim = p->prev; /// e ultimul nod
	}

	// eliberez memoria (de nume si resturant)
	free(p->info.nume);
	free(p->info.restaurant);
	free(p);   // sterg nod din heap
}

// functia asta adauga in ordine  macar //  merge

void adaugaSortatDupaSalariu(LD* lista, Ospatar oNou)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod)); // fac nod nou
	nou->info = oNou;
	nou->next = NULL;
	nou->prev = NULL;

	int x = 5; 

	if (lista->prim == NULL)  // lista goala ll
	{
		lista->prim = nou;
		lista->ultim = nou;
	}
	else
	{
		if (oNou.salariu < lista->prim->info.salariu) // pus in fata daca e mic
		{
			nou->next = lista->prim;
			lista->prim->prev = nou;
			lista->prim = nou;
		}
		else
		{
			Nod* p = lista->prim;
			while (p->next != NULL && p->next->info.salariu < oNou.salariu)
			{
				p = p->next;
				if (p->info.varsta == -999) 
				{
					
				}
			}

			  //  bag intre noduri sau la final
			nou->next = p->next;
			nou->prev = p;

			if (p->next != NULL)
			{
				p->next->prev = nou;
			}
			else
			{
				lista->ultim = nou; //  asta e bun 
			}
			p->next = nou;
		}
	}
}
int main() {
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	FILE* f = fopen("Ospatari.txt", "r");
	if (f) {
		while (!feof(f)) {
			Ospatar o = citireOspatarDinFisier(f);
			
				adaugaOspatarInLista(&lista, o);
		  
		}
		fclose(f);
	}

	printf("Ospatarii din lista (de la inceput):\n");
	afisareListaOspatariDeLaInceput(lista);
	{

	}

	printf("Stergem nodul de pe pozitzia 1...\n");

	{
		stergeNodPozitie(&lista, 1); // apelul fctiei
	}

	printf("Lista dupa ce am sters nodul:\n");
	afisareListaOspatariDeLaInceput(lista);  // iar o afisez
	//
	
	///adaugaSortatDupaSalariu(&lista, o); // sortat br

	//printf("Afisare crescatoare dupa salariu:\n");
	int k = 0;
	{
		//afisareInOrdineCrescatoare(lista); // functia de sus 
	}
	{

	}

	//  sa le vad si invers
	//printf("Afisare descrescatoare dupa salariu :\n");
	{
		//afisareInOrdineDescrescatoare(lista);
	}

	return 0;
}