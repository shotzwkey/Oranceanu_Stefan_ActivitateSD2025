//3. Fișiere Considerati codul de la task - ul precedent.
// Creati un fisier in care sa aveti minim 10 obiecte de tipul structurii create.
// Asezarea in fisier a elementelor o faceti la libera alegere.
// Scrieti intr - un program C functia care sa citeasca obiectele din fisier 
// si sa le salveze intr - un vector.
// Scrieti o functie care va salva un obiect intr - un fisier text.
// Scrieti o functie care va salva un vector de obiecte intr - un fisier text.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//folosesc fisierul TEMA_3_FISIER.txt


struct StructuraOspatar {
	int id;
	int Varsta;
	float Salariu;
	char* Nume;
	char* Prenume;
	unsigned char InitialaTatalui;
};
typedef struct StructuraOspatar Ospatar;

void afisareOspatar(Ospatar angajat) {
	printf("ID:%d\n", angajat.id);
	printf("Varsta:%d\n", angajat.Varsta);
	printf("Salariu:%.2f\n", angajat.Salariu);
	printf("Nume:%s\n", angajat.Nume);
	printf("Prenume:%s\n", angajat.Prenume);
	printf("InitialaTatalui:%c\n\n", angajat.InitialaTatalui);

}

void afisareVectorOspatari(Ospatar* EX3_ANGAJATI, int nrAngajati) {
	for (int i = 0; i < nrAngajati; i++)
	{
		afisareOspatar(EX3_ANGAJATI[i]);
	}
}

void adaugaOspatarInVector(Ospatar** EX3_ANGAJATI, int* nrAngajati, Ospatar angajatNou) {
	Ospatar* aux = (Ospatar*)malloc(sizeof(Ospatar) * ((*nrAngajati) + 1));
	for (int i = 0; i < *nrAngajati; i++)
	{
		aux[i] = (*EX3_ANGAJATI)[i];
	}
	aux[(*nrAngajati)] = angajatNou;
	free(*EX3_ANGAJATI);
	(*EX3_ANGAJATI) = aux;
	(*nrAngajati)++;
}

Ospatar citireAngajatFisier(FILE* file) {
	Ospatar m;
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, file);
	m.id = atoi(strtok(buffer, sep));
	m.Varsta = atoi(strtok(NULL, sep));
	m.Salariu = atof(strtok(NULL, sep));
	char* aux;
	aux = strtok(NULL, sep);
	m.Nume = (char*)malloc(strlen(aux) + 1);
	strcpy(m.Nume, aux);
	aux = strtok(NULL, sep);
	m.Prenume = (char*)malloc(strlen(aux) + 1);
	strcpy(m.Prenume, aux);
	m.InitialaTatalui = strtok(NULL, sep)[0];
	return m;


}

Ospatar* citireVectorAngajatiFisier(const char* numeFisier, int* nrAngajatiCititi) {
	FILE* f = fopen(numeFisier, "r");
	Ospatar* EX3_ANGAJATI = NULL;
	(*nrAngajatiCititi) = 0;
	while (!feof(f))
	{
		adaugaOspatarInVector(&EX3_ANGAJATI, nrAngajatiCititi, citireAngajatFisier(f));
	}
	fclose(f);
	return EX3_ANGAJATI;
}

void dezalocareVectorAngajati(Ospatar** vector, int* nrAngajati) {
	for (int i = 0; i < *nrAngajati; i++)
	{
		if (((*vector)[i].Nume) != NULL)
		{
			free((*vector)[i].Nume);
		}

		if (((*vector)[i].Prenume) != NULL)
		{
			free((*vector)[i].Prenume);
		}
		free(*vector);
		(*vector) = NULL;
		(*nrAngajati) = 0;
	}
}

int main() {
	int nrAngajati = 0;
	Ospatar* EX3_ANGAJATI = citireVectorAngajatiFisier("TEMA_3_FISIER.txt", &nrAngajati);
	afisareVectorOspatari(EX3_ANGAJATI, nrAngajati);
	dezalocareVectorAngajati(&EX3_ANGAJATI, &nrAngajati);
	return 0;
}