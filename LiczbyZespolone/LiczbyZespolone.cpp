#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

class dev_by0 : public std::exception{
public:
    dev_by0() : std::exception(){
    }
    const char * what() const noexcept override
    {
        return "Nie dziel przez 0";
    }
};

class LiczbaZespolona
{
public:
    float rzeczywista;
    float urojona;

    //konstruktor bezargumentowy
    LiczbaZespolona()
    {
        rzeczywista = 0;
        urojona = 0;
    }

    //konstruktor jednoargumentowy
    LiczbaZespolona(float rzeczywista)
    {
        this->rzeczywista = rzeczywista;
        urojona = 0;
    }

    //kontruktor dwuargumentowy
    LiczbaZespolona(float rzeczywista, float urojona)
    {
        this->rzeczywista = rzeczywista;
        this->urojona = urojona;
    }

    //kontruktor kopiujacy
    LiczbaZespolona(const LiczbaZespolona &oryginal)
    {
        this -> rzeczywista = oryginal.rzeczywista;
        this -> urojona = oryginal.urojona;
    }

    //metoda obliczajaca sprzezenie liczby zespolonej
    LiczbaZespolona Sprzezenie()
    {
        LiczbaZespolona s = LiczbaZespolona(rzeczywista, (-1)*urojona);
        return s;
    }

    //metoda obliczajaca modul liczby zespolonej
    float Modul()
    {
        float m = rzeczywista*rzeczywista + urojona*urojona;
        return sqrt(m);
    }

    //operator [], liczba[0] zwroci rzeczywiste, a liczba[1] urojone
    float operator[](int n)
    {
        if(n == 0)
            return rzeczywista;
        else if(n == 1)
            return urojona;
        else
            return 0;
    }
};

//operatory + i - jednoargumentowe
LiczbaZespolona operator-(LiczbaZespolona &l)
{
    return LiczbaZespolona((-1)*l.rzeczywista, (-1)*l.urojona);
}

LiczbaZespolona operator+(LiczbaZespolona &l)
{
    return LiczbaZespolona(l.rzeczywista, l.urojona);
}

//operatory + i - dwuargumentowe
LiczbaZespolona operator-(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    return LiczbaZespolona(l1.rzeczywista-l2.rzeczywista, l1.urojona-l2.urojona);
}

LiczbaZespolona operator+(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    return LiczbaZespolona(l1.rzeczywista+l2.rzeczywista, l1.urojona+l2.urojona);
}

//operatory * i /
LiczbaZespolona operator*(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    float r = 0, u = 0;
    r = l1.rzeczywista * l2.rzeczywista - l1.urojona * l2.urojona;
    u = l1.rzeczywista * l2.urojona + l2.rzeczywista * l1.urojona;

    return LiczbaZespolona(r, u);
}

LiczbaZespolona operator/(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    if(l2.rzeczywista == 0 && l2.urojona == 0)
        throw dev_by0();
    else if(l2.urojona == 0)
    {
        return LiczbaZespolona(l1.rzeczywista/l2.rzeczywista, l1.urojona/l2.rzeczywista);
    }
    else
    {
        LiczbaZespolona s = l2.Sprzezenie();
        LiczbaZespolona l = l1 * s;  //l - licznik
        LiczbaZespolona m = l2 * s;  //m - mianownik
        float b = m.rzeczywista;
        if(b == 0)
            throw dev_by0();
        else
            return LiczbaZespolona(l.rzeczywista/b, l.urojona/b);
    }
}

//operatory >, >=, <, <=
//porownuje po czesci rzeczywistej liczby, jesli czesci rzecztwiste sa sobie rowne, to porownuje po czesci urojonej
bool operator>(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    if(l1.rzeczywista > l2.rzeczywista)
        return true;
    else if(l1.rzeczywista == l2.rzeczywista)
    {
        if(l1.urojona > l2.urojona)
            return true;
    }
    return false;
}

bool operator>=(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    if(l1.rzeczywista > l2.rzeczywista)
        return true;
    else if(l1.rzeczywista == l2.rzeczywista)
    {
        if(l1.urojona >= l2.urojona)
            return true;
    }
    return false;
}

bool operator<(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    if(l1.rzeczywista < l2.rzeczywista)
        return true;
    else if(l1.rzeczywista == l2.rzeczywista)
    {
        if(l1.urojona < l2.urojona)
            return true;
    }
    return false;
}

