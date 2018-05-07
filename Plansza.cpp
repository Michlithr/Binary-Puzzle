#pragma once
#include "Plansza.h"
#include "Liczba.h"
#include "Jedynka.h"
#include "Zero.h"
#include "Kursor.h"
#include "Stale.h"
#include "Menu.h"
#include "conio2.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>

Plansza::Plansza() : szerokoscPlanszy(SZEROKOSC_BAZOWA), wysokoscPlanszy(WYSOKOSC_BAZOWA) 
{
	this->menu = new Menu;
	this->kursor = new Kursor;
	this->bufor = new char[32];
	this->znak = 0;
	this->zero = 0;
	this->useHelp = false;
	this->help = false;
	this->x = PLANSZA_X;
	this->y = PLANSZA_Y;
	this->allocLiczby();
	for (int i = 0; i < this->wysokoscPlanszy; i++){
		for (int j = 0; j < this->szerokoscPlanszy; j++){
			liczby[i][j] = NULL;
		}
	}
	for (int i = 0; i < 32; i++) {
		bufor[i] = NULL;
	}
}

void Plansza::rysuj()
{
	textbackground(BLACK);
	this->menu->rysuj();
	if (this->help) {
		gotoxy(MENU_X, MENU_Y + 18);
		textcolor(WHITE);
		cputs("Automatyczna detekcja ON");
	}
	gotoxy(MENU_X, MENU_Y + 5);
	cputs("x: ");
	gotoxy(MENU_X + 2, MENU_Y + 5);
	_itoa_s(this->kursor->getX() - PLANSZA_X, this->bufor, 32, 10);
	cputs(bufor);
	gotoxy(MENU_X, MENU_Y + 6);
	cputs("y: ");
	gotoxy(MENU_X + 2, MENU_Y + 6);
	_itoa_s(this->kursor->getY() - PLANSZA_Y, this->bufor, 32, 10);
	cputs(bufor);
	textcolor(WHITE);
	for (int i = 0; i < this->wysokoscPlanszy; i++) {
		for (int j = 0; j < this->szerokoscPlanszy; j++) {
			if (this->liczby[i][j] != NULL) {
				gotoxy(this->liczby[i][j]->getX(), this->liczby[i][j]->getY());
				if (this->liczby[i][j]->getMod() == true) textcolor(WHITE);
				else textcolor(RED);
				putch(this->liczby[i][j]->getN());
			}
			else putch(' ');
		}
	}
	this->ramka();
	this->wyswIlosciLiczb();
	if (this->useHelp) {
		this->useHelp = false;
		this->polaJednoznaczne();
		gotoxy(MENU_X, MENU_Y + 16);
		textcolor(WHITE);
	}
	gotoxy(this->kursor->getX(), this->kursor->getY());
	textcolor(this->kursor->getKolor());
	textbackground(this->kursor->getTlo());
	putch('|');
	this->zero = 0;
	this->znak = getch();
	switch (znak) {
	case KEY1: case KEY2:
		clrscr();
		this->poruszaniePoPlanszy();
		break;
	case PUT0:
		if ((this->czyMoznaDodac(this->kursor->getX() - PLANSZA_X, this->kursor->getY() - PLANSZA_Y) ||
			this->liczby[this->kursor->getY() - PLANSZA_Y][this->kursor->getX() - PLANSZA_X]->getMod() == true) &&
			this->warunekPierwszy(this->kursor->getX(), this->kursor->getY(), PUT0) &&
			this->warunekDrugi(this->kursor->getX(), this->kursor->getY(), PUT0) &&
			this->warunekTrzeci(this->kursor->getX(), this->kursor->getY(), PUT0)) {
			this->dodajLiczbe(this->kursor->getX(), this->kursor->getY(), PUT0, true);
			if (this->help) this->useHelp = true;
		}
		break;
	case PUT1:
		if ((this->czyMoznaDodac(this->kursor->getX() - PLANSZA_X, this->kursor->getY() - PLANSZA_Y) ||
			this->liczby[this->kursor->getY() - PLANSZA_Y][this->kursor->getX() - PLANSZA_X]->getMod() == true) &&
			this->warunekPierwszy(this->kursor->getX(), this->kursor->getY(), PUT1) &&
			this->warunekDrugi(this->kursor->getX(), this->kursor->getY(), PUT1) &&
			this->warunekTrzeci(this->kursor->getX(), this->kursor->getY(), PUT1)) {
			this->dodajLiczbe(this->kursor->getX(), this->kursor->getY(), PUT1, true);
			if (this->help) this->useHelp = true;
		}
		break;
	case LOSOWE_WYPELNIENIE:
		clrscr();
		this->wypelnienie();
		break;
	case PROSTA_PODPOWIEDZ:
		clrscr();
		this->prostaPodpowiedz(this->kursor->getX(), this->kursor->getY());
		break;
	case ROZMIARY_USER:
		this->nowaPlansza();
		break;
	case PROSTE_SPRAWDZENIE:
		this->prosteSprawdzenie();
		clrscr();
		break;
	case POLA_JEDNOZN:
		this->polaJednoznaczne();
		clrscr();
		break;
	case AUTODETEKCJA:
		if (this->help) this->help = false;
		else this->help = true;
		break;
	case NOWA_GRA:
		clrscr();
		this->domyslnaPlansza();
		break;
	case ZAPIS:
		clrscr();
		this->zapis();
		getch();
		clrscr();
		break;
	case WCZYTANIE:
		clrscr();
		this->wczytywanie();
		getch();
		clrscr();
		break;
	}

}

