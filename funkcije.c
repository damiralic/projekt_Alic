#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int nova_ulaznica() {
	FILE* fileP = NULL;
	ULAZNICA* nova_ulaznica = NULL;
	nova_ulaznica = (ULAZNICA*)malloc(sizeof(ULAZNICA));
	int broj_ulaznica;
	if (nova_ulaznica == NULL) {
		return 1;
	}
	else {
		char username[15];
		char password[12];
		int prijava = 0;


		printf("Unesite svoje ime:\n");
		scanf("%s", &username);

		printf("Unesite svoju lozinku:\n");
		scanf("%s", &password);

		if (strcmp(username, "Damir") == 0) {
			if (strcmp(password, "123") == 0) {

				printf("\nUspjesna prijava!\n\n");
				prijava = 1;

			}
			else {
				printf("\nPogresna lozinka");
				prijava = 0;
			}
		}
		else {
			printf("\nKorisnik ne postoji!");
			prijava = 0;
		}
		if (prijava == 1) {
			printf("Unesite vrstu eventa: ");
			scanf(" %99[^\n]", nova_ulaznica->ime_eventa);
			printf("Unesite cijenu eventa: ");
			scanf(" %49[^\n]", nova_ulaznica->cijena_eventa);
			printf("Unesite broj dostupnih mjesta: ");
			scanf(" %49[^\n]", nova_ulaznica->dostupne_ul);
			printf("Unesite datum prikazivanja eventa: ");
			scanf("%d", &nova_ulaznica->godina_izdanja);
			fileP = fopen("ulaznice.bin", "rb");
			if (fileP == NULL) {
				fileP = fopen("ulaznice.bin", "wb");
				broj_ulaznica = 1;
				fwrite(&broj_ulaznica, sizeof(int), 1, fileP);
				fwrite(nova_ulaznica, sizeof(ULAZNICA), 1, fileP);
				fclose(fileP);
			}
			else {
				fclose(fileP);
				fileP = fopen("ulaznice.bin", "rb+");
				if (fileP == NULL) {
					return 1;
				}
				else {
					fseek(fileP, 0, SEEK_SET);
					fread(&broj_ulaznica, sizeof(int), 1, fileP);
					broj_ulaznica++;
					fseek(fileP, 0, SEEK_SET);
					fwrite(&broj_ulaznica, sizeof(int), 1, fileP);
					fseek(fileP, 0, SEEK_END);
					fwrite(nova_ulaznica, sizeof(ULAZNICA), 1, fileP);
					fclose(fileP);
				}
			}
		}
	}

	free(nova_ulaznica);
	return 0;
}

void ispisUlaznice(ULAZNICA* ulaznice) {
	printf("\n\nIme eventa: %s", ulaznice->ime_eventa);
	printf("\nCijena: %s", ulaznice->cijena_eventa);
	printf("\nBroj Dostupnih mjesta: %s", ulaznice->dostupne_ul);
	printf("\nGodina dogadjaja: %d", ulaznice->godina_izdanja);

	return;
}

void pretrazivanje(char kriterij) {
	ULAZNICA* ulaznice = NULL;
	FILE* fileP = NULL;
	char trazeni_event[100], cijena_ulaznice[50], trazena_vrsta[50];
	int trazena_godina;

	int broj_ulaznica, f = 0;
	system("cls");

	fileP = fopen("ulaznice.bin", "rb");
	if (fileP == NULL) {
		printf("\nNesto je poslo po krivu :(.\n");
	}
	else {
		fread(&broj_ulaznica, sizeof(int), 1, fileP);
		ulaznice = (ULAZNICA*)malloc(sizeof(ULAZNICA));
		if (ulaznice == NULL) {
			printf("Nesto je poslo po krivu :(.\n");
		}
		else {
			switch (kriterij) {
			case 'i':
				printf("Unesite naslov događaja: ");
				scanf(" %99[^\n]", trazeni_event);
				for (int i = 0; i < broj_ulaznica; i++) {
					fread(ulaznice, sizeof(ULAZNICA), 1, fileP);
					if (strcmp(ulaznice->ime_eventa, trazeni_event) == 0) {
						printf("\nulaznica je dostupna.");
						ispisUlaznice(ulaznice);
						f = 1;
						break;
					}
				}
				break;

			case 'g':
				printf("Unesite godinu trazenog događaja: ");
				scanf(" %d", &trazena_godina);
				for (int i = 0; i < broj_ulaznica; i++) {
					fread(ulaznice, sizeof(ULAZNICA), 1, fileP);
					if (ulaznice->godina_izdanja == trazena_godina) {
						printf("\nulaznica je dostupna.");
						ispisUlaznice(ulaznice);
						f = 1;
					}
				}
				break;

			case 'a':
				printf("Unesite cijenu trazene ulaznice: ");
				scanf(" %49[^\n]", cijena_ulaznice);
				for (int i = 0; i < broj_ulaznica; i++) {
					fread(ulaznice, sizeof(ULAZNICA), 1, fileP);
					if (strcmp(ulaznice->cijena_eventa, cijena_ulaznice) == 0) {
						printf("\nulaznica je dostupna.");
						ispisUlaznice(ulaznice);
						f = 1;
					}
				}
				break;

			case 'v':
				printf("Unesite broj dostupnih mjesta ulaznice: ");
				scanf(" %49[^\n]", trazena_vrsta);
				for (int i = 0; i < broj_ulaznica; i++) {
					fread(ulaznice, sizeof(ULAZNICA), 1, fileP);
					if (strcmp(ulaznice->dostupne_ul, trazena_vrsta) == 0) {
						printf("\nulaznica je dostupna.");
						ispisUlaznice(ulaznice);
						f = 1;
					}
				}
				break;
			}
			if (f == 0) {
				printf("\nulaznica nije dostupna");
			}
			fclose(fileP);
		}
	}
}