bool operator<=(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    if(l1.rzeczywista < l2.rzeczywista)
        return true;
    else if(l1.rzeczywista == l2.rzeczywista)
    {
        if(l1.urojona >= l2.urojona)
            return true;
    }
    return false;
}

// operatory ==, !=
bool operator==(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    if(l1.rzeczywista == l2.rzeczywista && l1.urojona == l2.urojona)
        return true;
    return false;
}

bool operator!=(LiczbaZespolona &l1, LiczbaZespolona &l2)
{
    if(l1.rzeczywista != l2.rzeczywista || l1.urojona != l2.urojona)
        return true;
    return false;
}

//+, -, *, / dla zapisu zespolona X float i float X zespolona
LiczbaZespolona operator+(LiczbaZespolona &l, float x)
{
    return LiczbaZespolona(x+l.rzeczywista, 0+l.urojona);
}

LiczbaZespolona operator+(float x, LiczbaZespolona &l)
{
    return LiczbaZespolona(x+l.rzeczywista, 0+l.urojona);
}

LiczbaZespolona operator-(LiczbaZespolona &l, float x)
{
    return LiczbaZespolona(l.rzeczywista - x, l.urojona);
}

LiczbaZespolona operator-(float x, LiczbaZespolona &l)
{
    return LiczbaZespolona(x-l.rzeczywista, 0-l.urojona);
}

LiczbaZespolona operator*(LiczbaZespolona &l, float x)
{
    return LiczbaZespolona(x*l.rzeczywista, x*l.urojona);
}

LiczbaZespolona operator*(float x, LiczbaZespolona &l)
{
    return LiczbaZespolona(x*l.rzeczywista, 0*l.urojona);
}
LiczbaZespolona operator/(float x, LiczbaZespolona &l)
{
    return LiczbaZespolona(x/l.rzeczywista, 0);
}

LiczbaZespolona operator/(LiczbaZespolona &l, float x)
{
    if(x == 0)
        throw dev_by0();
    return LiczbaZespolona(l.rzeczywista/x, l.urojona/x);
}

// przeciazony operator << dla std::cout wyswietla zaokraglana liczbe zespolona do 3 cyfr po przecinku
std::ostream& operator<<(std::ostream &stream, LiczbaZespolona &l)
{
    stream << setprecision(3) << l.rzeczywista << "+" << l.urojona << "i";
    return stream;
}

//metoda zwraca liczbe zespolona o module 1 (liczba zespolona jest traktowana jako wektor [a, b]
LiczbaZespolona Normalizacja(LiczbaZespolona l)
{
    if(l.Modul() > 0)
    {
        float M = l.Modul();
        l.rzeczywista = l.rzeczywista / M;
        l.urojona = l.urojona / M;
    }
    return LiczbaZespolona(l.rzeczywista, l.urojona);
}

int main()
{
    cout << "Oto kalkulator liczb zespolonych" << endl;
    cout << "Liczby sa przedstawione w postaci 'a + bi'" << endl;
    cout << "podaj wartosci a i b kolejno dla pierwszej liczby i dla drugiej, aby wyswietlic obliczenia na tych liczbach" << endl;
    int a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;

    //uzycie kontruktorow dwuargumntowych
    LiczbaZespolona l1 = LiczbaZespolona(a1, b1);
    LiczbaZespolona l2 = LiczbaZespolona(a2, b2);

    LiczbaZespolona wynik;

    //wyniki obliczen
    wynik = l1 + l2;
    cout << l1 << " + " << l2 << " = " << wynik << endl;
    wynik = l1 - l2;
    cout << l1 << " - " << l2 << " = " << wynik << endl;
    wynik = l1 * l2;
    cout << l1 << " * " << l2 << " = " << wynik << endl;
    wynik = l1 / l2;
    cout << l1 << " / " << l2 << " = " << wynik << endl;

    cout << endl;

    //porownanie dwoch liczb
    if(l1 == l2)
        cout << "Liczby te sa rowne" << endl;
    if(l1 > l2)
        cout << l1 << " jest wieksze od " << l2 << endl;
    else
        cout << l2 << "jest wieksze od " << l1 << endl;

    cout << endl;

    wynik = Normalizacja(l1);
    //normalizacja
    cout << l1 << " po normalizacji: " << wynik << endl;

    //liczby rzeczywiste
    cout << "liczba rzeczywista w "  << l1 << " to " << l1[0] << endl;
}