void Plansza::ramka()
{
	for (int i = RAMKA_Y; i < RAMKA_Y + this->wysokoscPlanszy + 2; i++) {
		for (int j = RAMKA_X; j < RAMKA_X + this->szerokoscPlanszy + 2; j++) {
			if (i == RAMKA_Y || i == RAMKA_Y + this->wysokoscPlanszy + 1) {
				gotoxy(j, i);
				textcolor(RED);
				putch('*');
			}
			if (j == RAMKA_X || j == RAMKA_X + this->szerokoscPlanszy + 1) {
				gotoxy(j, i);
				textcolor(RED);
				putch('*');
			}

		}
	}
}

void Plansza::domyslnaPlansza() 
{
	FILE* plik = NULL;
	fopen_s(&plik, "12x12.txt", "r");
	int x, y;
	char c;
	if (!plik) {
		clrscr();
		cputs("Nie udalo sie otworzyc planszy.");
	}
	else {
		this->freeLiczby();

		fscanf(plik, "%i\n%i\n", &(this->szerokoscPlanszy), &(this->wysokoscPlanszy));
		this->allocLiczby();
		for (int i = 0; i < this->wysokoscPlanszy; i++) {
			for (int j = 0; j < this->szerokoscPlanszy; j++) {
				c = getc(plik);
				if (c == '1') {
					this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, c, false);
				}
				else if (c == '0') {
					this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, c, false);
				}
				else if (c == '.') {
					this->liczby[i][j] = NULL;
				}
			}
			fscanf(plik, "%c", &c);
		}
		this->kursor->setPoczY();
		this->kursor->setPoczX();
		fclose(plik);
	}

}

int Plansza::wczytajLiczbe() {
	int zn = 0, a = 0, i = 0;
	gotoxy(1, 2);
	while (zn != ENTER){
		zn = getch();
		putch(zn);
		if (zn >= '0'&&zn <= '9'){
			a = a * 10 + (zn - '0');
			i++;
		}
		else if (zn == BACKSPACE && i>0){
			i--;
			a /= 10;
			clreol();
		}
	}
	return a;
}

void Plansza::nowaPlansza() {

	this->freeLiczby();
	
	do {
		clrscr();
		gotoxy(1, 1);
		cputs("Podaj dlogosc boku(liczba naturalna parzysta >= 2): ");
		this->szerokoscPlanszy = this->wczytajLiczbe();
	} while (this->szerokoscPlanszy < 2 || this->szerokoscPlanszy % 2 == 1);
	this->wysokoscPlanszy = this->szerokoscPlanszy;
	this->allocLiczby();

	char* fname = new char[MAX_LEN];
	int n = this->szerokoscPlanszy;
	for (int j = 0; j < MAX_LEN; j++) fname[j] = '\0';
	int i = 0, k = 0;
	_itoa_s(n, fname, MAX_LEN, 10);
	while (fname[i] != '\0') i++;
	char txt[5] = ".txt";
	while (txt[k] != '\0') {
		fname[i] = txt[k];
		i++;
		k++;
	}
	fname[i] = '\0';
	FILE* plik = NULL;
	fopen_s(&plik, fname, "r");
	char c;
	if (!plik) {
		for (int i = 0; i < this->wysokoscPlanszy; i++) {
			for (int j = 0; j < this->szerokoscPlanszy; j++) {
				liczby[i][j] = NULL;
			}
		}
		clrscr();
		this->wypelnienie();
	}
	else {
		clrscr();
		for (int i = 0; i < this->wysokoscPlanszy; i++) {
			for (int j = 0; j < this->szerokoscPlanszy; j++) {
				c = getc(plik);
				if (c == '1') {
					this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, c, false);
				}
				else if (c == '0') {
					this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, c, false);
				}
				else if (c == '.') {
					this->liczby[i][j] = NULL;
				}
			}
			fscanf(plik, "%c", &c);
		}
		fclose(plik);
	}
	this->kursor->setPoczY();
	this->kursor->setPoczX();
	
}

