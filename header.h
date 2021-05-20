#ifndef HEADER_H
#define HEADER_H

typedef struct ulaznica {
	char ime_eventa[100];
	char cijena_eventa[50];
	int godina_izdanja;
	char dostupne_ul[50];
}ULAZNICA;

/*
typedef struct ulaznica {
	char ime_eventa[100];
	char cijena_eventa[50];
	int godina_izdanja;
	char dostupne_ul[50];
}ULAZNICA;
*/

int nova_ulaznica();

void pretrazivanje(char);

void ispisUlaznice(ULAZNICA*);

int ispis_ulaznica();

void izbornik_pretrazivanje();

void sortiranje_po_imenu_eventa_silazno(ULAZNICA*, int);

void sortiranje_po_imenu_eventa_uzlazno(ULAZNICA*, int);

void sortiranje_po_imenu_redatelja_silazno(ULAZNICA*, int);

void sortiranje_po_imenu_redatelja_uzlazno(ULAZNICA*, int);

void sortiranje_po_vrsti_djela_silazno(ULAZNICA*, int);

void sortiranje_po_vrsti_djela_uzlazno(ULAZNICA*, int);

void sortiranje_po_godini_silazno(ULAZNICA*, int);

void sortiranje_po_godini_uzlazno(ULAZNICA*, int);

void sortiranje_izbornik();

void brisanje_ulaznice();

void uredivanje_ulaznice();

void izlazak_iz_programa();

#endif