void brisanje_ulaznice() {
	FILE* fileP = NULL;
	ULAZNICA* ulaznica = NULL;
	int broj_ulaznica;
	int index_za_brisanje;
	fileP = fopen("ulaznice.bin", "rb");
	if (fileP == NULL) {
		printf("\nNesto je poslo po krivu :(!");
	}
	else {
		fread(&broj_ulaznica, sizeof(int), 1, fileP);
		ulaznica = (ULAZNICA*)malloc(broj_ulaznica * sizeof(ULAZNICA));

		if (ulaznica == NULL) {
			printf("\nNesto je poslo po krivu :(!");
		}
		else {
			fread(ulaznica, sizeof(ULAZNICA), broj_ulaznica, fileP);
			fclose(fileP);
			//pretraga
			char trazeni_naslov[100];
			int f = 0;
			system("cls");
			printf("Unesite naslov dogadjaja koju zelite obrisati: ");
			scanf(" %99[^\n]", trazeni_naslov);
			for (int i = 0; i < broj_ulaznica; i++) {
				if (strcmp((ulaznica + i)->ime_eventa, trazeni_naslov) == 0) {
					ispisUlaznice(ulaznica + i);
					index_za_brisanje = i;
					f = 1;
					break;
				}
			}
			if (f == 0) {
				printf("\nulaznica nije pronadena");
			}
			else {
				fclose(fileP);
				fileP = fopen("ulaznice.bin", "wb");
				if (fileP == NULL) {
					printf("\nNesto je poslo po krivu :(!");
				}
				else {
					broj_ulaznica--;
					fwrite(&broj_ulaznica, sizeof(int), 1, fileP);
					for (int i = 0; i < broj_ulaznica + 1; i++) {
						if (i == index_za_brisanje) {
							continue;
						}
						else {
							fwrite((ulaznica + i), sizeof(ULAZNICA), 1, fileP);
						}
					}
					printf("\n\nulaznica je obrisana.");
					fclose(fileP);
				}
			}
		}
	}
}

