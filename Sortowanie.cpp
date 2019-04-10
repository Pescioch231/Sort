#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

template <typename Typ>
void Wypisz_tablice(Typ tab[], int rozm)
{
	for (int i = 0; i < rozm; i++)
	{
		cout << tab[i] << "\t";
		if ((i + 1) % 10 == 0) // Estetyczny wygląd w konsoli
			cout << endl;
	}
}

int Wybierz_srodek(int pocz, int kon)
{
	return (kon - pocz) / 2 + pocz;
}

template <typename Typ>
void Zamien_indeksy(Typ tablica[], int numer1, int numer2)
{
	Typ pomoc = tablica[numer1];
	tablica[numer1] = tablica[numer2];
	tablica[numer2] = pomoc;
}

template <typename Typ>
void Odwroc_tablice(Typ tab[], int rozmiar)
{
	int i = 0;
	int j = rozmiar - 1;
	while (i < j)
	{
		Zamien_indeksy(tab, i, j);
		i++;
		j = j - 1;
	}
}

template <typename Typ>
int Podziel(Typ tab[], int pocz, int kon)
{
	int srodek_ind = Wybierz_srodek(pocz, kon);
	Typ srodek_wart = tab[srodek_ind];
	Zamien_indeksy(tab, srodek_ind, kon);
	int aktualny_ind = pocz;
	for (int i = pocz; i < kon; i++)
	{
		if (tab[i] < srodek_wart)
		{
			Zamien_indeksy(tab, i, aktualny_ind);
			aktualny_ind = aktualny_ind + 1;
		}
	}
	Zamien_indeksy(tab, aktualny_ind, kon);
	return aktualny_ind;
}

template <typename Typ>
void Quicksort(Typ tab[], int pocz, int kon)
{
	if (pocz < kon)
	{
		int pomoc = Podziel(tab, pocz, kon);
		Quicksort(tab, pocz, pomoc - 1);
		Quicksort(tab, pomoc + 1, kon);
	}
}

template <typename Typ>
void Scalanie(Typ tab[], int pocz, int srodek, int kon)
{
	int i = pocz, j = srodek + 1, k = 0;
	int rozmiar = kon - pocz + 1;
	Typ *tab_pomoc = new Typ[rozmiar];
	
	while(k < rozmiar)
	{
		if(i > srodek)
			for (; j <= kon; j++)
			{
				tab_pomoc[k] = tab[j];
				k++;
			}
		else if(j > kon)
			for (; i <= srodek; i++)
			{
				tab_pomoc[k] = tab[i];
				k++;
			}
		else
		{
			if (tab[i] <= tab[j])
			{
				tab_pomoc[k] = tab[i];
				i++;
				k++;
			}
			else
			{
				tab_pomoc[k] = tab[j];
				j++;
				k++;
			}
		}
	}
	int p = pocz;
	for (int l = 0; l < rozmiar; l++)
	{
		tab[p] = tab_pomoc[l];
		p++;
	}
	delete [] tab_pomoc;

}

template <typename Typ>
void Sortowanie_scalanie(Typ tab[], int pocz, int kon)
{
	if (pocz < kon)
	{
		int srodek = Wybierz_srodek(pocz, kon);
		Sortowanie_scalanie(tab, pocz, srodek);
		Sortowanie_scalanie(tab, srodek + 1, kon);
		Scalanie(tab, pocz, srodek, kon);
	}
}

template <typename Typ>
void Utworz_kopiec(Typ tab[], int pocz, int kon)
{
	kon++;
	int rozmiar = kon - pocz + 1;
	Typ *tab_pomoc = new Typ[rozmiar + 1];
	tab_pomoc[0] = 0;							// Nie bierze udziału w sortowaniu
	for (int l = 1; l < rozmiar + 1; l++)
	{
		tab_pomoc[l] = tab[pocz + l - 1];
	}
	int j, k;
	for (int i = 1; i < rozmiar; i++)
	{
		j = i;
		k = j / 2;
		while (tab_pomoc[j] > tab_pomoc[k] and k != 0)
		{
			Zamien_indeksy(tab_pomoc, k, j);
			j = k;
			k = j / 2;
		}

	}
	for (int l = 1; l < rozmiar + 1; l++)
	{
		tab[pocz + l - 1] = tab_pomoc[l];
	}
	delete [] tab_pomoc;
}

