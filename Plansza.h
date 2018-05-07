#pragma once
class Liczba;
class Kursor;
class Menu;
class Plansza
{
private:
	//wspolrzedne poczatkowe planszy
	int x;
	int y;
	//wielkosc planszy
	int szerokoscPlanszy;
	int wysokoscPlanszy;

	int w3x, w3y; //w3x, w3y to numery kolumny/wiersza ktroe nie spelniaja w3 
	bool help, useHelp;
	char* bufor;
	int znak;
	int zero;
	Menu* menu;
	Kursor* kursor;
	Liczba*** liczby;


	void rysuj();
	void ramka();
	int wczytajLiczbe();
	void domyslnaPlansza();
	void nowaPlansza();
	void wypelnienie();
	void dodajLiczbe(int x, int y, char n, bool m);
	bool czyMoznaDodac(int x, int y); //czy miejsce jest puste
	bool porownanieLiczb(int x, int y, char n);
	bool warunekPierwszy(int x, int y, char n);
	bool warunekDrugi(int x, int y, char n);
	bool warunekTrzeci(int x, int y, char n);
	void prostaPodpowiedz(int x, int y);
	void prosteSprawdzenie();
	void wyswIlosciLiczb();
	void polaJednoznaczne();
	void poruszaniePoPlanszy();
	void zapis();
	void wczytywanie();
	void wczytajNazwe(char* name);
	void allocLiczby();
	void freeLiczby();
public:
	Plansza();
	void gra();

	~Plansza();
};