void uredivanje_ulaznice() {
	FILE* fileP = NULL;
	ULAZNICA* ulaznica = NULL;
	int broj_ulaznica;
	fileP = fopen("ulaznice.bin", "rb+");
	if (fileP == NULL) {
		printf("\nNesto je poslo po krivu :(!");
	}
	else {
		fread(&broj_ulaznica, sizeof(int), 1, fileP);
		ulaznica = (ULAZNICA*)malloc(sizeof(ULAZNICA));
		if (ulaznica == NULL) {
			printf("\nNesto je poslo po krivu :(!");
		}
		else {
			//pretraga
			char trazeni_naslov[100];
			int f = 0;
			system("cls");
			char username[15];
			char password[12];
			int prijava = 0;


			printf("Unesite svoje ime:\n");
			scanf("%s", &username);

			printf("Unesite svoju lozinku:\n");
			scanf("%s", &password);

			if (strcmp(username, "Damir") == 0) {
				if (strcmp(password, "123") == 0) {

					printf("\nUspjesna prijava!\n\n");
					prijava = 1;

				}
				else {
					printf("\nPogresna lozinka");
					prijava = 0;
				}
			}
			else {
				printf("\nKorisnik ne postoji!");
				prijava = 0;
			}
			if (prijava == 1) {
				printf("Unesite naslov dogadjaja koje zelite urediti: ");
				scanf(" %99[^\n]", trazeni_naslov);
				for (int i = 0; i < broj_ulaznica; i++) {
					fread(ulaznica, sizeof(ULAZNICA), 1, fileP);
					if (strcmp(ulaznica->ime_eventa, trazeni_naslov) == 0) {
						f = 1;
						ispisUlaznice(ulaznica);
						//izbornik 
						system("cls");
						printf("1. Promjena vrste dogadjaja");
						printf("\n2. Promjena cijene");
						printf("\n3. Promjena dostupnih mjesta");
						printf("\n4. Promjena datuma prikazivanja dogadjaja\n");
						printf("5. Povratak u glavni izbornik\n");
						char odabir = getch();
						switch (odabir) {
						case '1': // promjena naslova
							printf("\nUnesite novi naslov: ");
							char novi_naslov[100];
							scanf(" %99[^\n]", novi_naslov);
							strcpy((ulaznica)->ime_eventa, novi_naslov);
							fseek(fileP, -(int)sizeof(ULAZNICA), SEEK_CUR);
							fwrite(ulaznica, sizeof(ULAZNICA), 1, fileP);
							printf("Naziv uspjesno promjenjen.\n");
							break;

						case '2': // promjena redatelja
							printf("\nUnesite novu cijenu: ");
							char novi_autor[50];
							scanf(" %49[^\n]", novi_autor);
							strcpy((ulaznica)->cijena_eventa, novi_autor);
							fseek(fileP, -(int)sizeof(ULAZNICA), SEEK_CUR);
							fwrite(ulaznica, sizeof(ULAZNICA), 1, fileP);
							printf("\nCijena uspjesno promjenjena.\n");
							break;

						case '3': // promjena vrste
							printf("\nUnesite novi broj dostupnih mjesta: ");
							char nova_vrsta[50];
							scanf(" %49[^\n]", nova_vrsta);
							strcpy((ulaznica)->dostupne_ul, nova_vrsta);
							fseek(fileP, -(int)sizeof(ULAZNICA), SEEK_CUR);
							fwrite(ulaznica, sizeof(ULAZNICA), 1, fileP);
							printf("\nBroj mjesta uspjesno promjenjena.\n");
							break;

						case '4': // promjena godine
							printf("\nUnesite novu godinu: ");
							int nova_godina;
							scanf("%d", &nova_godina);
							ulaznica->godina_izdanja = nova_godina;
							fseek(fileP, -(int)sizeof(ULAZNICA), SEEK_CUR);
							fwrite(ulaznica, sizeof(ULAZNICA), 1, fileP);
							printf("\nGodina uspjesno promjenjena.\n");
							break;

						case '5':
							return;
							break;
						default:
							printf("Krivi unos.");
						}
						break;
					}
				}
			}

			if (f == 0) {
				printf("\nulaznica nije pronadena");
			}
		}
		fclose(fileP);
	}
	free(ulaznica);
	ulaznica = NULL;
}

void izbornik_pretrazivanje() {
	system("cls");
	printf("1. Pretrazivanje po nazivu\n");
	printf("2. Pretrazivanje po cijeni\n");
	printf("3. Pretrazivanje po broju dostupnih mjesta\n");
	printf("4. Pretrazivanje po godini\n");
	printf("5. Povratak u glavni izbornik\n");
	char odabir = getch();
	switch (odabir) {
	case '1':
		pretrazivanje('i');
		break;

	case '2':
		pretrazivanje('a');
		break;

	case '3':
		pretrazivanje('v');
		break;

	case '4':
		pretrazivanje('g');
		break;

	case '5':
		return;
		break;
	default:
		printf("\nKrivi unos.");
	}
}