void Plansza::wypelnienie() {
	srand(time(NULL));
	char a;
	unsigned int y, x, number;
	unsigned int n = rand() % (this->szerokoscPlanszy*this->wysokoscPlanszy / OGRANICZENIE_LOSOWANIA);
	while (n) {
		bool t = false;
		int i = PROBY;
		while (i > 0 && !t) {
			x = rand() % (this->szerokoscPlanszy);
			y = rand() % (this->wysokoscPlanszy);
			number = rand() % 2;
			if (number == 0) a = '0';
			else a = '1';
			if (this->czyMoznaDodac(x, y) && this->warunekPierwszy(x + PLANSZA_X, y + PLANSZA_Y, a) &&
				this->warunekDrugi(x + PLANSZA_X, y + PLANSZA_Y, a) &&
				this->warunekTrzeci(x + PLANSZA_X, y + PLANSZA_Y, a)) {
				this->dodajLiczbe(x + PLANSZA_X , y + PLANSZA_Y, a, true);
				t = true;
			}
			i--;
		}
		n--;
	}
}

void Plansza::dodajLiczbe(int x, int y, char n, bool m) 
{
	switch (n) {
	case PUT0:
		liczby[y - PLANSZA_Y][x - PLANSZA_X] = new Liczba(x, y, PUT0, m);
		break;
	case PUT1:
		liczby[y - PLANSZA_Y][x - PLANSZA_X] = new Liczba(x, y, PUT1, m);
		break;
	}
}

bool Plansza::czyMoznaDodac(int x, int y)
{
	if (this->liczby[y][x] != NULL) return false;
	else return true;
}

bool Plansza::porownanieLiczb(int x, int y, char n)
{
	if (this->liczby[y][x]->getN() == n)
		return true;
	else return false;
}

