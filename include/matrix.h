#pragma once
#include <memory>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <ostream>

using namespace std;

/// @class matrix
/// @brief Klasa reprezentujaca macierz liczb zmiennoprzecinkowych
/// Klasa zapewnia operacje macierzowe oraz zaawansowane funkcjonalnosci
/// do manipulacji danymi macierzy.
class matrix {
public:
    /// @brief Konstruktor domyslny
    /// Tworzy macierz z wartosciami domyslnymi
    matrix() noexcept;
    
    /// @brief Konstruktor parametryzowany
    /// @param rows Liczba wierszy macierzy
    /// @param cols Liczba kolumn macierzy
    /// @param value Wartosc inicjujaca wszystkie elementy (domyslnie 0.0)
    matrix(std::size_t rows, std::size_t cols, double value = 0.0);
    
    /// @brief Konstruktor z listy inicjalizacyjnej
    /// @param init Lista zagniezdzona zawierajaca wartosci macierzy
    matrix(std::initializer_list<std::initializer_list<double>> init);

    /// @brief Konstruktor kopiujacy
    /// @param other Macierz do skopiowania
    matrix(const matrix& other);
    
    /// @brief Operator przypisania (kopiowanie)
    /// @param other Macierz do skopiowania
    /// @return Referencja na biezaca macierz
    matrix& operator=(const matrix& other);
    
    /// @brief Konstruktor przenoszacy
    matrix(matrix&&) noexcept = default;
    
    /// @brief Operator przypisania (przenoszenie)
    matrix& operator=(matrix&&) noexcept = default;
    
    /// @brief Destruktor
    ~matrix() = default;

    /// @brief Zwraca liczbe wierszy
    /// @return Liczba wierszy macierzy
    std::size_t get_rows() const noexcept { return rows; }
    
    /// @brief Zwraca liczbe kolumn
    /// @return Liczba kolumn macierzy
    std::size_t get_cols() const noexcept { return cols; }
    
    /// @brief Zwraca rozmiar macierzy
    /// @return Calkowita liczba elementow (wiersze * kolumny)
    std::size_t size() const noexcept { return rows * cols; }

    /// @brief Alokuje pamiec dla macierzy
    /// @param n Liczba elementow do alokacji
    void alokuj(std::size_t n);

    /// @brief Dostep do elementu macierzy (do zapisu)
    /// @param r Indeks wiersza
    /// @param c Indeks kolumny
    /// @return Referencja na element macierzy
    double& operator()(std::size_t r, std::size_t c);
    
    /// @brief Dostep do elementu macierzy (do odczytu)
    /// @param r Indeks wiersza
    /// @param c Indeks kolumny
    /// @return Wartosc elementu macierzy
    double operator()(std::size_t r, std::size_t c) const;

    /// @brief Dodawanie dwoch macierzy
    /// @param m Macierz do dodania
    /// @return Referencja na wynik (macierz zmieniona)
    matrix& operator+(matrix& m);
    
    /// @brief Mnozenie dwoch macierzy
    /// @param m Macierz do pomnozenia
    /// @return Referencja na wynik (macierz zmieniona)
    matrix& operator*(matrix& m);
    
    /// @brief Dodawanie skalara do macierzy
    /// @param a Wartosc skalara
    /// @return Referencja na wynik (macierz zmieniona)
    matrix& operator+(int a);
    
    /// @brief Mnozenie macierzy przez skalar
    /// @param a Wartosc skalara
    /// @return Referencja na wynik (macierz zmieniona)
    matrix& operator*(int a);
    
    /// @brief Odejmowanie skalara od macierzy
    /// @param a Wartosc skalara
    /// @return Referencja na wynik (macierz zmieniona)
    matrix& operator-(int a);

    /// @brief Dodawanie skalara do macierzy (skalar z lewej)
    /// @param a Wartosc skalara
    /// @param m Macierz
    /// @return Wynik operacji
    friend matrix operator+(int a, matrix& m);
    
    /// @brief Mnozenie macierzy przez skalar (skalar z lewej)
    /// @param a Wartosc skalara
    /// @param m Macierz
    /// @return Wynik operacji
    friend matrix operator*(int a, matrix& m);
    
    /// @brief Odejmowanie macierzy od skalara
    /// @param a Wartosc skalara
    /// @param m Macierz
    /// @return Wynik operacji
    friend matrix operator-(int a, matrix& m);

    /// @brief Inkrementacja wszystkich elementow (operator postfixowy)
    /// @return Referencja na macierz przed zmiana
    matrix& operator++(int);
    
    /// @brief Dekrementacja wszystkich elementow (operator postfixowy)
    /// @return Referencja na macierz przed zmiana
    matrix& operator--(int);

