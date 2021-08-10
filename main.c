#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>
#include "history.h"

void jatek(char* name1, char* name2, bool name_seged);
bool vizsgalat(char matrix[41][41], int kurzor[2], char XO);
bool name(char* name1, char* name2);
void menu(char* name1, char* name2, bool name_seged);
bool return_seged = false;  //rekurziv fuggleny miatti globalis valtozo tobbszoros return miatt

int main()
{
	bool name_seged = false;	//segedvaltozo, figyeli, hogy jatek elott van e neve a jatekosoknak
	char name1[20];				//1. jatekos neve
	char name2[20];				//2. jatekos neves

	menu(name1, name2, name_seged); //menu meghivasa
		
	return 0;
}

bool name(char* name1, char* name2) //nevek atirasa/beirasa
{
	system("cls");
	printf("Players's names:\n\nO: ");
	scanf_s(" %[^\n]s", name1, 20);
	system("cls");
	printf("Players's names:\n\nO: %s\nX: ", name1);
	scanf_s(" %[^\n]s", name2, 20);
	return true;
}

void menu(char* name1, char* name2, bool name_seged)
{
	int menuleptetes = 3;			//0-3 menupontok szamai 0 exit 1 change name 2 play
	char menuleptetes_seged = 0;	// w,s menu nyil fel-le lepteteshez char beolvasasra
	while (1)						//menu, kurzor leptetes
	{
		system("cls");  //clear screen

		printf("\tXXXX  Amoba  OOOO");

		switch (menuleptetes)  //kurzor pozicio
		{
		case 0: printf("\n\nPlay\nChange names\nHistory\nExit <-\n"); break;  // 0 Exit
		case 1: printf("\n\nPlay\nChange names\nHistory <-\nExit\n"); break;  // 1 History
		case 2: printf("\n\nPlay\nChange names <-\nHistory\nExit\n"); break;  // 2 Change name
		case 3: printf("\n\nPlay <-\nChange names\nHistory\nExit\n"); break;  // 3 Play 
		}

		printf("\nS=down, W=up, Enter=choose");

		menuleptetes_seged = _getch();						// 1 karakter beolvasasa (enter nelkul)
		if (menuleptetes_seged == 's') { menuleptetes--; }	// s le
		if (menuleptetes_seged == 'w') { menuleptetes++; }	// w fel
		if (menuleptetes < 0) { menuleptetes = 0; }			//intervallumbol valo kifutas ellen
		if (menuleptetes > 3) { menuleptetes = 3; }
		if (menuleptetes_seged == '\r')						//enter lenyomasara menu valasztas
		{
			switch (menuleptetes)
			{
			case 0: system("cls"); return;				// 0 Exit menu: clear screen, kilepes
			case 1: elozmenyolvasas(); break;
			case 2: name_seged = name(name1, name2); break;	// name fv hivas a nevek megvaltoztatasahoz
			case 3: if (name_seged == false) { name_seged = name(name1, name2); } jatek(name1, name2, name_seged); break;
			}												//ha nincs nev: nev beiras, jatek  ha van nev: jatek
		} // enter nyomasara kilepes (menupont kivalasztasa)
	}
}

