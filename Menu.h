#pragma once
class Menu
{
private:
	int szerokoscMenu; //punkt poczatkowy x0
	int wysokoscMenu; //punkt poczatkowy y0
	int pozycjaKursora;
	int kolor;
	int tlo;
public:
	Menu();
	void rysuj();
	~Menu();
};