bool Plansza::warunekPierwszy(int x, int y, char n)
{
	bool test = true;
	//granica z gory
	if (y == PLANSZA_Y) {
		//jesli lewy gorny rog
		if (x == PLANSZA_X) {
			//jesli lewy gorny rog i oba miejsca wolne 
			if (this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y)) {
				return true;
			}
			else {
				//jesli dol nie jest wolny
				if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1)) {
					//jesli dol jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 2) &&
						this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, this->liczby[y - PLANSZA_Y + 2][x - PLANSZA_X]->getN())) {
						return false;
					}
				}
				//inaczej jesli prawo nie jest wolne
				if (!this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y)) {
					//jesli w prawo jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X + 2, y - PLANSZA_Y) &&
						this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X + 2]->getN())) {
						return false;
					}
				}
				return test;
			}
		}
		//jesli prawy gorny rog
		else if (x == PLANSZA_X + szerokoscPlanszy - 1) {
			//jesli prawy gorny rog i oba miejsca wolne
			if (this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y)) {
				return true;
			}
			else {
				//jesli dol nie jest wolny
				if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1)) {
					//jesli dol jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 2) &&
						this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, this->liczby[y - PLANSZA_Y + 2][x - PLANSZA_X]->getN())) {
						return false;
					}
				}
				//inaczej jesli lewo nie jest wolne
				if (!this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y)) {
					//jesli w lewo jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X - 2, y - PLANSZA_Y) &&
						this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X - 2]->getN())) {
						return false;
					}
				}
				return test;
			}
		}
		//jesli graniczy z gora
		else {
			if (this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y) &&
				this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y)) {
				return true;
			}
			else {
				if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1)) {
					//jesli dol jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 2) &&
						this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, this->liczby[y - PLANSZA_Y + 2][x - PLANSZA_X]->getN())) {
						return false;
					}
				}
				//inaczej jesli lewo nie jest wolne
				if (!this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y) && (x - PLANSZA_X - 2 >= 0)) {
					//jesli w lewo jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X - 2, y - PLANSZA_Y) &&
						this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X - 2]->getN())) {
						return false;
					}
				}
				//jesli prawo zajete
				if (!this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y) && (x - PLANSZA_X + 2 <= this->szerokoscPlanszy - 1)) {
					//jesli w prawo jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X + 2, y - PLANSZA_Y) &&
						this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X + 2]->getN())) {
						return false;
					}
				}
				//jesli lewo i prawo zajete i ta sama liczba
				if (!this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y) && !this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y)
					&& this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, n) && this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, n)) {
					return false;
				}
				return test;
			}//dziala
		}
	}
	//jesli graniczy z dolem planszy
	else if (y == PLANSZA_Y + wysokoscPlanszy - 1) {
		//lewy dolny rog
		if (x == PLANSZA_X) {
			//jesli gora i prawo jest wolne
			if (this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) && this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y)) {
				return true;
			}
			else {
				//jesli gora nie jest wolny
				if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1)) {
					//jesli gora jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 2) &&
						this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, this->liczby[y - PLANSZA_Y - 2][x - PLANSZA_X]->getN())) {
						return false;
					}
				}
				//inaczej jesli prawo nie jest wolne
				if (!this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y)) {
					//jesli w prawo jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X + 2, y - PLANSZA_Y) &&
						this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X + 2]->getN())) {
						return false;
					}
				}
				return test;
			}
		}
		//prawy dolny rog
		else if (x == PLANSZA_X + szerokoscPlanszy - 1) {
			//jesli prawy dolny rog i oba miejsca wolne
			if (this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) && this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y)) {
				return true;
			}
			else {
				//jesli gora nie jest wolny
				if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1)) {
					//jesli fora jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 2) &&
						this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, this->liczby[y - PLANSZA_Y - 2][x - PLANSZA_X]->getN())) {
						return false;
					}
				}
				//inaczej jesli lewo nie jest wolne
				if (!this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y)) {
					//jesli w lewo jest ta sama liczba i nie spelnia warunku 1
					if (this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, n) &&
						!this->czyMoznaDodac(x - PLANSZA_X - 2, y - PLANSZA_Y) &&
						this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X - 2]->getN())) {
						return false;
					}
				}
				return test;
			}
		}
		//graniczy z dolu
		else {
			//jesli gora, lewo, prawo wolne
			if (this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) && this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y) &&
				this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y)) {
				return true;
			}
			//jesli gora zajeta
			if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) && (y - PLANSZA_Y - 2 >= 0)) {
				//jesli gora jest ta sama liczba i nie spelnia warunku 1
				if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, n) &&
					!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 2) &&
					this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, this->liczby[y - PLANSZA_Y - 2][x - PLANSZA_X]->getN())) {
					return false;
				}
			}
			//inaczej jesli lewo nie jest wolne
			if (!this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y) && (x - PLANSZA_X - 2 >= 0)) {
				//jesli w lewo jest ta sama liczba i nie spelnia warunku 1
				if (this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, n) &&
					!this->czyMoznaDodac(x - PLANSZA_X - 2, y - PLANSZA_Y) &&
					this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X - 2]->getN())) {
					return false;
				}
			}
			//jesli prawo zajete
			if (!this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y) && (x - PLANSZA_X + 2 <= this->szerokoscPlanszy - 1)) {
				//jesli w prawo jest ta sama liczba i nie spelnia warunku 1
				if (this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, n) &&
					!this->czyMoznaDodac(x - PLANSZA_X + 2, y - PLANSZA_Y) &&
					this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X + 2]->getN())) {
					return false;
				}
			}
			//jesli prawo i lewo zajete
			if (!this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y) && !this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y)
				&& this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, n) && this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, n)) {
				return false;
			}
			return test;
		}
	}
	//jesli graniczy z bokiem planszy z lewej
	else if (x == PLANSZA_X) {
		//jesli gora, dol, prawo wolne
		if (this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) &&
			this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y)) {
			return true;
		}
		//jesli dol zajety
		if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && (y - PLANSZA_Y + 2 <= this->wysokoscPlanszy - 1)) {
			//jesli dol jest ta sama liczba i nie spelnia warunku 1
			if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, n) &&
				!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 2) &&
				this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, this->liczby[y - PLANSZA_Y + 2][x - PLANSZA_X]->getN())) {
				return false;
			}
		}
		//inaczej jesli gora nie jest wolne
		if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) && (y - PLANSZA_Y - 2 >= 0)) {
			//jesli w gora jest ta sama liczba i nie spelnia warunku 1
			if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, n) &&
				!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 2) &&
				this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, this->liczby[y - PLANSZA_Y - 2][x - PLANSZA_X]->getN())) {
				return false;
			}
		}
		// jesli prawo jest zajete
		if (!this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y)) {
			//jesli w prawo jest ta sama liczba i nie spelnia warunku 1
			if (this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, n) &&
				!this->czyMoznaDodac(x - PLANSZA_X + 2, y - PLANSZA_Y) &&
				this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X + 2]->getN())) {
				return false;
			}
		}
		//jesli gora i dol zajete
		if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && !this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1)
			&& this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, n) && this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, n)) {
			return false;
		}
		return test;
	}
	//jesli graniczy z bokiem planszy z prawej
	else if (x == PLANSZA_X + szerokoscPlanszy - 1) {
		//jesli gora, dol, prawo wolne
		if (this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) &&
			this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y)) {
			return true;
		}
		//jesli dol zajety
		if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && (y - PLANSZA_Y + 2 <= this->wysokoscPlanszy - 1)) {
			//jesli dol jest ta sama liczba i nie spelnia warunku 1
			if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, n) &&
				!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 2) &&
				this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, this->liczby[y - PLANSZA_Y + 2][x - PLANSZA_X]->getN())) {
				return false;
			}
		}
		//inaczej jesli gora nie jest wolne
		if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) && (y - PLANSZA_Y - 2 >= 0)) {
			//jesli w gora jest ta sama liczba i nie spelnia warunku 1
			if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, n) &&
				!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 2) &&
				this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, this->liczby[y - PLANSZA_Y - 2][x - PLANSZA_X]->getN())) {
				return false;
			}
		}
		// jesli prawo jest zajete
		if (!this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y)) {
			//jesli w prawo jest ta sama liczba i nie spelnia warunku 1
			if (this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, n) &&
				!this->czyMoznaDodac(x - PLANSZA_X - 2, y - PLANSZA_Y) &&
				this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X - 2]->getN())) {
				return false;
			}
		}
		//jesli gora i dol zajete przez ta sama liczbe
		if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && !this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1)
			&& this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, n) && this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, n)) {
			return false;
		}
		return test;
	}
	//jesli nie graniczy z krawedzia planszy
	else {
		//jesli pola wokol sa wolne
		if (this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) &&
			this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y) && this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y)) {
			return true;
		}
		else {
			//jesli dol nie jest wolny
			if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && (y - PLANSZA_Y + 2 <= this->wysokoscPlanszy - 1)) {
				//jesli dol jest ta sama liczba i nie spelnia warunku 1
				if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, n) &&
					!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 2) &&
					this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, this->liczby[y - PLANSZA_Y + 2][x - PLANSZA_X]->getN())) {
					return false;
				}
			}
			//inaczej jesli gora nie jest wolna
			if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1) && (y - PLANSZA_Y - 2 >= 0)) {
				//jesli dol jest ta sama liczba i nie spelnia warunku 1
				if (this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, n) &&
					!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 2) &&
					this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, this->liczby[y - PLANSZA_Y - 2][x - PLANSZA_X]->getN())) {
					return false;
				}
			}
			//inaczej jesli lewo nie jest wolne
			if (!this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y) && (x - PLANSZA_X - 2 >= 0)) {
				//jesli w lewo jest ta sama liczba i nie spelnia warunku 1
				if (this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, n) &&
					!this->czyMoznaDodac(x - PLANSZA_X - 2, y - PLANSZA_Y) &&
					this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X - 2]->getN())) {
					return false;
				}
			}
			//inaczej jesli prawo nie jest wolne
			if (!this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y) && (x - PLANSZA_X + 2 <= this->szerokoscPlanszy - 1)) {
				//jesli w prawo jest ta sama liczba i nie spelnia warunku 1
				if (this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, n) &&
					!this->czyMoznaDodac(x - PLANSZA_X + 2, y - PLANSZA_Y) &&
					this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, this->liczby[y - PLANSZA_Y][x - PLANSZA_X + 2]->getN())) {
					return false;
				}
			}
			//jesli prawo i lewo zajete
			if (!this->czyMoznaDodac(x - PLANSZA_X + 1, y - PLANSZA_Y) && !this->czyMoznaDodac(x - PLANSZA_X - 1, y - PLANSZA_Y)
				&& this->porownanieLiczb(x - PLANSZA_X + 1, y - PLANSZA_Y, n) && this->porownanieLiczb(x - PLANSZA_X - 1, y - PLANSZA_Y, n)) {
				return false;
			}
			//jesli gora i dol zajete
			if (!this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y + 1) && !this->czyMoznaDodac(x - PLANSZA_X, y - PLANSZA_Y - 1)
				&& this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y + 1, n) && this->porownanieLiczb(x - PLANSZA_X, y - PLANSZA_Y - 1, n)) {
				return false;
			}
			return test;
		}
	}
}