    /// @brief Dodaj skalar do wszystkich elementow
    /// @param a Wartosc skalara do dodania
    /// @return Referencja na zmieniona macierz
    matrix& operator+=(int a);
    
    /// @brief Odejmij skalar od wszystkich elementow
    /// @param a Wartosc skalara do odjecia
    /// @return Referencja na zmieniona macierz
    matrix& operator-=(int a);
    
    /// @brief Pomnozy wszystkie elementy przez skalar
    /// @param a Wartosc skalara do mnozenia
    /// @return Referencja na zmieniona macierz
    matrix& operator*=(int a);

    /// @brief Ustaw wszystkie elementy na dana wartosc
    /// @param value Wartosc do ustawienia
    /// @return Referencja na zmieniona macierz
    matrix& operator()(double value);

    /// @brief Wypisz macierz na strumien wyjsciowy
    /// @param o Strumien wyjsciowy
    /// @param m Macierz do wypisania
    /// @return Strumien wyjsciowy
    friend ostream& operator<<(ostream& o, matrix& m);

    /// @brief Sprawdz czy dwie macierze sa rowne
    /// @param m Macierz do porownania
    /// @return Prawda jesli macierze sa rowne
    bool operator==(const matrix& m);
    
    /// @brief Sprawdz czy macierz jest wieksza niz druga
    /// @param m Macierz do porownania
    /// @return Prawda jesli warunek jest spelniony
    bool operator>(const matrix& m);
    
    /// @brief Sprawdz czy macierz jest mniejsza niz druga
    /// @param m Macierz do porownania
    /// @return Prawda jesli warunek jest spelniony
    bool operator<(const matrix& m);

    /// @brief Wstaw wartosc w okreslone miejsce
    /// @param x Indeks wiersza
    /// @param y Indeks kolumny
    /// @param wartosc Wartosc do wstawienia
    /// @return Referencja na zmieniona macierz
    matrix& wstaw(int x, int y, int wartosc);
    
    /// @brief Pokaz wartosc z danego miejsca
    /// @param x Indeks wiersza
    /// @param y Indeks kolumny
    /// @return Wartosc z okreslonych wspolrzednych
    int pokaz(int x, int y);
    
    /// @brief Odwroc macierz (transponuj)
    /// @return Referencja na zmieniona macierz
    matrix& dowroc();
    
    /// @brief Wypelnij macierz losowymi wartosciami
    /// @return Referencja na zmieniona macierz
    matrix& losuj();
    
    /// @brief Wypelnij macierz losowymi wartosciami z zakresu
    /// @param x Maksymalna wartosc losowa
    /// @return Referencja na zmieniona macierz
    matrix& losuj(int x);
    
    /// @brief Utworz macierz diagonalna z tablicy
    /// @param t Tablica zawierajaca wartosci diagonalne
    /// @return Referencja na zmieniona macierz
    matrix& diagonalna(int* t);
    
    /// @brief Utworz macierz z diagonala przesunietej
    /// @param k Przesunicie diagonali (dodatnie - nad glowna, ujemne - pod glowna)
    /// @param t Tablica zawierajaca wartosci diagonalne
    /// @return Referencja na zmieniona macierz
    matrix& diagonalna_k(int k, int* t);
    
    /// @brief Wstaw wartosci tablicy w kolumne macierzy
    /// @param x Numer kolumny
    /// @param t Tablica wartosci
    /// @return Referencja na zmieniona macierz
    matrix& kolumna(int x, int* t);
    
    /// @brief Wstaw wartosci tablicy w wiersz macierzy
    /// @param y Numer wiersza
    /// @param t Tablica wartosci
    /// @return Referencja na zmieniona macierz
    matrix& wiersz(int y, int* t);
    
    /// @brief Wypelnij macierz glowna diagonala
    /// @return Referencja na zmieniona macierz
    matrix& przekatna();
    
    /// @brief Wypelnij czesc pod glowna diagonala
    /// @return Referencja na zmieniona macierz
    matrix& pod_przekatna();
    
    /// @brief Wypelnij czesc nad glowna diagonala
    /// @return Referencja na zmieniona macierz
    matrix& nad_przekatna();
    
    /// @brief Wypelnij macierz w wzor szachownicy
    /// @return Referencja na zmieniona macierz
    matrix& szachownica();

    /// @brief Liczba wierszy macierzy
    int rows;
    
    /// @brief Liczba kolumn macierzy
    int cols;
    
    /// @brief Wskaznik na dane macierzy (tablica wskaz­ni­kow do wierszy)
    std::unique_ptr<double*[]> data;

private:
};