template <typename Typ>
void Sortowanie_kopcowanie(Typ tab[], int pocz, int kon)
{
	kon++;
	int rozmiar = kon - pocz + 1;
	Typ *tab_pomoc = new Typ[rozmiar + 1];
	tab_pomoc[0] = 0;
	for (int l = 1; l < rozmiar + 1; l++)
	{
		tab_pomoc[l] = tab[pocz + l - 1];
	}

	for (int i = 1; i < rozmiar - 1; i++)
	{
		Zamien_indeksy(tab_pomoc, 1, rozmiar - i);
		for (int j = 1; j < rozmiar;)
		{
			if (2 * j < rozmiar - i and 2 * j + 1 < rozmiar - i)   // Gdy istnieje dwóch synów
			{
				if (tab_pomoc[2 * j] >= tab_pomoc[2 * j + 1] and tab_pomoc[2 * j] > tab_pomoc[j])
				{
					Zamien_indeksy(tab_pomoc, j, 2 * j);
					j = 2 * j;
				}
				else if (tab_pomoc[2 * j + 1] > tab_pomoc[2 * j] and tab_pomoc[2 * j + 1] > tab_pomoc[j])
				{
					Zamien_indeksy(tab_pomoc, j, 2 * j + 1);
					j = 2 * j + 1;
				}
				else
					j = rozmiar;
			}
			else if ((2 * j < rozmiar - i) and (2 * j + 1 == rozmiar - i)) //Gdy istnieje tylko lewy syn
			{
				if (tab_pomoc[2 * j] > tab_pomoc[j])
				{
					Zamien_indeksy(tab_pomoc, j, 2 * j);
					j = 2 * j;
				}
				else
					j = rozmiar;  //Gdy synowie nie istnieją
			}
			else
				j = rozmiar;
		}
	}
	for (int l = 1; l < rozmiar + 1; l++)
	{
		tab[pocz + l - 1] = tab_pomoc[l];
	}
	delete[] tab_pomoc;
}

template <typename Typ>
void Hybryda(Typ tab[], int pocz, int kon, int M)
{
	if (M <= 0)
	{
		Utworz_kopiec(tab, pocz, kon);
		Sortowanie_kopcowanie(tab, pocz, kon);
		return;
	}
	if(pocz < kon and M>0){
		int pomoc = Podziel(tab, pocz, kon);
		Hybryda(tab, pocz, pomoc - 1, M - 1);
		Hybryda(tab, pomoc + 1, kon, M - 1);
	}
}

template <typename Typ>
void Sortowanie_Introspektywne (Typ tab[] , int N)
{
	Hybryda (tab, 0, N, (int)floor(2 * log2 (N)));
}

template <typename Typ>
void czyOk(Typ tablica[], int rozmiar)
{
	bool czy_ok = 0;
	for (int g = 0; g < rozmiar - 1; g++)
	{
		if (tablica[g] > tablica[g + 1])
		{
			czy_ok++;
		}
	}
	if (czy_ok == 0)
		cout << "Wszystko okej!" << endl;
	else
		cout << "Cos nie tak!" << endl;
}

template <typename Typ>
void Wypelnij_tablice(int rozmiar, Typ tab[], double procent, bool odwrot)
{
	double czesc_posortowana = procent/100;
	if (czesc_posortowana >= 0 && czesc_posortowana <= 1)
	{
		int ile_posortowane = (rozmiar -1) * czesc_posortowana;   //rozmiar czesci posortowanej
		srand(time(NULL));
		for (int i = 0; i < rozmiar; i++)
		{
			tab[i] = rand() % rozmiar + 1;
			//tab[i] = tab[i] * 0.1; //Sprawdzenie czy algorytm działa na liczbach zmiennoprzecinkowych
		}
		Quicksort(tab, 0, ile_posortowane);
	}
	else 
		cout << "Ulamek musi byc z przedzialu 0 - 1" << endl;
	if (odwrot == 1)
		Odwroc_tablice(tab, rozmiar);
};

