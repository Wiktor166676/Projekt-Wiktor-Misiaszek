#include <bits/stdc++.h>
#include <iostream>
#include <string>

using namespace std;

// Gdy znaleziono najdlusza sume, metoda drukuje wynik
// Jesli nie znaleziono zadnego pasujacego ukladu liczb, metoda drukuje informacje o braku wyniku
void znajdz_najdluzszy_podciag(int tablica[], int dlugosc, int suma)
{
    // Zmienne pomocnicze
    int aktualna_suma, i, j;
    string najdluzsza = "";
    int najdluzsza_dlugosc = 0;
    string najdluzsza_tymczasowa = "";
    int najdluzsza_tymczasowa_dlugosc;

    for (i = 0; i < dlugosc; i++)
        {
        // Ustawiamy aktualny element jako aktualna suma
        // i dodajemy do kolekcji tymczasowej ktora przechowa nam aktualny zbior
        aktualna_suma = tablica[i];
        najdluzsza_tymczasowa = "";
        najdluzsza_tymczasowa = to_string(tablica[i])+najdluzsza_tymczasowa;
        najdluzsza_tymczasowa_dlugosc = 1;

        // Mamy jeden wybrany element z naszej tablicy
        // I przeszukujemy reszte tablicy do konca w poszukiwaniu najdluzszej sekwencji elementow
        // Pasujacych do sumy
        for (j = i + 1; j < dlugosc; j++) {
            // Jesli obie liczby to ten sam element, powinnismy wyjsc z petli
            if (i == j) break;
            // Jesli aktualna suma jest rowna oczekiwanej, znalezlismy wynik pasujacy do sumy
            if (aktualna_suma == suma)
            {

                // To znaczy ze nie powinnismy juz dalej przeszukiwac i musimy zakonczyc petle
                // Aby szukac kolejnych sekwencji liczb
                break;
            }
            // Jesli aktualna suma przekroczyla oczekiwana lub wyszlismy poza dlugosc tablicy, to przerywamy petle
            if (aktualna_suma > suma)
                break;
            // W przeciwnym razie dodajemy do aktualnej sumy aktualny element
            // I robimy kolejny obrot petli by znow sprawdzic aktualna sume
            aktualna_suma = aktualna_suma + tablica[j];
            najdluzsza_tymczasowa += ",";
            najdluzsza_tymczasowa += to_string(tablica[j]);
            najdluzsza_tymczasowa_dlugosc += 1;
        }
        // Podstawiamy tymczasowa tablice do naszej koncowej wynikowej, jesli jest dluzsza
        if (najdluzsza_tymczasowa_dlugosc > najdluzsza_dlugosc && aktualna_suma == suma)
            {
            najdluzsza_dlugosc = najdluzsza_tymczasowa_dlugosc;
            najdluzsza = najdluzsza_tymczasowa;
            }
    }

    // Jesli znalezlismy jakis zestaw liczb dla danej sumy to:
    if (najdluzsza_dlugosc > 0)
        {
        // Drukujemy wynik
        cout << "Najdluzszy podciag to [" << najdluzsza << "] o dlugosci " << najdluzsza_dlugosc;
        // Zapisujemy do pliku
        ofstream plik("wyniki.txt");
        plik << "Najdluzszy podciag to [" << najdluzsza << "] o dlugosci " << najdluzsza_dlugosc;
        plik.close();
    }
     else
    { // W przeciwnym razie drukujemy informacje o braku wyniku
        cout << "Nie znaleziono pasujacych liczb";
    }
}


int main()
{
    // Wczytujemy dane z pliku
    // Wczytujemy dane linia po linii
    // Dlatego mamy 2 elementy:
    // Pierwszy to pierwsza linijka z pliku czyli "A[] = [...]"
    // Drugi to druga linijka z pliku czyli "Suma = ..."
    // Wszystko jest stringiem w tym momencie
    string aktualna_linia;
    string linie[2];
    int index = 0;
    ifstream plik("dane.txt");
    if(plik.good()==false){cout<<"Plik dane.txt nie istnieje"<<endl;}
    while (getline(plik, aktualna_linia))
    {
        linie[index] = aktualna_linia;
        index++;
    }
    plik.close();

    // Bierzemy pierwsza linie i wyciagamy z niej sama tablice liczb aby miec ja w formacie "x,y,z"
    // Wywalamy zatem "A[] = " oraz nawiasy kwadratowe
    // Zostana nam jeszcze przecinki pomiedzy liczbami, ktore usuniemy pozniej
    string tablica_z_pliku = linie[0].substr(linie[0].find(" = ") + 4, linie[0].length() - 8);

    // Bierzemy druga linie i wyciagamy wartosc sumy
    // Wywalamy "Suma = "
    string suma_z_pliku = linie[1].substr(linie[1].find(" = ") + 3);

    // Wykonujemy parsowanie tablicy, czyli wywalamy wszystkie przecinki i to co zostanie zamieniamy na liczby
    vector<int> wektor;
    stringstream tablica_jako_array(tablica_z_pliku);
    for (int i; tablica_jako_array >> i;)
    {
        wektor.push_back(i);
        if (tablica_jako_array.peek() == ',')
        {
            tablica_jako_array.ignore();
        }
    }
    int tablica[wektor.size()];
    for (size_t i = 0; i < wektor.size(); i++)
    {
        tablica[i] = wektor[i];
    }

    // Ustalamy dlugosc tablicy (ile elementow)
    int dlugosc = wektor.size();

    // Parsujemy sume ze stringa na liczbe
    int suma;
    stringstream suma_jako_liczba(suma_z_pliku);
    suma_jako_liczba >> suma;

    // Mamy wszystko przygotowane, wiec wywolujemy funkcje szukajaca
    znajdz_najdluzszy_podciag(tablica, dlugosc, suma);


    return 0;
}