bool Plansza::warunekDrugi(int x, int y, char n) {
	int a = 0;
	//sprawdzamy poziom
	for (int i = 0; i < this->szerokoscPlanszy; i++) {
		//jesli jest juz n/2 przerwij
		if (a >= this->szerokoscPlanszy / 2) {
			return false;
		}
		else if (this->liczby[y - PLANSZA_Y][i] != NULL && this->liczby[y - PLANSZA_Y][i]->getN() == n) a++;
	}
	a = 0;
	//sprawdzamy pion
	for (int i = 0; i < this->wysokoscPlanszy; i++) {
		//jesli jest juz n/2 przerwij
		if (a >= this->wysokoscPlanszy / 2) {
			return false;
		}
		else if (this->liczby[i][x - PLANSZA_X] != NULL && this->liczby[i][x - PLANSZA_X]->getN() == n) a++;
	}
	return true;
}

bool Plansza::warunekTrzeci(int x, int y, char n) {
	bool t = true;
	int a = 0;
	this->w3y = 0, this->w3x = 0;
	//porownuje wszystkie wiersze z wierszem w ktory wstawiam liczbe 
	for (int i = 0; i < this->wysokoscPlanszy; i++) {
		for (int j = 0; j < this->szerokoscPlanszy; j++) {
			//jesli liczba w sprawdzanym wierszu jest taka sama jak w tym do ktorego wstawiamy
			if ((i != y - PLANSZA_Y) && (j != x - PLANSZA_X) && liczby[y - PLANSZA_Y][j]  != NULL &&
				liczby[i][j] != NULL && (liczby[i][j]->getN() == liczby[y - PLANSZA_Y][j]->getN()))
				a++;
		}
		//jesli wszystkie liczby sie powtorzyly to sprawdz miejsce w ktorym chcesz wstawic i porownywane miejsce
		if (i != y - PLANSZA_Y && a == this->szerokoscPlanszy - 1 && liczby[i][x - PLANSZA_X] != NULL &&
			liczby[i][x - PLANSZA_X]->getN() == n) {
			w3y = i + 1;
			return false;
		}
		else a = 0;
	}
	a = 0;
	//porownuje wszystkie piony z tym w ktory wstawiam liczbe 
	for (int i = 0; i < this->szerokoscPlanszy; i++) {
		for (int j = 0; j < this->wysokoscPlanszy; j++) {
			if ((j != y - PLANSZA_Y) && (i != x - PLANSZA_X) && (liczby[j][x - PLANSZA_X] != NULL) &&
				liczby[j][i] != NULL && (liczby[j][i]->getN() == liczby[j][x - PLANSZA_X]->getN()))
				a++;
		}
		if (i != x - PLANSZA_X && a == this->wysokoscPlanszy - 1 && liczby[y - PLANSZA_Y][i] != NULL &&
			liczby[y - PLANSZA_Y][i]->getN() == n) {
			w3x = i + 1;
			return false;
		}
		else a = 0;
	}
	return t;
}

