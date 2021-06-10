#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

int main(void) {
	int odabir_opcije;
	while (1) {				//u mainu sam napravio glavni izbornik koji sluzi za pokretanje svih unutarnih funkcija, to sam napravio u switch caseu koji vodi do funkcije koja obavlja napisani posao
		system("cls");
		printf("*********KUPOVINA ULAZNICA*********\n");
		printf("___________________________________\n");
		printf(" 1. Dodavanje novih dogadjaja(admin) \n");
		printf("____________________________________\n");
		printf(" 2. Uredivanje dogadjaja(admin)   \n");
		printf("____________________________________\n");
		printf("     3. Popis dogadjaja       \n");
		printf("____________________________________\n");
		printf("   4. Sortiranje kosarice    \n");
		printf("____________________________________\n");
		printf("   5. Pretrazivanje kosarice   \n");
		printf("____________________________________\n");
		printf("    6. Brisanje ulaznica     \n");
		printf("____________________________________\n");
		printf("  7. Izlazak iz izbornika  \n");
		printf("____________________________________\n");
		printf("\n");
		printf("Izaberite opciju: ");

		odabir_opcije = getch();
		switch (odabir_opcije) {
		case '1':
			system("cls");
			if (nova_ulaznica() == 1) {
				printf("\nGreska.\n");
			}
			printf("\n\nPritisnite bilo koju tipku za povratak...");
			getch();
			break;

		case '2':
			uredivanje_ulaznice();
			printf("\n\nPritisnite bilo koju tipku za povratak...");
			getch();
			break;
		case '3': 
			system("cls");
			if (ispis_ulaznica() == -1) {
				printf("\nGreska.\n");
			}
			printf("\n\nPritisnite bilo koju tipku za povratak...");
			getch();
			break;
		case '4':
			system("cls");
			sortiranje_izbornik();
			break;
		case '5':
			izbornik_pretrazivanje();
			printf("\n\nPritisnite bilo koju tipku za povratak...");
			getch();
			break;
		case '6':
			brisanje_ulaznice();
			printf("\n\nPritisnite bilo koju tipku za povratak...");
			getch();
			break;
		case '7':
			system("cls");
			izlazak_iz_programa();
		default:
			/*printf("\nKrivi unos!\n");*/
			printf("\nPritisnite bilo koju tipku za povratak...");
			getch();

		}
	}
}