template <typename Typ>
void Testowanie(double czesc_posortowana, int wybor, bool odwrot) 
{
	const int ilosc_pomiarow = 100;  //Ilość powtórzeń pojedynczego pomiaru
	double Pomiary[ilosc_pomiarow];  //Wyniki pomiarów
	clock_t start, stop;
	double czas;
	double licznik, srednia;
	fstream plik;

	plik.open("dane.txt", ios::out | ios::app);
	if (plik.good() == true)
	{
		plik << endl << wybor << "_" << czesc_posortowana << "%" << endl;
		plik.close();
	}
	else
		cout << "BLAD: nie mozna otworzyc pliku." << endl;
	
	for (int j = 0; j < 5; j++)
	{
		int sizeTab[5] = { 10000, 50000, 100000, 500000, 1000000 };      // rozmiary tablic do testów
		for (int i = 0; i < ilosc_pomiarow; i++)
		{
			Typ *tablica = new Typ[sizeTab[j]];
			Wypelnij_tablice(sizeTab[j], tablica, czesc_posortowana, odwrot);

			switch (wybor) {
			case 1:
				start = clock();
				Quicksort(tablica, 0, sizeTab[j] - 1);
				stop = clock();
				if (i == 0 and j == 0)
					Wypisz_tablice(tablica, sizeTab[j]);
				czyOk(tablica, sizeTab[j]);
				break;
			case 2:
				start = clock();
				Sortowanie_scalanie(tablica, 0, sizeTab[j] - 1);
				stop = clock();
				czyOk(tablica, sizeTab[j]);
				break;
			case 3:
				start = clock();
				Sortowanie_Introspektywne(tablica, sizeTab[j] - 1);
				stop = clock();
				czyOk(tablica, sizeTab[j]);
				break;
			}
			czas = (double)(stop - start) / CLOCKS_PER_SEC;
			Pomiary[i] = czas;
			delete[] tablica;
		}
		licznik = 0;
		for (int i = 0; i < ilosc_pomiarow; i++) 
			licznik += Pomiary[i];
		srednia = licznik / ilosc_pomiarow;

		double minimalna_wartosc = Pomiary[0];
		for (int i = 0; i < ilosc_pomiarow; i++)
			if (minimalna_wartosc > Pomiary[i])
				minimalna_wartosc = Pomiary[i];

		double maksymalna_wartosc = Pomiary[0];
		for (int i = 0; i < ilosc_pomiarow; i++)
			if (maksymalna_wartosc < Pomiary[i])
				maksymalna_wartosc = Pomiary[i];

		plik.open("dane.txt", ios::out | ios::app);
		if (plik.good() == true)
		{
			plik << minimalna_wartosc << "\t" << srednia << "\t" << maksymalna_wartosc << endl;
			plik.close();
		}else
			cout << "BLAD: nie mozna otworzyc pliku." << endl;
	}
}

int main()
{
	double czesc_posortowana = 0;  // ile posortowane

	cout << "Menu programu do sortowania" << endl;
	do {
		cout << "Podaj w ilu % ma byc posortowana tablica:";
		cin >> czesc_posortowana;
		if(czesc_posortowana < 0 or czesc_posortowana>100)
			cout << "wpisz wartość od 0 do 100"<< endl;
	} while (czesc_posortowana < 0 or czesc_posortowana>100);

	bool Czy_odwrocona = 0;
	cout << "Czy odwrocic?\n1 - Tak\n0 - Nie\n";
	cin >> Czy_odwrocona;

	cout << "Wybierz rodzaj sortowania" << endl;
	cout << "1 - Quicksort" << endl << "2 - Przez scalanie" << endl << "3 - Introspektywne" << endl;
	cout << "Wpisz numer sortowania:";
	int x = 0;
	cin >> x;

	switch (x)
	{
	case 1:
		cout << "Wybrales Quicksort" << endl;
		Testowanie<float>(czesc_posortowana, x, Czy_odwrocona);
		break;
	case 2:
		cout << "Wybrales Sortowanie przez scalanie" << endl;
		Testowanie<float>(czesc_posortowana, x, Czy_odwrocona);
		break;
	case 3:
		cout << "Wybrales Sortowanie Introspektywne" << endl;
		Testowanie<float>(czesc_posortowana, x, Czy_odwrocona);
		break;
	}
	return 0;
}




























// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
