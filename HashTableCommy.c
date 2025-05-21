#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aici am definit o structura pt masina... are un ID, nr de usi, pret, model, sofer si o serie
struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

// nod pt lista inlantuita - o sa legam masinile in caz de coliziune in hash table
struct Nod {
	Masina masina;
	struct Nod* next;
};
typedef struct Nod Nod;

// structura pt hash table - adica "tabela" propriu-zisa
struct HashTable {
	int dim;
	Nod** tabela;
};
typedef struct HashTable HashTable;

// Functie de citire masina din fisier 
Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100]; // aici salvam linia citita
	char sep[3] = ",\n"; // separatorii, adica virgula si enterul
	fgets(buffer, 100, file); // luam o linie
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep); // luam primul camp
	m1.id = atoi(aux); // convertim la int
	m1.nrUsi = atoi(strtok(NULL, sep)); // urmatorul camp
	m1.pret = atof(strtok(NULL, sep)); // pretul, care e float

	// modelul
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy(m1.model, aux);

	// numele soferului
	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer, aux);

	// seria, e doar un char
	m1.serie = *strtok(NULL, sep);
	return m1;
}

// afisare masina  pe ecran
void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

// functie pt cand vrem sa afisam o lista intreaga de masini 
void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->masina);
		cap = cap->next;
	}
}

// Adaugam o masina la sfarsitul listei - folosita la coliziuni
void adaugaMasinaInLista(Nod* cap, Masina masinaNoua) {
	Nod* p = cap;
	while (p->next) { // mergem pana la ultimul nod
		p = p->next;
	}
	Nod* nou = (Nod*)malloc(sizeof(Nod)); // facem un nod nou
	nou->masina = masinaNoua;
	nou->next = NULL;
	p->next = nou; // il lipim la coada
}

// Initializam tabela hash, toate sloturile goale
HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) {
		ht.tabela[i] = NULL; // fiecare slot e NULL la inceput
	}
	return ht;
}

// Functie simpla de hash - aduna caracterele din nume si face modulo
int calculeazaHash(const char* nume, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(nume); i++) {
		suma += nume[i];
	}
	return suma % dimensiune;
}

// Inseram masina in tabela - daca e gol slotul, punem direct; daca nu, o bagam in lista
void inserareMasinaInTabela(HashTable hash, Masina masina) {
	int pozitie = calculeazaHash(masina.numeSofer, hash.dim);
	if (hash.tabela[pozitie] == NULL) {
		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->masina = masina;
		hash.tabela[pozitie]->next = NULL;
	}
	else {
		adaugaMasinaInLista(hash.tabela[pozitie], masina);
	}
}

// Citim toate masinile din fisier si le bagam in tabela
HashTable citireMasiniDinFisier(const char* numeFisier, int dimensiune) {
	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		printf("Eroare la deschiderea fisierului %s\n", numeFisier);
		exit(1);
	}
	while (!feof(f)) {
		Masina masina = citireMasinaDinFisier(f);
		inserareMasinaInTabela(hash, masina);
	}
	fclose(f);
	return hash;
}

// Afisam toata tabela - si sloturile goale si cele pline
void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			printf("\nMasinile de pe pozitia %d sunt:\n", i);
			afisareListaMasini(ht.tabela[i]);
		}
		else {
			printf("\nPe pozitia %d nu avem masini\n", i);
		}
	}
}

// Dezalocam o lista de masini - important pt memory leaks
void dezalocareListaMasini(Nod** cap) {
	Nod* p = *cap;
	while (p) {
		Nod* temp = p;
		p = p->next;
		if (temp->masina.model != NULL) {
			free(temp->masina.model);
		}
		if (temp->masina.numeSofer != NULL) {
			free(temp->masina.numeSofer);
		}
		free(temp);
	}
	*cap = NULL;
}

// La final dezalocam si tabela hash
void dezalocareTabelaDeMasini(HashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {
		dezalocareListaMasini(&(ht->tabela[i]));
	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;
}

// Calculeaza media preturilor pt o lista - ca sa vedem cat de scumpi suntem pe un slot
float calculeazaMedieLista(Nod* cap) {
	float suma = 0;
	int nrElemente = 0;
	while (cap) {
		suma += cap->masina.pret;
		nrElemente++;
		cap = cap->next;
	}
	return (nrElemente > 0 ? (suma / nrElemente) : 0);
}

// Calculeaza preturile medii pt fiecare cluster (slot cu cel putin o masina)
float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	float* preturi = NULL;
	*nrClustere = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			(*nrClustere)++; // numaram cate clustere avem
		}
	}
	preturi = (float*)malloc(sizeof(float) * (*nrClustere)); // alocam vectorul
	int contor = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			preturi[contor] = calculeazaMedieLista(ht.tabela[i]);
			contor++;
		}
	}
	return preturi;
}

// Cauta masina intr-o lista (un slot din tabela)
Masina getMasinaDinLista(Nod* cap, const char* nume) {
	Masina m;
	m.id = -1;
	while (cap && strcmp(cap->masina.numeSofer, nume) != 0) {
		cap = cap->next;
	}
	if (cap) {
		m = cap->masina;
		m.model = (char*)malloc(strlen(cap->masina.model) + 1);
		strcpy(m.model, cap->masina.model);
		m.numeSofer = (char*)malloc(strlen(cap->masina.numeSofer) + 1);
		strcpy(m.numeSofer, cap->masina.numeSofer);
	}
	return m;
}

// Cauta o masina in tabela dupa numele soferului
Masina getMasinaDupaNumeSofer(HashTable ht, const char* numeCautat) {
	Masina m;
	m.id = -1;
	int poz = calculeazaHash(numeCautat, ht.dim);
	if (poz >= 0 && poz < ht.dim) {
		return getMasinaDinLista(ht.tabela[poz], numeCautat);
	}
	return m;
}

int main() {
	// Cream tabela si citim masinile din fisier
	HashTable ht = citireMasiniDinFisier("masini.txt", 7);
	afisareTabelaDeMasini(ht);

	// Afisam mediile de pret pe fiecare cluster
	int nrClustere = 0;
	float* preturi = calculeazaPreturiMediiPerClustere(ht, &nrClustere);

	printf("Preturile medii per clustere sunt:\n");
	for (int i = 0; i < nrClustere; i++) {
		printf("%.2f  ", preturi[i]);
	}
	printf("\n");

	// Testam cautarea dupa un nume de sofer
	Masina masina = getMasinaDupaNumeSofer(ht, "Gigel Gigel");

	if (masina.id != -1) {
		printf("Masina cautata:\n");
		afisareMasina(masina);
		if (masina.model != NULL) {
			free(masina.model);
		}
		if (masina.numeSofer != NULL) {
			free(masina.numeSofer);
		}
	}
	else {
		printf("Masina nu a fost gasita. Soferul respectiv nu are nicio masina.\n");
	}

	free(preturi);
	dezalocareTabelaDeMasini(&ht);
	return 0;
}