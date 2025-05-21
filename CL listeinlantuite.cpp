#include <iostream>
#include <cstdio>
using namespace std;

struct nod{
    int date;
    nod *next;
};

void afisare(nod *cap){
    while(cap != NULL){
        cout<<cap->date<<" ";
        cap = cap->next;
    }
    cout<<endl;
}

void adaugare_cap(int x, nod*&cap){
    nod *nou = new nod;
    nou->date = x;
    nou->next = cap;
    cap = nou;
}
void adaugare_coada(int x, nod*cap){
    nod *coada = new nod;
    coada->date = x;
    while(cap->next!=NULL){
        cap = cap->next;
    }
    cap->next = coada;
    coada->next = NULL;
}

void stergere_cap(nod *&cap){
    cap = cap->next;
    delete cap;

}

void stergere_coada(nod *cap){
    while(cap->next->next!=NULL){
        cap = cap->next;
    }
    delete cap->next;
    cap->next = NULL;
}

int nr_elemente(nod *cap,int &nrelem){
    while(cap != NULL){
        cap = cap->next;
        nrelem++;
    }
    return nrelem;
}

int suma_elem(nod *cap, int &s){
    s+=cap->date;
    while(cap->next != NULL){
        cap = cap->next;
        s+=cap->date;
    }
    return s;
}

int valoare_minima(nod *cap){
    int min = cap->date;
    while(cap->next != NULL){
        cap = cap->next;
        if(cap->date<min){
            min = cap->date;
        }
    }
    return min;

}

int valoare_maxima(nod *cap){
    int max = cap->date;
    while(cap->next != NULL){
        cap = cap->next;
        if(cap->date>max){
            max = cap->date;
        }
    }
    return max;

}
double medie_artm(nod *cap, double medie){
    medie+=cap->date;
    int nr = 0;
    nr_elemente(cap,nr);
    while(cap->next != NULL){
        cap = cap->next;
        medie+=cap->date;
    }
    medie = medie/nr;
    return medie;


}

int main(void){
    int nrelem = 0;
    int suma = 0;
    double medie;
    nod *cap;
    nod *a = new nod;
    nod *b = new nod;
    nod *c = new nod;
    cap = a;
    a->date = 1;
    a->next = b;

    b->date = 2;
    b->next = c;

    c->date = 3;
    c->next = NULL;

    adaugare_cap(0,cap);
    adaugare_coada(4,cap);
    stergere_cap(cap);
    stergere_coada(cap);
    afisare(cap);
    cout <<"Nr de elemente este : "<<nr_elemente(cap,nrelem)<<endl;
    cout <<"Suma este : "<<suma_elem(cap,suma)<<endl;
    cout <<"Minimul este : "<<valoare_minima(cap)<<endl;
    cout <<"Maximul este : "<<valoare_maxima(cap)<<endl;
    cout <<"Media este : "<<medie_artm(cap,medie)<<endl;
}
