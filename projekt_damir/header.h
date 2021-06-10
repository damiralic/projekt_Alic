#ifndef HEADER_H
#define HEADER_H

typedef struct ulaznica {
	char ime_eventa[100];
	int cijena_eventa;
	int godina_izdanja;
	int dostupne_ul;
}ULAZNICA;
//ispisivanje svih funkcija

int nova_ulaznica();

void pretrazivanje(char);

void ispisUlaznice(ULAZNICA*);

int ispis_ulaznica();

void izbornik_pretrazivanje();

void sortiranje_po_imenu_eventa_silazno(ULAZNICA*, int);

void sortiranje_po_imenu_eventa_uzlazno(ULAZNICA*, int);

void sortiranje_po_cijeni_eventa_silazno(ULAZNICA*, int);

void sortiranje_po_cijeni_eventa_uzlazno(ULAZNICA*, int);

void sortiranje_po_vrsti_eventa_silazno(ULAZNICA*, int);

void sortiranje_po_vrsti_eventa_uzlazno(ULAZNICA*, int);

void sortiranje_po_godini_silazno(ULAZNICA*, int);

void sortiranje_po_godini_uzlazno(ULAZNICA*, int);

void sortiranje_izbornik();

void brisanje_ulaznice();

void uredivanje_ulaznice();

void izlazak_iz_programa();

#endif