void sortiranje_po_imenu_eventa_silazno(ULAZNICA* ulaznice, int broj_ulaznica) {
	ULAZNICA temp;
	char prvo_slovo, prvo_slovo_pom;
	int min;


	for (int i = 0; i < broj_ulaznica - 1; i++) {
		min = i;
		prvo_slovo = (ulaznice + i)->ime_eventa[0] >= 'A' && (ulaznice + i)->ime_eventa[0] <= 'Z' ? (ulaznice + i)->ime_eventa[0] : (ulaznice + i)->ime_eventa[0] - 32;
		for (int j = i + 1; j < broj_ulaznica; j++) {
			prvo_slovo_pom = (ulaznice + j)->ime_eventa[0] >= 'A' && (ulaznice + j)->ime_eventa[0] <= 'Z' ? (ulaznice + j)->ime_eventa[0] : (ulaznice + j)->ime_eventa[0] - 32;
			if (prvo_slovo < prvo_slovo_pom) {
				min = j;
				prvo_slovo = (ulaznice + j)->ime_eventa[0] >= 'A' && (ulaznice + j)->ime_eventa[0] <= 'Z' ? (ulaznice + j)->ime_eventa[0] : (ulaznice + j)->ime_eventa[0] - 32;
			}
		}
		//zamjena imena eventa
		strcpy(temp.ime_eventa, (ulaznice + i)->ime_eventa);
		strcpy((ulaznice + i)->ime_eventa, (ulaznice + min)->ime_eventa);
		strcpy((ulaznice + min)->ime_eventa, temp.ime_eventa);
		//zamjena redatelja eventa
		strcpy(temp.cijena_eventa, (ulaznice + i)->cijena_eventa);
		strcpy((ulaznice + i)->cijena_eventa, (ulaznice + min)->cijena_eventa);
		strcpy((ulaznice + min)->cijena_eventa, temp.cijena_eventa);
		//zamjena vrste eventa
		strcpy(temp.dostupne_ul, (ulaznice + i)->dostupne_ul);
		strcpy((ulaznice + i)->dostupne_ul, (ulaznice + min)->dostupne_ul);
		strcpy((ulaznice + min)->dostupne_ul, temp.dostupne_ul);
		//zamjena godine izdanja
		temp.godina_izdanja = (ulaznice + i)->godina_izdanja;
		(ulaznice + i)->godina_izdanja = (ulaznice + min)->godina_izdanja;
		(ulaznice + min)->godina_izdanja = temp.godina_izdanja;
	}

	return;
}

void sortiranje_po_imenu_eventa_uzlazno(ULAZNICA* ulaznice, int broj_ulaznica) {
	ULAZNICA temp;
	char prvo_slovo, prvo_slovo_pom;
	int max;

	for (int i = 0; i < broj_ulaznica - 1; i++) {
		max = i;
		prvo_slovo = (ulaznice + i)->ime_eventa[0] >= 'A' && (ulaznice + i)->ime_eventa[0] <= 'Z' ? (ulaznice + i)->ime_eventa[0] : (ulaznice + i)->ime_eventa[0] - 32;
		for (int j = i + 1; j < broj_ulaznica; j++) {
			prvo_slovo_pom = (ulaznice + j)->ime_eventa[0] >= 'A' && (ulaznice + j)->ime_eventa[0] <= 'Z' ? (ulaznice + j)->ime_eventa[0] : (ulaznice + j)->ime_eventa[0] - 32;
			if (prvo_slovo > prvo_slovo_pom) {
				max = j;
				prvo_slovo = (ulaznice + j)->ime_eventa[0] >= 'A' && (ulaznice + j)->ime_eventa[0] <= 'Z' ? (ulaznice + j)->ime_eventa[0] : (ulaznice + j)->ime_eventa[0] - 32;
			}
		}
		//zamjena imena eventa
		strcpy(temp.ime_eventa, (ulaznice + i)->ime_eventa);
		strcpy((ulaznice + i)->ime_eventa, (ulaznice + max)->ime_eventa);
		strcpy((ulaznice + max)->ime_eventa, temp.ime_eventa);
		//zamjena redatelja eventa
		strcpy(temp.cijena_eventa, (ulaznice + i)->cijena_eventa);
		strcpy((ulaznice + i)->cijena_eventa, (ulaznice + max)->cijena_eventa);
		strcpy((ulaznice + max)->cijena_eventa, temp.cijena_eventa);
		//zamjena vrste eventa
		strcpy(temp.dostupne_ul, (ulaznice + i)->dostupne_ul);
		strcpy((ulaznice + i)->dostupne_ul, (ulaznice + max)->dostupne_ul);
		strcpy((ulaznice + max)->dostupne_ul, temp.dostupne_ul);
		//zamjena godine izdanja
		temp.godina_izdanja = (ulaznice + i)->godina_izdanja;
		(ulaznice + i)->godina_izdanja = (ulaznice + max)->godina_izdanja;
		(ulaznice + max)->godina_izdanja = temp.godina_izdanja;
	}

	return;
}

