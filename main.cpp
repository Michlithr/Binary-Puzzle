#include <stdio.h>
#include <stddef.h>
#include "Stale.h"
#include "Plansza.h"
#include "conio2.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

/* Uwaga: w docelowym programie nale¿y zadeklarowaæ odpowiednie
sta³e, na przyk³ad po to, aby wyeliminowaæ z programu
wartoœci numeryczne umieszczajac w ich miejsce
dobrze dobrane identyfikatory */

int main() {
	Plansza* plansza = new Plansza;
	plansza->gra();
	return 0;
}
