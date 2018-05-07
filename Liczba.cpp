#pragma once
#include "Liczba.h"
#include "Plansza.h"


Liczba::Liczba(int x, int y, char n, bool modify) : x(x), y(y), n(n), modify(modify) {}

int Liczba::getX()
{
	return this->x;
}

int Liczba::getY()
{
	return this->y;
}

char Liczba::getN()
{
	return this->n;
}

bool Liczba::getMod()
{
	return this->modify;
}

void Liczba::setN(char n)
{
	this->n = n;
}

void Liczba::setX(int x)
{
	this->x = x;
}

void Liczba::setY(int y)
{
	this->y = y;
}

Liczba::~Liczba() {}