void sortiranje_po_imenu_redatelja_silazno(ULAZNICA* ulaznice, int broj_ulaznica) {
	ULAZNICA temp;
	char prvo_slovo, prvo_slovo_pom;
	int min;

	for (int i = 0; i < broj_ulaznica - 1; i++) {
		min = i;
		prvo_slovo = (ulaznice + i)->cijena_eventa[0] >= 'A' && (ulaznice + i)->cijena_eventa[0] <= 'Z' ? (ulaznice + i)->cijena_eventa[0] : (ulaznice + i)->cijena_eventa[0] - 32;
		for (int j = i + 1; j < broj_ulaznica; j++) {
			prvo_slovo_pom = (ulaznice + j)->cijena_eventa[0] >= 'A' && (ulaznice + j)->cijena_eventa[0] <= 'Z' ? (ulaznice + j)->cijena_eventa[0] : (ulaznice + j)->cijena_eventa[0] - 32;
			if (prvo_slovo < prvo_slovo_pom) {
				min = j;
				prvo_slovo = (ulaznice + j)->cijena_eventa[0] >= 'A' && (ulaznice + j)->cijena_eventa[0] <= 'Z' ? (ulaznice + j)->cijena_eventa[0] : (ulaznice + j)->cijena_eventa[0] - 32;
			}
		}
		//zamjena imena eventa
		strcpy(temp.ime_eventa, (ulaznice + i)->ime_eventa);
		strcpy((ulaznice + i)->ime_eventa, (ulaznice + min)->ime_eventa);
		strcpy((ulaznice + min)->ime_eventa, temp.ime_eventa);
		//zamjena redatelja eventa
		strcpy(temp.cijena_eventa, (ulaznice + i)->cijena_eventa);
		strcpy((ulaznice + i)->cijena_eventa, (ulaznice + min)->cijena_eventa);
		strcpy((ulaznice + min)->cijena_eventa, temp.cijena_eventa);
		//zamjena vrste eventa
		strcpy(temp.dostupne_ul, (ulaznice + i)->dostupne_ul);
		strcpy((ulaznice + i)->dostupne_ul, (ulaznice + min)->dostupne_ul);
		strcpy((ulaznice + min)->dostupne_ul, temp.dostupne_ul);
		//zamjena godine izdanja
		temp.godina_izdanja = (ulaznice + i)->godina_izdanja;
		(ulaznice + i)->godina_izdanja = (ulaznice + min)->godina_izdanja;
		(ulaznice + min)->godina_izdanja = temp.godina_izdanja;
	}

	return;
}

void sortiranje_po_imenu_redatelja_uzlazno(ULAZNICA* ulaznice, int broj_ulaznica) {
	ULAZNICA temp;
	char prvo_slovo, prvo_slovo_pom;
	int max;

	for (int i = 0; i < broj_ulaznica - 1; i++) {
		max = i;
		prvo_slovo = (ulaznice + i)->cijena_eventa[0] >= 'A' && (ulaznice + i)->cijena_eventa[0] <= 'Z' ? (ulaznice + i)->cijena_eventa[0] : (ulaznice + i)->cijena_eventa[0] - 32;
		for (int j = i + 1; j < broj_ulaznica; j++) {
			prvo_slovo_pom = (ulaznice + j)->cijena_eventa[0] >= 'A' && (ulaznice + j)->cijena_eventa[0] <= 'Z' ? (ulaznice + j)->cijena_eventa[0] : (ulaznice + j)->cijena_eventa[0] - 32;
			if (prvo_slovo > prvo_slovo_pom) {
				max = j;
				prvo_slovo = (ulaznice + j)->cijena_eventa[0] >= 'A' && (ulaznice + j)->cijena_eventa[0] <= 'Z' ? (ulaznice + j)->cijena_eventa[0] : (ulaznice + j)->cijena_eventa[0] - 32;
			}
		}
		//zamjena imena eventa
		strcpy(temp.ime_eventa, (ulaznice + i)->ime_eventa);
		strcpy((ulaznice + i)->ime_eventa, (ulaznice + max)->ime_eventa);
		strcpy((ulaznice + max)->ime_eventa, temp.ime_eventa);
		//zamjena redatelja eventa
		strcpy(temp.cijena_eventa, (ulaznice + i)->cijena_eventa);
		strcpy((ulaznice + i)->cijena_eventa, (ulaznice + max)->cijena_eventa);
		strcpy((ulaznice + max)->cijena_eventa, temp.cijena_eventa);
		//zamjena vrste eventa
		strcpy(temp.dostupne_ul, (ulaznice + i)->dostupne_ul);
		strcpy((ulaznice + i)->dostupne_ul, (ulaznice + max)->dostupne_ul);
		strcpy((ulaznice + max)->dostupne_ul, temp.dostupne_ul);
		//zamjena godine izdanja
		temp.godina_izdanja = (ulaznice + i)->godina_izdanja;
		(ulaznice + i)->godina_izdanja = (ulaznice + max)->godina_izdanja;
		(ulaznice + max)->godina_izdanja = temp.godina_izdanja;
	}

	return;
}

