#include "Menu.h"
#include "Stale.h"
#include "conio2.h"


Menu::Menu()
{
	this->szerokoscMenu = MENU_X;
	this->wysokoscMenu = MENU_Y;
	this->kolor = LIGHTGRAY;
	this->tlo = BLACK;
}

void Menu::rysuj()
{
	textcolor(kolor);
	textbackground(tlo);
	gotoxy(this->szerokoscMenu, this->wysokoscMenu);
	cputs("Michal Litwa, 169495");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 1);
	cputs("strzalki: poruszanie");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 2);
	cputs("0, 1: wpisanie liczby");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 3);
	cputs("Esc = zwyjscie");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 4);
	cputs("Pozycja kursora:");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 7);
	cputs("a,b,c,d,e,f,g,h,i,j,k,l,m,n");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 8);
	cputs("n - nowa gra(domyslna)");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 9);
	cputs("o - losowe wypelnienie");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 10);
	cputs("p - prosta podpowiedz");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 11);
	cputs("j - wskazanie pol jednoznacznych");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 12);
	cputs("k - proste sprawdzenie konca gry");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 13);
	cputs("r - nowa gra z podaniem rozmiaru");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 14);
	cputs("a - ON/OFF autodetekcja konca gry");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 15);
	cputs("w - uzupelnij zaznaczone pola jednoznaczne");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 16);
	cputs("s - zapis");
	gotoxy(this->szerokoscMenu, this->wysokoscMenu + 17);
	cputs("l - wczytywanie");
}


Menu::~Menu()
{
}
