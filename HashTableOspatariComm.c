#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// asta e structura care tine info despre ospatari
//  ce  ar fi relevant pt un ospatar
struct StructuraOspatar {
	int id; // un fel de cod unic pt fiecare ospatar
	int aniExperienta; // 
	float salariu; // salariul actual 
	char* restaurant; // la ce restaurant lucreaza
	char* numeOspatar; // numele lui complet
	unsigned char nivelCertificare; // un fel de A, B, C... pt skill level
};
typedef struct StructuraOspatar Ospatar;

// nod standard pt o lista simpla (linked list)
struct Nod {
	Ospatar ospatar;
	struct Nod* next;
};
typedef struct Nod Nod;

// hash table-ul unde stocam toti ospatarii (pe bucati)
struct HashTable {
	int dim; // dimensiunea tabelei
	Nod** tabela; // tabela e un vector de pointeri la Nod
};
typedef struct HashTable HashTable;

// citeste un ospatar din fisier (linia aia cu datele lui)
// separa cu strtok valorile de pe linie si le pune in structura
Ospatar citireOspatarDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file); // citeste linia

	char* aux;
	Ospatar o;

	// luam valorile una cate una si le bagam in struct
	aux = strtok(buffer, sep);
	o.id = atoi(aux);

	o.aniExperienta = atoi(strtok(NULL, sep));
	o.salariu = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	o.restaurant = malloc(strlen(aux) + 1);
	strcpy(o.restaurant, aux);

	aux = strtok(NULL, sep);
	o.numeOspatar = malloc(strlen(aux) + 1);
	strcpy(o.numeOspatar, aux);

	// ultimul e caracterul de certificare (un char)
	o.nivelCertificare = *strtok(NULL, sep);

	return o;
}

// doar afiseaza un ospatar, asa cu tot ce stim despre el
void afisareOspatar(Ospatar o) {
	printf("Id: %d\n", o.id);
	printf("Ani experienta: %d\n", o.aniExperienta);
	printf("Salariu: %.2f\n", o.salariu);
	printf("Restaurant: %s\n", o.restaurant);
	printf("Nume ospatar: %s\n", o.numeOspatar);
	printf("Nivel certificare: %c\n\n", o.nivelCertificare);
}

// parcurge o lista si afiseaza fiecare ospatar
void afisareListaOspatari(Nod* cap) {
	while (cap) {
		afisareOspatar(cap->ospatar);
		cap = cap->next;
	}
}

// adauga un nou ospatar in lista, la final
void adaugaOspatarInLista(Nod* cap, Ospatar o) {
	Nod* p = cap;
	while (p->next) {
		p = p->next;
	}
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->ospatar = o;
	nou->next = NULL;
	p->next = nou;
}

// creaza tabela (aloca spatiu si initializeaza cu NULL)
HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) {
		ht.tabela[i] = NULL;
	}
	return ht;
}

// calculeaza un hash din numele ospatarului
int calculeazaHash(const char* nume, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(nume); i++) {
		suma += nume[i];
	}
	return suma % dimensiune;
}

// insereaza un ospatar in tabela, in functie de hash
void inserareOspatarInTabela(HashTable hash, Ospatar o) {
	int pozitie = calculeazaHash(o.numeOspatar, hash.dim);
	if (hash.tabela[pozitie] == NULL) {
		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->ospatar = o;
		hash.tabela[pozitie]->next = NULL;
	}
	else {
		adaugaOspatarInLista(hash.tabela[pozitie], o);
	}
}

// citeste tot fisierul linie cu linie si baga ospatarii in hash table
HashTable citireOspatariDinFisier(const char* numeFisier, int dimensiune) {
	HashTable hash = initializareHashTable(dimensiune);

	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		perror("Eroare la deschiderea fisierului"); // in caz ca am uitat sa punem fisierul
		return hash;
	}

	while (!feof(f)) {
		Ospatar o = citireOspatarDinFisier(f);
		inserareOspatarInTabela(hash, o);
	}
	fclose(f);
	return hash;
}