void sortiranje_po_vrsti_eventa_silazno(ULAZNICA* ulaznice, int broj_ulaznica) {
	ULAZNICA temp;
	char prvo_slovo, prvo_slovo_pom;
	int min;


	for (int i = 0; i < broj_ulaznica - 1; i++) {
		min = i;
		prvo_slovo = (ulaznice + i)->dostupne_ul[0] >= 'A' && (ulaznice + i)->dostupne_ul[0] <= 'Z' ? (ulaznice + i)->dostupne_ul[0] : (ulaznice + i)->dostupne_ul[0] - 32;
		for (int j = i + 1; j < broj_ulaznica; j++) {
			prvo_slovo_pom = (ulaznice + j)->dostupne_ul[0] >= 'A' && (ulaznice + j)->dostupne_ul[0] <= 'Z' ? (ulaznice + j)->dostupne_ul[0] : (ulaznice + j)->dostupne_ul[0] - 32;
			if (prvo_slovo < prvo_slovo_pom) {
				min = j;
				prvo_slovo = (ulaznice + j)->dostupne_ul[0] >= 'A' && (ulaznice + j)->dostupne_ul[0] <= 'Z' ? (ulaznice + j)->dostupne_ul[0] : (ulaznice + j)->dostupne_ul[0] - 32;
			}
		}
		//zamjena imena eventa
		strcpy(temp.ime_eventa, (ulaznice + i)->ime_eventa);
		strcpy((ulaznice + i)->ime_eventa, (ulaznice + min)->ime_eventa);
		strcpy((ulaznice + min)->ime_eventa, temp.ime_eventa);
		//zamjena redatelja eventa
		strcpy(temp.cijena_eventa, (ulaznice + i)->cijena_eventa);
		strcpy((ulaznice + i)->cijena_eventa, (ulaznice + min)->cijena_eventa);
		strcpy((ulaznice + min)->cijena_eventa, temp.cijena_eventa);
		//zamjena vrste eventa
		strcpy(temp.dostupne_ul, (ulaznice + i)->dostupne_ul);
		strcpy((ulaznice + i)->dostupne_ul, (ulaznice + min)->dostupne_ul);
		strcpy((ulaznice + min)->dostupne_ul, temp.dostupne_ul);
		//zamjena godine izdanja
		temp.godina_izdanja = (ulaznice + i)->godina_izdanja;
		(ulaznice + i)->godina_izdanja = (ulaznice + min)->godina_izdanja;
		(ulaznice + min)->godina_izdanja = temp.godina_izdanja;
	}

	return;
}

void sortiranje_po_vrsti_eventa_uzlazno(ULAZNICA* ulaznice, int broj_ulaznica) {
	ULAZNICA temp;
	char prvo_slovo, prvo_slovo_pom;
	int max;

	for (int i = 0; i < broj_ulaznica - 1; i++) {
		max = i;
		prvo_slovo = (ulaznice + i)->dostupne_ul[0] >= 'A' && (ulaznice + i)->dostupne_ul[0] <= 'Z' ? (ulaznice + i)->dostupne_ul[0] : (ulaznice + i)->dostupne_ul[0] - 32;
		for (int j = i + 1; j < broj_ulaznica; j++) {
			prvo_slovo_pom = (ulaznice + j)->dostupne_ul[0] >= 'A' && (ulaznice + j)->dostupne_ul[0] <= 'Z' ? (ulaznice + j)->dostupne_ul[0] : (ulaznice + j)->dostupne_ul[0] - 32;
			if (prvo_slovo > prvo_slovo_pom) {
				max = j;
				prvo_slovo = (ulaznice + j)->dostupne_ul[0] >= 'A' && (ulaznice + j)->dostupne_ul[0] <= 'Z' ? (ulaznice + j)->dostupne_ul[0] : (ulaznice + j)->dostupne_ul[0] - 32;
			}
		}
		//zamjena imena eventa
		strcpy(temp.ime_eventa, (ulaznice + i)->ime_eventa);
		strcpy((ulaznice + i)->ime_eventa, (ulaznice + max)->ime_eventa);
		strcpy((ulaznice + max)->ime_eventa, temp.ime_eventa);
		//zamjena redatelja eventa
		strcpy(temp.cijena_eventa, (ulaznice + i)->cijena_eventa);
		strcpy((ulaznice + i)->cijena_eventa, (ulaznice + max)->cijena_eventa);
		strcpy((ulaznice + max)->cijena_eventa, temp.cijena_eventa);
		//zamjena vrste eventa
		strcpy(temp.dostupne_ul, (ulaznice + i)->dostupne_ul);
		strcpy((ulaznice + i)->dostupne_ul, (ulaznice + max)->dostupne_ul);
		strcpy((ulaznice + max)->dostupne_ul, temp.dostupne_ul);
		//zamjena godine izdanja
		temp.godina_izdanja = (ulaznice + i)->godina_izdanja;
		(ulaznice + i)->godina_izdanja = (ulaznice + max)->godina_izdanja;
		(ulaznice + max)->godina_izdanja = temp.godina_izdanja;
	}

	return;
}

