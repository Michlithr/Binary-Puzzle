#pragma once
//podstawowa wielkosc planszy
#define WYSOKOSC_BAZOWA 10
#define SZEROKOSC_BAZOWA 10
//polozenie dla planszy
#define PLANSZA_X 50
#define PLANSZA_Y 2
//polozenie dla ramki
#define RAMKA_X PLANSZA_X-1
#define RAMKA_Y PLANSZA_Y-1
//polozenie dla menu 
#define MENU_X 2
#define MENU_Y 1
//max nazwa pliku
#define MAX_LEN 32
//sterowanie kursorem
#define KEY1 0 //pierwsza stala warunkowa do wychwycenia specjalnego znaku klawiatury (strzalki)
#define KEY2 224 //druga stala warunkowa do wychwycenia specjalnego znaku klawiatury (strzalki)
#define DOL 80 //stale poszczegolnych kierunkow strzalek
#define GORA 72
#define PRAWO 77
#define LEWO 75
#define SETD_L -1 //stale do zmiany polozenia kursora 
#define SETUP_R 1
#define ENTER 0x0d 
#define BACKSPACE 0x08
//losowe wypelnienie planszy
#define PROBY 10
#define OGRANICZENIE_LOSOWANIA 5 //dzielnik dla x*y planszy
//obsluga zdarzen z klawiatury
#define PUT1 '1'
#define PUT0 '0'
#define NOWA_GRA 'n'
#define ESC 27
#define LOSOWE_WYPELNIENIE 'o'
#define PROSTA_PODPOWIEDZ 'p'
#define PROSTE_SPRAWDZENIE 'k'
#define POLA_JEDNOZN 'j'
#define UZUPELNIENIE_JEDNOZN 'w'
#define AUTODETEKCJA 'a'
#define ROZMIARY_USER 'r'
#define ZAPIS 's'
#define WCZYTANIE 'l'
#define PELNE_SPRAWDZENINE 'b'
//zapis i odczyt pliku mod oznacza modyfikowalny, notm - niemodyfikowalny
#define JEDEN_MOD "j" 
#define JEDEN_NOTM "n"
#define ZERO_MOD "z"
#define ZERO_NOTM "x"
#define NOTHING "."
#define MAX_NAME 50
#define JM 'j'
#define JNM 'n'
#define ZM 'z'
#define ZNM 'x'