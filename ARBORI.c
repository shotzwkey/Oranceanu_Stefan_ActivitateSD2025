#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraOspatar {
	int id;
	int varsta;
	float salariu;
	char* nume;
	char* restaurant;
	unsigned char nivelExperienta;
};
typedef struct StructuraOspatar Ospatar;

typedef struct Nod Nod;
struct Nod {
	Nod* st;
	Nod* dr;
	Ospatar info;
};

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
	o.nume = malloc(strlen(aux) + 1);
	strcpy(o.nume, aux);
	aux = strtok(NULL, sep);
	o.restaurant = malloc(strlen(aux) + 1);
	strcpy(o.restaurant, aux);
	o.nivelExperienta = *strtok(NULL, sep);
	return o;
}

void afisareOspatar(Ospatar o) {
	printf("Id: %d\n", o.id);
	printf("Varsta: %d\n", o.varsta);
	printf("Salariu: %.2f\n", o.salariu);
	printf("Nume: %s\n", o.nume);
	printf("Restaurant: %s\n", o.restaurant);
	printf("Nivel Experienta: %c\n\n", o.nivelExperienta);
}

void adaugaOspatarInArbore(Nod** radacina, Ospatar oNou) {
	if ((*radacina) != NULL) {
		if (oNou.id < (*radacina)->info.id) {
			adaugaOspatarInArbore(&((*radacina)->st), oNou);
		}
		else if (oNou.id > (*radacina)->info.id) {
			adaugaOspatarInArbore(&((*radacina)->dr), oNou);
		}
		else {
			if ((*radacina)->info.nume != NULL) free((*radacina)->info.nume);
			if ((*radacina)->info.restaurant != NULL) free((*radacina)->info.restaurant);
			(*radacina)->info.varsta = oNou.varsta;
			(*radacina)->info.salariu = oNou.salariu;
			(*radacina)->info.nivelExperienta = oNou.nivelExperienta;
			(*radacina)->info.nume = malloc(strlen(oNou.nume) + 1);
			strcpy((*radacina)->info.nume, oNou.nume);
			(*radacina)->info.restaurant = malloc(strlen(oNou.restaurant) + 1);
			strcpy((*radacina)->info.restaurant, oNou.restaurant);
		}
	}
	else {
		(*radacina) = malloc(sizeof(Nod));
		(*radacina)->info = oNou;
		(*radacina)->info.nume = malloc(strlen(oNou.nume) + 1);
		strcpy((*radacina)->info.nume, oNou.nume);
		(*radacina)->info.restaurant = malloc(strlen(oNou.restaurant) + 1);
		strcpy((*radacina)->info.restaurant, oNou.restaurant);
		(*radacina)->st = NULL;
		(*radacina)->dr = NULL;
	}
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(file)) {
		Ospatar o = citireOspatarDinFisier(file);
		adaugaOspatarInArbore(&radacina, o);
		free(o.nume);
		free(o.restaurant);
	}
	fclose(file);
	return radacina;
}

void afisareOspatariInOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareOspatariInOrdine(radacina->st);
		afisareOspatar(radacina->info);
		afisareOspatariInOrdine(radacina->dr);
	}
}

void dezalocareArbore(Nod** radacina) {
	if ((*radacina) != NULL) {
		dezalocareArbore(&((*radacina)->st));
		dezalocareArbore(&((*radacina)->dr));
		free((*radacina)->info.nume);
		free((*radacina)->info.restaurant);
		free(*radacina);
		*radacina = NULL;
	}
}

Ospatar getOspatarByID(Nod* radacina, int id) {
	Ospatar o;
	o.id = -1;
	if (radacina == NULL) return o;

	if (id > radacina->info.id) {
		return getOspatarByID(radacina->dr, id);
	}
	else if (id < radacina->info.id) {
		return getOspatarByID(radacina->st, id);
	}
	else {
		o = radacina->info;
		o.nume = malloc(strlen(radacina->info.nume) + 1);
		strcpy(o.nume, radacina->info.nume);
		o.restaurant = malloc(strlen(radacina->info.restaurant) + 1);
		strcpy(o.restaurant, radacina->info.restaurant);
		return o;
	}
}

int determinaNumarNoduri(Nod* radacina) {
	if (radacina != NULL) {
		return 1 + determinaNumarNoduri(radacina->st) + determinaNumarNoduri(radacina->dr);
	}
	else {
		return 0;
	}
}

int main() {
	Nod* arbore = citireArboreDinFisier("ospatari.txt");
	afisareOspatariInOrdine(arbore);

	Ospatar o = getOspatarByID(arbore, 2);
	printf("\n\n---------------\n");
	afisareOspatar(o);

	int i = determinaNumarNoduri(arbore);
	printf("\nNumar ospatari in arbore: %d\n", i);

	dezalocareArbore(&arbore);
	return 0;
}