// afiseaza toata tabela cu ospatari pe fiecare pozitie
void afisareTabelaDeOspatari(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			printf("\nOspatarii de pe pozitia %d sunt:\n", i);
			afisareListaOspatari(ht.tabela[i]);
		}
		else {
			printf("\nPe pozitia %d nu avem ospatari\n", i); // goala pozitia
		}
	}
}

// scoate tot din memorie pt lista data
void dezalocareListaOspatari(Nod** cap) {
	Nod* p = *cap;
	while (p) {
		Nod* temp = p;
		p = p->next;

		// elibereaza stringurile
		if (temp->ospatar.restaurant != NULL) free(temp->ospatar.restaurant);
		if (temp->ospatar.numeOspatar != NULL) free(temp->ospatar.numeOspatar);

		free(temp);
	}
	*cap = NULL;
}

// elibereaza toata tabela
void dezalocareTabelaDeOspatari(HashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {
		dezalocareListaOspatari(&(ht->tabela[i]));
	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;
}

// calculeaza media salariilor pt o lista de ospatari (gen un cluster)
float calculeazaMedieLista(Nod* cap) {
	float suma = 0;
	int nrElemente = 0;
	while (cap) {
		suma += cap->ospatar.salariu;
		nrElemente++;
		cap = cap->next;
	}
	return (nrElemente > 0 ? (suma / nrElemente) : 0);
}

// asta intoarce un vector cu media salariilor pe clustere (doar pt cele ocupate)
float* calculeazaSalariiMediiPerClustere(HashTable ht, int* nrClustere) {
	float* salarii = NULL;
	*nrClustere = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			(*nrClustere)++;
		}
	}
	salarii = (float*)malloc(sizeof(float) * (*nrClustere));
	int contor = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			salarii[contor] = calculeazaMedieLista(ht.tabela[i]);
			contor++;
		}
	}
	return salarii;
}

// cauta un ospatar in lista, dupa nume
Ospatar getOspatarDinLista(Nod* cap, const char* nume) {
	Ospatar o;
	o.id = -1; // default, daca nu gasim nimic
	while (cap && strcmp(cap->ospatar.numeOspatar, nume) != 0) {
		cap = cap->next;
	}
	if (cap) {
		o = cap->ospatar;
		o.restaurant = (char*)malloc(strlen(cap->ospatar.restaurant) + 1);
		strcpy(o.restaurant, cap->ospatar.restaurant);
		o.numeOspatar = (char*)malloc(strlen(cap->ospatar.numeOspatar) + 1);
		strcpy(o.numeOspatar, cap->ospatar.numeOspatar);
	}
	return o;
}

// cauta un ospatar dupa nume in tabela hash
Ospatar getOspatarDupaNume(HashTable ht, const char* numeCautat) {
	Ospatar o;
	o.id = -1;
	int poz = calculeazaHash(numeCautat, ht.dim);
	if (poz >= 0 && poz < ht.dim) {
		return getOspatarDinLista(ht.tabela[poz], numeCautat);
	}
	return o;
}

// aici se intampla totul - mainul e simplu
int main() {
	HashTable ht = citireOspatariDinFisier("ospatari.txt", 7);

	afisareTabelaDeOspatari(ht);

	int nrClustere = 0;
	float* salarii = calculeazaSalariiMediiPerClustere(ht, &nrClustere);

	printf("Salariile medii per clustere sunt:\n");
	for (int i = 0; i < nrClustere; i++) {
		printf("%.2f  ", salarii[i]);
	}
	printf("\n");

	Ospatar o = getOspatarDupaNume(ht, "Ion Popescu");

	if (o.id != -1) {
		printf("Ospatarul cautat:\n");
		afisareOspatar(o);
		if (o.restaurant != NULL) free(o.restaurant);
		if (o.numeOspatar != NULL) free(o.numeOspatar);
	}
	else {
		printf("Ospatarul nu a fost gasit.\n");
	}

	dezalocareTabelaDeOspatari(&ht);
	return 0;
}