void Plansza::prostaPodpowiedz(int x, int y){
	bool w1 = true, w2 = true, w3 = true;
	int i = 3;
	if (!this->warunekPierwszy(x, y, PUT0)) w1 = false;
	if (!this->warunekDrugi(x, y, PUT0)) w2 = false;
	if (!this->warunekTrzeci(x, y, PUT0)) w3 = false;
	if (w1 && w2 && w3) {
		gotoxy(MENU_X, MENU_Y + 17 + i);
		cputs("Mozna wpisac 0");
		i++;
	}
	else {
		gotoxy(MENU_X, MENU_Y + 17 + i);
		cputs("Nie mozna wpisac 0, bo: ");
		i++;
		if (!w1) {
			gotoxy(MENU_X, MENU_Y + 17 + i);
			cputs("Byloby to trzecie 0 (war 1)");
			i++;
		}
		if (!w2) {
			gotoxy(MENU_X, MENU_Y + 17 + i);
			cputs("Jest juz n/2 zer");
			i++;
		}
		if (!w3) {
			gotoxy(MENU_X, MENU_Y + 17 + i);
			cputs("Przeczy war 3 ");
			i++;
			if (w3x) {
				cputs(" Kolumna: ");
				putch(w3x + 48);
			}
			if (w3y) {
				cputs(" Wiersz: ");
				putch(w3y + 48);
			}
		}
	}
	w1 = true; w2 = true; w3 = true;
	if (!this->warunekPierwszy(x, y, PUT1)) w1 = false;
	if (!this->warunekDrugi(x, y, PUT1)) w2 = false;
	if (!this->warunekTrzeci(x, y, PUT1)) w3 = false;
	if (w1 && w2 && w3) {
		gotoxy(MENU_X, MENU_Y + 17 + i);
		cputs("Mozna wpisac 1");
		i++;
	}
	else {
		gotoxy(MENU_X, MENU_Y + 17 + i);
		cputs("Nie mozna wpisac 1, bo: ");
		i++;
		if (!w1) {
			gotoxy(MENU_X, MENU_Y + 17 + i);
			cputs("Bylaby to trzecia 1 (war 1)");
			i++;
		}
		if (!w2) {
			gotoxy(MENU_X, MENU_Y + 17 + i);
			cputs("Jest juz n/2 jedynek");
			i++;
		}
		if (!w3) {
			gotoxy(MENU_X, MENU_Y + 17 + i);
			cputs("Przeczy war3 ");
			if (w3x) {
				cputs(" Kolumna: ");
				putch(w3x + 48);
			}
			if (w3y) {
				cputs(" Wiersz: ");
				putch(w3y + 48);
			}
		}
	}
}