void jatek(char* name1, char* name2, bool name_seged)	//jatek
{
	int palya_seged = 40;								//elso sor kiirasahoz seged
	bool turn = false;									//tarolja, hogy melyik jatekos van soron eppen
	char elozo_allapot = '_';							//matrixban a kurzor *-kent szerepel, ez a valtozo a kurzor elotti 
														//karaktert tarolja
	int menuleptetes = 1;								//menu valtozoi
	char menuleptetes_seged = 0;

	int x = 0, y = 0;									//matrix megjelenitesi segedvaltozok
	char matrix[41][41];								//41x41 matrix a jatekra
	while (40 >= y)										//matrix feltoltese '_' karakterekkel (negyzethalo kialakitasahoz)
	{
		while (40 >= x)
		{
			matrix[x][y]='_';
			x++;
		}
		x = 0;
		y++;
	}
	y = 0;

	int kurzor[2] = { 19, 19 };							//kurzor koordinatai
	matrix[kurzor[0]][kurzor[1]] = '*';					//kurzor beirasa a matrixba

	while (1)
	{
		system("cls");						//jatekterulet folotti alapinfok
		printf("\t Amoba  \n\nPlayer X: %s,   Player O: %s   W=up, S=down, A=left, D=right, Enter=choose, Esc=quit\n\n", name1, name2);	
		if (turn==false) { printf("%s's turn (X)\n\n", name2); }				//jatekosok nevenek valtozasa, hogy epp ki jon
		else { printf("%s's turn (O)\n\n", name1); }
	
		while (palya_seged >= 0)												//palya elso soranak feltoltese _ _ _ _ _
		{
			printf(" _");
			palya_seged--;
		}
		palya_seged = 40;
		printf("\n");
		
		while (40 >= y)															//palya kialakitasa a matrix alapjan |_|_|_|
		{
			while (40 >= x)
			{
				printf("|%c", matrix[x][y]);
				x++;
			}
			printf("|\n");
			x = 0;
			y++;
		}
		y = 0;

		switch (_getch())														//w,a,s,d beolvasas a kurzor leptetesehez
		{
			case 'a':	matrix[kurzor[0]][kurzor[1]] = elozo_allapot;
						kurzor[0]--; if (kurzor[0] == -1) { kurzor[0] = 40; }
						elozo_allapot = matrix[kurzor[0]][kurzor[1]]; 
						matrix[kurzor[0]][kurzor[1]] = '*'; break;

			case 'd':	matrix[kurzor[0]][kurzor[1]] = elozo_allapot; 
						kurzor[0]++; if (kurzor[0] == 41) { kurzor[0] = 0; }
						elozo_allapot = matrix[kurzor[0]][kurzor[1]]; 
						matrix[kurzor[0]][kurzor[1]] = '*'; break;

			case 's':	matrix[kurzor[0]][kurzor[1]] = elozo_allapot; 
						kurzor[1]++; if (kurzor[1] == 40) { kurzor[1] = 0; }
						elozo_allapot = matrix[kurzor[0]][kurzor[1]]; 
						matrix[kurzor[0]][kurzor[1]] = '*'; break;

			case 'w':	matrix[kurzor[0]][kurzor[1]] = elozo_allapot; 
						kurzor[1]--; if (kurzor[1] == -1) { kurzor[1] = 40; }
						elozo_allapot = matrix[kurzor[0]][kurzor[1]]; 
						matrix[kurzor[0]][kurzor[1]] = '*'; break;

			case '\r':	if (elozo_allapot == '_')								//enter eseten X vagy O "lerakasa", 
						{														//beiras a matrixba
							if (turn == false) { matrix[kurzor[0]][kurzor[1]] = 'X'; elozo_allapot = 'X'; turn = true; }
							else { matrix[kurzor[0]][kurzor[1]] = 'O'; elozo_allapot = 'O'; turn = false; }
						}  
						break;
			case 27:	while (1)
						{
							system("cls");  //Esc eseten jatek megszakitasa es kilepes (megerosites eseten)
							switch (menuleptetes)  //kurzor pozicio
							{
							case 0: printf("Are you sure want to quit?\n\nNo\nYes <-");  break;  // 0 Quit, yes
							case 1: printf("Are you sure want to quit?\n\nNo <-\nYes");  break;  // 1 Quit, no
							}

							printf("\n\nS=down, W=up, Enter=choose");

							menuleptetes_seged = _getch();  // 1 karakter beolvasasa (enter nelkul)
							if (menuleptetes_seged == 's') { menuleptetes--; } // s le
							if (menuleptetes_seged == 'w') { menuleptetes++; } // w fel
							if (menuleptetes < 0) { menuleptetes = 0; }  //intervallumbol valo kifutas ellen
							if (menuleptetes > 1) { menuleptetes = 1; }
							if (menuleptetes_seged == '\r')
							{
								if (menuleptetes==0)
								{
									system("cls"); return_seged = true; return; // 0 Exit menu: clear screen, kilepes
								}
								else { break; }
							}
						}
		}

		if (vizsgalat(matrix, kurzor, elozo_allapot) == true)		//vizsgalja, hogy nyert e valamelyik jatekos
		{
			menuleptetes = 2;
			menuleptetes_seged = 0;							//a jatek vege utan a tabla ala kiirja a menupontokat

			char name1_[20];
			strcpy_s(name1_, 20, name1);
			char name2_[20];
			strcpy_s(name2_, 20, name2);

			if (elozo_allapot == 'X') { elozmenyiras(name2, name1); }	//kiiras a history-ba fv
			else { elozmenyiras(name1, name2); }

			while (1)  //menu, kurzor leptetes
			{
				system("cls");  //clear screen

				while (palya_seged >= 0)
				{
					printf(" _");
					palya_seged--;
				}
				palya_seged = 40;
				printf("\n");

				while (40 >= y)
				{
					while (40 >= x)
					{
						printf("|%c", matrix[x][y]);
						x++;
					}
					printf("|\n");
					x = 0;
					y++;
				}
				y = 0;

				if (elozo_allapot == 'X') { printf("%s WON!!!", name2_); }	//nyeres eseten kiirja a gyoztes nevet
				else { printf("%s WON!!!", name1_); }

				switch (menuleptetes)  //kurzor pozicio
				{
					case 0: printf("\n\nPlay again\nChange names\nExit to menu <-\n"); break;  // 0 Exit
					case 1: printf("\n\nPlay again\nChange names <-\nExit to menu\n"); break;  // 1 Change name
					case 2: printf("\n\nPlay again <-\nChange names\nExit to menu\n"); break;  // 2 Play 
				}

				printf("\nS=down, W=up, Enter=choose");

				menuleptetes_seged = _getch();  // 1 karakter beolvasasa (enter nelkul)
				if (menuleptetes_seged == 's') { menuleptetes--; } // s le
				if (menuleptetes_seged == 'w') { menuleptetes++; } // w fel
				if (menuleptetes < 0) { menuleptetes = 0; }  //intervallumbol valo kifutas ellen
				if (menuleptetes > 2) { menuleptetes = 2; }
				if (menuleptetes_seged == '\r')
				{
					switch (menuleptetes)
					{
					case 0: system("cls"); return_seged = true; return; // 0 Exit menu: clear screen, kilepes
					case 1: name_seged = name(name1, name2); break;
					case 2: if (name_seged == false) { name_seged = name(name1, name2); } jatek(name1, name2, name_seged);
						if (return_seged == true) { return; }break;
					}
				} // enter nyomasara kilepes (menupont kivalasztasa)
			}
		}
	}
}

