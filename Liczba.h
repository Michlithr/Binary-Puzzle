#pragma once
class Liczba
{
private:
	int x;
	int y;
	char n;
	const bool modify;
public:
	Liczba(int x, int y, char n, bool modify);
	int getX();
	int getY();
	char getN();
	bool getMod();
	void setN(char n);
	void setX(int x);
	void setY(int y);
	virtual ~Liczba();
};

