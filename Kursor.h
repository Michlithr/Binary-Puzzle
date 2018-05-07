#pragma once
class Kursor
{
private: 
	int x; 
	int y;
	int kolor;
	int tlo;
public:
	Kursor();
	int getY();
	int getX();
	int getKolor();
	int getTlo();
	void setY(int y);
	void setX(int x);
	void setPoczY();
	void setPoczX();
	~Kursor();
};