bool vizsgalat(char matrix[41][41], int kurzor[2], char XO)		//5db X/O osszegyulesenek vizsgalata
{
	int vizsgalo = kurzor[0] - 4;								//vizszintes vizsgalat
	int szamlalo = 0;
	int seged = 9;

	while (seged > 0)											
	{
		if (matrix[vizsgalo][kurzor[1]] == XO) { szamlalo++; }
		if (matrix[vizsgalo][kurzor[1]] != XO) { szamlalo=0; }
		vizsgalo++;
		seged--;
		if (szamlalo == 5) { return true; }
	}

	seged = 9;													//fuggoleges vizsgalat
	szamlalo = 0;

	vizsgalo = kurzor[1] - 4;
	while (seged > 0)
	{
		if (matrix[kurzor[0]][vizsgalo] == XO) { szamlalo++; }
		if (matrix[kurzor[0]][vizsgalo] != XO) { szamlalo = 0; }
		vizsgalo++;
		seged--;
		if (szamlalo == 5) { return true; }
	}

	seged = 9;													//kereszt iranyu vizsgalat 1
	szamlalo = 0;

	vizsgalo = kurzor[0] - 4;
	int vizsgalo2 = kurzor[1] - 4;
	while (seged > 0)
	{
		if (matrix[vizsgalo][vizsgalo2] == XO) { szamlalo++; }
		if (matrix[vizsgalo][vizsgalo2] != XO) { szamlalo = 0; }
		vizsgalo++;
		vizsgalo2++;
		seged--;
		if (szamlalo == 5) { return true; }
	}

	seged = 9;													//kereszt iranyu vizsgalat 2
	szamlalo = 0;

	vizsgalo = kurzor[0] - 4;
	vizsgalo2 = kurzor[1] + 4;
	while (seged > 0)
	{
		if (matrix[vizsgalo][vizsgalo2] == XO) { szamlalo++; }
		if (matrix[vizsgalo][vizsgalo2] != XO) { szamlalo = 0; }
		vizsgalo++;
		vizsgalo2--;
		seged--;
		if (szamlalo == 5) { return true; }
	}

	return false;
}