void Plansza::prosteSprawdzenie() {
	textbackground(BLUE);
	for (int i = 0; i < this->wysokoscPlanszy; i++) {
		for (int j = 0; j < this->szerokoscPlanszy; j++) {
			if (!(liczby[i][j] != NULL) && (!this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT0) || !this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT0) ||
				!this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT0)) &&	(!this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT1) ||
				!this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT1) || !this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT1))) {
				gotoxy(PLANSZA_X + j, PLANSZA_Y + i);
				putch(' ');
			}
		}
	}
	getch();
	textbackground(BLACK);
}

void Plansza::wyswIlosciLiczb() {
	int n0 = 0, n1 = 0;
	textcolor(GREEN);
	for (int i = 0; i < this->wysokoscPlanszy; i++) {
		for (int j = 0; j < this->szerokoscPlanszy; j++) {
			if (liczby[i][j] != NULL) {
				if(liczby[i][j]->getN() == PUT1) n1++;
				else n0++;
			}
		}
		gotoxy(this->x + this->szerokoscPlanszy + 1, this->y + i);
		if (n0 < 9) {
			putch(n0 + 48);
		}
		else if (n0 < 35) putch(n0 + 56);
		gotoxy(this->x + this->szerokoscPlanszy + 3, this->y + i);
		if (n1 < 9) {
			putch(n1 + 48);
		}
		else if (n1 < 35) putch(n1 + 56);
		n1 = 0;
		n0 = 0;
	}

	for (int i = 0; i < this->szerokoscPlanszy; i++) {
		for (int j = 0; j < this->wysokoscPlanszy; j++) {
			if (liczby[j][i] != NULL) {
				if (liczby[j][i]->getN() == PUT1) n1++;
				else n0++;
			}
		}
		gotoxy(this->x + i, this->y + this->wysokoscPlanszy + 1);
		if (n0 < 9) {
			putch(n0 + 48);
		}
		else if (n0 < 35) putch(n0 + 56);
		gotoxy(this->x + i, this->y + this->wysokoscPlanszy + 3);
		if (n1 < 9) {
			putch(n1 + 48);
		}
		else if (n1 < 35) putch(n1 + 56);
		n1 = 0;
		n0 = 0;
	}
}

void Plansza::polaJednoznaczne() {
	textbackground(YELLOW);
	for (int i = 0; i < this->wysokoscPlanszy; i++) {
		for (int j = 0; j < this->szerokoscPlanszy; j++) {
			if (liczby[i][j] == NULL && (((this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT0) && this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT0) &&
				this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT0)) && (!this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT1) ||
				!this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT1) || !this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT1))) || 
				((this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT1) && this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT1) &&
				this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT1)) && (!this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT0) ||
				!this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT0) || !this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT0))))) {
				gotoxy(PLANSZA_X + j, PLANSZA_Y + i);
				putch(' ');
			}
		}
	}
	int zn;
	zn = getch();
	if (zn == UZUPELNIENIE_JEDNOZN) {
		for (int i = 0; i < this->wysokoscPlanszy; i++) {
			for (int j = 0; j < this->szerokoscPlanszy; j++) {
				if (liczby[i][j] == NULL) {
					if ((this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT0) && this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT0) &&
						this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT0)) && (!this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT1) ||
						!this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT1) || !this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT1))) {
						this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, PUT0, true);
					}
					else if ((this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT1) && this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT1) &&
						this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT1)) && (!this->warunekPierwszy(j + PLANSZA_X, i + PLANSZA_Y, PUT0) ||
						!this->warunekDrugi(j + PLANSZA_X, i + PLANSZA_Y, PUT0) || !this->warunekTrzeci(j + PLANSZA_X, i + PLANSZA_Y, PUT0))) {
						this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, PUT1, true);
					}
				}
			}
		}
	}
	textbackground(BLACK);
}