void sortiranje_po_godini_uzlazno(ULAZNICA* ulaznice, int broj_ulaznica) {
	ULAZNICA temp;
	int godina1, godina2;
	int min;

	for (int i = 0; i < broj_ulaznica - 1; i++) {
		min = i;
		godina1 = (ulaznice + i)->godina_izdanja;
		for (int j = i + 1; j < broj_ulaznica; j++) {
			godina2 = (ulaznice + j)->godina_izdanja;
			if (godina1 > godina2) {
				min = j;
				godina1 = (ulaznice + j)->godina_izdanja;
			}
		}
		//zamjena imena eventa
		strcpy(temp.ime_eventa, (ulaznice + i)->ime_eventa);
		strcpy((ulaznice + i)->ime_eventa, (ulaznice + min)->ime_eventa);
		strcpy((ulaznice + min)->ime_eventa, temp.ime_eventa);
		//zamjena redatelja eventa
		strcpy(temp.cijena_eventa, (ulaznice + i)->cijena_eventa);
		strcpy((ulaznice + i)->cijena_eventa, (ulaznice + min)->cijena_eventa);
		strcpy((ulaznice + min)->cijena_eventa, temp.cijena_eventa);
		//zamjena vrste eventa
		strcpy(temp.dostupne_ul, (ulaznice + i)->dostupne_ul);
		strcpy((ulaznice + i)->dostupne_ul, (ulaznice + min)->dostupne_ul);
		strcpy((ulaznice + min)->dostupne_ul, temp.dostupne_ul);
		//zamjena godine izdanja
		temp.godina_izdanja = (ulaznice + i)->godina_izdanja;
		(ulaznice + i)->godina_izdanja = (ulaznice + min)->godina_izdanja;
		(ulaznice + min)->godina_izdanja = temp.godina_izdanja;
	}

	return;
}

void sortiranje_po_godini_silazno(ULAZNICA* ulaznice, int broj_ulaznica) {
	ULAZNICA temp;
	int godina1, godina2;
	int max;

	for (int i = 0; i < broj_ulaznica - 1; i++) {
		max = i;
		godina1 = (ulaznice + i)->godina_izdanja;
		for (int j = i + 1; j < broj_ulaznica; j++) {
			godina2 = (ulaznice + j)->godina_izdanja;
			if (godina1 < godina2) {
				max = j;
				godina1 = (ulaznice + j)->godina_izdanja;
			}
		}
		//zamjena imena eventa
		strcpy(temp.ime_eventa, (ulaznice + i)->ime_eventa);
		strcpy((ulaznice + i)->ime_eventa, (ulaznice + max)->ime_eventa);
		strcpy((ulaznice + max)->ime_eventa, temp.ime_eventa);
		//zamjena redatelja eventa
		strcpy(temp.cijena_eventa, (ulaznice + i)->cijena_eventa);
		strcpy((ulaznice + i)->cijena_eventa, (ulaznice + max)->cijena_eventa);
		strcpy((ulaznice + max)->cijena_eventa, temp.cijena_eventa);
		//zamjena vrste eventa
		strcpy(temp.dostupne_ul, (ulaznice + i)->dostupne_ul);
		strcpy((ulaznice + i)->dostupne_ul, (ulaznice + max)->dostupne_ul);
		strcpy((ulaznice + max)->dostupne_ul, temp.dostupne_ul);
		//zamjena godine izdanja
		temp.godina_izdanja = (ulaznice + i)->godina_izdanja;
		(ulaznice + i)->godina_izdanja = (ulaznice + max)->godina_izdanja;
		(ulaznice + max)->godina_izdanja = temp.godina_izdanja;
	}

	return;
}

