#include "Kursor.h"
#include "conio2.h"
#include "Stale.h"


Kursor::Kursor()
{
	this->x = PLANSZA_X;
	this->y = PLANSZA_Y;
	this->kolor = WHITE;
	this->tlo = BLACK;
}

int Kursor::getY()
{
	return this->y;
}

int Kursor::getX()
{
	return this->x;
}

int Kursor::getKolor()
{
	return this->kolor;
}

int Kursor::getTlo()
{
	return this->tlo;
}

void Kursor::setY(int y)
{
	this->y += y;
}

void Kursor::setX(int x)
{
	this->x += x;
}

void Kursor::setPoczY()
{
	this->y = PLANSZA_Y;
}

void Kursor::setPoczX()
{
	this->x = PLANSZA_X;
}

Kursor::~Kursor()
{
}