void Plansza::poruszaniePoPlanszy()
{
	this->zero = 1;
	this->znak = getch();
	switch (znak) {
	case DOL:
		if(this->kursor->getY() < PLANSZA_Y + this->wysokoscPlanszy - 1) this->kursor->setY(SETUP_R);
		break;
	case GORA:
		if(this->kursor->getY() > PLANSZA_Y) this->kursor->setY(SETD_L);
		break;
	case LEWO:
		if(this->kursor->getX() > PLANSZA_X) this->kursor->setX(SETD_L);
		break;
	case PRAWO:
		if(this->kursor->getX() < PLANSZA_X + this->szerokoscPlanszy - 1) this->kursor->setX(SETUP_R);
		break;
	default:
		break;
	}
}

void Plansza::gra()
{
	do {
		this->rysuj();
	} while (this->znak != ESC);

}

void Plansza::zapis() {
	char* fname = new char[MAX_NAME];
	this->wczytajNazwe(fname);
	FILE* plik = NULL;
	fopen_s(&plik, fname, "w+");
	if (!plik) {
		clrscr();
		gotoxy(1, 1);
		cputs("Nie udalo sie zapisac planszy. Nacisnij przycisk aby kontynuowac");
	}
	else {
		fprintf(plik, "%d\n%d\n", this->szerokoscPlanszy, this->wysokoscPlanszy);
		for (int i = 0; i < this->wysokoscPlanszy; i++) {
			for (int j = 0; j < this->szerokoscPlanszy; j++) {
				if (this->liczby[i][j] == NULL) {
					fprintf(plik, NOTHING);
				}
				else if (this->liczby[i][j]->getN() == PUT1) {
					if (this->liczby[i][j]->getMod() == false) {
						fprintf(plik, JEDEN_NOTM);
					}
					else fprintf(plik, JEDEN_MOD);
				}
				else if (this->liczby[i][j]->getN() == PUT0) {
					if (this->liczby[i][j]->getMod() == false) {
						fprintf(plik, ZERO_NOTM);
					}
					else fprintf(plik, ZERO_MOD);
				}
			}
			fprintf(plik, "\n");
		}
		fclose(plik);
	}

}

void Plansza::wczytywanie() {
	char* fname = new char[MAX_NAME];
	this->wczytajNazwe(fname);
	FILE* plik = NULL;
	fopen_s(&plik, fname, "r");
	char c;
	if (!plik) {
		clrscr();
		gotoxy(1, 1);
		cputs("Nie udalo sie otworzyc planszy. Nacisnij przycisk aby kontynuowac");
	}
	else {
		this->freeLiczby();
		fscanf(plik, "%i\n%i\n", &(this->szerokoscPlanszy), &(this->wysokoscPlanszy));
		this->allocLiczby();
		for (int i = 0; i < this->wysokoscPlanszy; i++) {
			for (int j = 0; j < this->szerokoscPlanszy; j++) {
				c = getc(plik);
				if (c == JM) {
					this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, PUT1, true);
				}
				else if (c == JNM) {
					this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, PUT1, false);
				}
				else if (c == ZM) {
					this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, PUT0, true);
				}
				else if (c == ZNM) {
					this->dodajLiczbe(j + PLANSZA_X, i + PLANSZA_Y, PUT0, false);
				}
				else if (c == '.') {
					this->liczby[i][j] = NULL;
				}
			}
			fscanf(plik, "%c", &c);
		}
		this->kursor->setPoczY();
		this->kursor->setPoczX();
		fclose(plik);
	}
}

void Plansza::wczytajNazwe(char* name) {
	int zn, i = 0;
	do
	{
		gotoxy(5, 1);
		cputs("Podaj nazwe pliku: ");
		zn = getch();
		if (zn != ENTER) {
			name[i] = zn;
			i++; 
			gotoxy(25 + i, 1);
			putch(zn);
		}
	} while (zn != ENTER);
	name[i] = '.';
	i++;
	name[i] = 't';
	i++;
	name[i] = 'x';
	i++;
	name[i] = 't';
	i++;
	name[i] = '\0';
}

void Plansza::allocLiczby() {
	this->liczby = new Liczba**[this->wysokoscPlanszy];
	for (int i = 0; i < this->wysokoscPlanszy; i++) {
		this->liczby[i] = new Liczba*[this->szerokoscPlanszy];
	}
}

void Plansza::freeLiczby() {
	for (int i = 0; i < this->wysokoscPlanszy; i++)
	{
		delete[] liczby[i];
	}
	delete[] liczby;
}

Plansza::~Plansza(){
	this->freeLiczby();
	delete menu;
	delete kursor;
	delete[] bufor;
}