void sortiranje_izbornik() {
	ULAZNICA* ulaznice = NULL;
	FILE* fileP = NULL;
	char prvi_odabir, drugi_odabir;
	char odabir[30];

	int broj_ulaznica;
	system("cls");

	fileP = fopen("ulaznice.bin", "rb"); 
	if (fileP == NULL) {
		printf("\nNesto je poslo po krivu :(.\n");
	}
	else {
		fread(&broj_ulaznica, sizeof(int), 1, fileP); //citanje broja ulaznica
		ulaznice = (ULAZNICA*)malloc(broj_ulaznica * sizeof(ULAZNICA));
		if (ulaznice == NULL) {
			printf("\nNesto je poslo po krivu :(!");
		}
		else {
			fread(ulaznice, sizeof(ULAZNICA), broj_ulaznica, fileP);
			system("cls");
			printf("Odaberite nacin sortiranja:\n");
			printf("1. Naziv dogadjaja\n2. Cijena\n3. Broj dostupnih mjesta\n4. Godina izdanja\n");
			do {
				prvi_odabir = getch();
			} while (prvi_odabir < '1' || prvi_odabir > '4');
			//printf("Redoslijed:\n1. Uzlazno\n2. Silazno");
			printf("Redoslijed: \n1. Od najmanje\n2. Od najvece");
			do {
				drugi_odabir = getch();
			} while (drugi_odabir < '1' || drugi_odabir > '2');

			switch (prvi_odabir) {
			case '1':
				if (drugi_odabir == '1') {
					sortiranje_po_imenu_eventa_uzlazno(ulaznice, broj_ulaznica);
				}
				else {
					sortiranje_po_imenu_eventa_silazno(ulaznice, broj_ulaznica);
				}
				break;
			case '2':
				if (drugi_odabir == '1') {
					sortiranje_po_imenu_redatelja_uzlazno(ulaznice, broj_ulaznica);
				}
				else {
					sortiranje_po_imenu_redatelja_silazno(ulaznice, broj_ulaznica);
				}
				break;
			case '3':
				if (drugi_odabir == '1') {
					sortiranje_po_vrsti_eventa_uzlazno(ulaznice, broj_ulaznica);
				}
				else {
					sortiranje_po_vrsti_eventa_silazno(ulaznice, broj_ulaznica);
				}
				break;
			case '4':
				if (drugi_odabir == '1') {
					sortiranje_po_godini_uzlazno(ulaznice, broj_ulaznica);
				}
				else {
					sortiranje_po_godini_silazno(ulaznice, broj_ulaznica);
				}
				break;
			}
			fclose(fileP);
			fileP = fopen("ulaznice.bin", "wb");
			if (fileP == NULL) {
				printf("\nNesto je poslo po krivu :(!");
			}
			else {
				//ovdje azuriram datotku
				fwrite(&broj_ulaznica, sizeof(int), 1, fileP);
				fwrite(ulaznice, sizeof(ULAZNICA), broj_ulaznica, fileP);
				fclose(fileP);
			}
			free(ulaznice);
			ulaznice = NULL;
		}
	}
	printf("\n\nSortiranje uspjesno obavljeno. Za rezultate pogledajte kosaricu!");
	printf("\nPritisnite bilo koju tipku za povratak...");
	getch();
}

int ispis_ulaznica() {
	int broj;
	ULAZNICA* ulaznice = NULL;
	FILE* fileP = NULL;
	fileP = fopen("ulaznice.bin", "rb");
	if (fileP == NULL) {
		return 1;
	}
	else {
		fread(&broj, sizeof(int), 1, fileP);
		ulaznice = (ULAZNICA*)malloc(sizeof(ULAZNICA));
		if (ulaznice == NULL) {
			return 1;
		}
		else {
			printf("U ponudi ima %d ulaznic%s.", broj, broj == 1 || broj > 4 ? "a" : "e");
			for (int i = 0; i < broj; i++) {
				fread(ulaznice, sizeof(ULAZNICA), 1, fileP);
				ispisUlaznice(ulaznice);
			}
			free(ulaznice);
			fclose(fileP);
			return broj;
		}
	}
}

void izlazak_iz_programa() {
	char odabir[3];
	printf("Zelite li izaci iz programa? (da/ne) ");
	scanf(" %2s", odabir);
	if (strcmp(odabir, "da") == 0 || strcmp(odabir, "Da") == 0 || strcmp(odabir, "DA") == 0 || strcmp(odabir, "dA") == 0) {
		printf("\nIzlazak iz programa...");
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(odabir, "ne") == 0 || strcmp(odabir, "Ne") == 0 || strcmp(odabir, "NE") == 0 || strcmp(odabir, "nE") == 0) {
		return;
	}
}
