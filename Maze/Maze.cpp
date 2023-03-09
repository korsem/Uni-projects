/*Wêze³ raz odwiedzony nie powinien byæ ca³kowicie ignorowany w obliczeniach.
Mo¿e istnieæ wiêcej œcie¿ek do danego punktu na mapie, a krótsza œcie¿ka niekoniecznie zostanie wybrana jako pierwsza.
*/

/*

# The maze

The maze programs returns the minimal cost of moves needed to be done to go through the maze from the start to the target postion.
The only moves allowed are vertical and horizontal. A move means changing position by one from the current place to the left, right, up or down.
Entry cost to the each position has a cost of one or two. Entering the initial position and the target position have the cost of 1.
There are also regular positions with the cost of 1 and the "hard terrain" positions with the cost of entry of 2.
There are also inaccessible positions forming the maze.
The maze is presented:

0 - initial position [entry cost is 1]
1 - target position[entry cost is 1]
'_' - regular position [input cost is 1].
. - "difficult terrain" position [entry cost is 2] .
X - field not available

The journey starts with cost = 0, from field '0' (entering this field costs 1).
Fields '0' and '1' always appear in one copy on the map.
Moving outside the map is not allowed.

# Not finished
*/


#include <iostream>
#include <algorithm>
#include <queue>
#define INT_MAX 2147483647

using namespace std;

//struktura Pole przechowuje wspolrzedne pola mapy
struct Pole {
    int a;
    int b;

    Pole()
    {
        a = -1;
        b = -1;
    }
    Pole(int a, int b)
    {
        this->a = a;
        this->b = b;
    }
    bool istnieje()
    {
        if (a != -1 && b != -1)
            return true;
        else
            return false;
    }
};

//przeciazenie operatora == sluzy do porownania dwoch pol
bool operator==(Pole &p1, Pole &p2)
{
    if (p1.a == p2.a && p1.b == p2.b)
    {
        return true;
    }
    else
        return false;
}

//funkcja ta sluzy do wypisania nowych wartosci wokol Pola ostatnie do tablicy odl
//uzupelnia wartosci talicy wokol Pola na ktorym aktualnie pracuje - ostatnie
void fillOkolice(int **odl, int **wagi, bool **vis, int w, int h, Pole ostatnie)
{
    vis[ostatnie.a][ostatnie.b] = true;

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    for(int i = 0; i < 4; i++)
    {
        int x = ostatnie.a + dx[i];
        int y = ostatnie.b + dy[i];

        if(x >= 0 && x < h && y >= 0 && y < w &&  wagi[x][y] != 3)//sprawdzanie, czy nowe współrzędne są w granicach tablicy i czy pole nie jest przeszkodą
        {

            if(!vis[x][y]) //jeśli pole nie zostało odwiedzone, ustawiam odległość jako sumę odległości do ostatniego pola i wagi pola
            {
                vis[x][y] = true;
                odl[x][y] = odl[ostatnie.a][ostatnie.b] + wagi[x][y];
            }
            else //jeśli pole zostało odwiedzone, ustawiam wartość na krótszą możliwą odległość
                odl[x][y] = min(odl[x][y], odl[ostatnie.a][ostatnie.b] + wagi[x][y]);

        }
    }
}

//funkcja dodaje do kolejki kolejne pola, na ktorych nastepnie bede wywolywac funkcje fillOkolice
//wynikiem dzialania tej funkcji jest uzupelniona tablica odl
//jest to funkcja rekurencyjna
void bfs(int **odl, int **wagi, bool **visited, bool **vis, int w, int h, Pole ostatnie, Pole stop, queue<Pole> q)
{
    q.push(ostatnie); //do kolejki dodaje Pole startowe
    visited[ostatnie.a][ostatnie.b] = true; //Zaznaczam je jako odwiedzone
    fillOkolice(odl, wagi, vis, w, h, ostatnie);

        Pole nowe = ostatnie; //zmienna pomocnicza przechowujaca pole na ktorym aktualnie pracuje
        if(ostatnie.a < h-1)
        {
            if(!visited[ostatnie.a+1][ostatnie.b])
            {
                visited[ostatnie.a + 1][ostatnie.b] = true;
                q.push(Pole(ostatnie.a + 1, ostatnie.b));
                nowe = Pole(ostatnie.a + 1,ostatnie.b);
                bfs(odl, wagi, visited, vis, w, h, nowe, stop, q);
            }
        }
        if(ostatnie.b < w-1)
        {
            if(!visited[ostatnie.a][ostatnie.b+1])
            {
                visited[ostatnie.a][ostatnie.b + 1] = true;
                q.push(Pole(ostatnie.a, ostatnie.b + 1));
                nowe = Pole(ostatnie.a, ostatnie.b + 1);
                bfs(odl, wagi, visited, vis, w, h, nowe, stop, q);
            }
        }
        if(ostatnie.a > 0)
        {
            if(!visited[ostatnie.a - 1][ostatnie.b])
            {
                visited[ostatnie.a - 1][ostatnie.b] = true;
                q.push(Pole(ostatnie.a - 1, ostatnie.b));
                nowe = Pole(ostatnie.a - 1,ostatnie.b);
                bfs(odl, wagi, visited, vis, w, h, nowe, stop, q);
            }
        }
        if(ostatnie.b > 0)
        {
            if(!visited[ostatnie.a][ostatnie.b - 1])
            {
                visited[ostatnie.a][ostatnie.b - 1] = true;
                q.push(Pole(ostatnie.a, ostatnie.b - 1));
                nowe = Pole(ostatnie.a, ostatnie.b - 1);
                bfs(odl, wagi, visited, vis, w, h, nowe, stop, q);
            }
        }
        ostatnie = nowe;

        //wedlug ustalonej przez kolejke kolejnosci uzupelniam tablice odl
        if(ostatnie == stop)
        {
           while (!q.empty())
            {
                Pole a = q.front();
                fillOkolice(odl, wagi, vis, w, h, a);
                q.pop();
            }
        }
    }

int main()
{
    int w, h; //szerokosc i wysokosc mapy
    cin >> w >> h;
    char c; //znak
    char mapa[h][w];
    Pole start; //zmienna przechowuje wspolrzedna Pola startowego
    Pole stop; //zmienna przechowuje wspolrzedna Pola koncowego
    int x = 0;
    //uzupelniam mape znakami
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            cin >> c;
            mapa[i][j] = c;
            if(c == '0')
            {
                start = Pole(i, j);
                x++;
            }
            else if(c == '1')
            {
                stop = Pole(i, j);
                x++;
            }
        }
    }

    //moga byc tylko 2 znaki 0 lub 1 na mapie
    if(x != 2)
    {
        cout << -1;
    }
    //jesli nie istnieje pole startowe lub koncowe zwracam -1
    else if(!start.istnieje() || !stop.istnieje())
    {
        cout << -1;
    }
    else
    {
        //tablica przechowuje wagi znakow z mapy
        int **wagi = new int*[h];
        for (int i = 0; i < h; i++)
        {
            wagi[i] = new int[w];
        }
         for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                if(mapa[i][j] == '.')
                    wagi[i][j] = 2;
                else if(mapa[i][j] == 'X')
                    wagi[i][j] = 3; //wartosc 3 oznacza X, czyli Pole na ktore nie mozna wchodzic
                else
                    wagi[i][j] = 1;
            }
        }

        //tablica odl przechowuje najkrotsze odleglosci do konkretnego pola
        int **odl = new int*[h];
        for (int i = 0; i < h; i++)
        {
            odl[i] = new int[w];
        }
            for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                odl[i][j] = INT_MAX; //ustawiam wartosci odleglosci poczatkowa na INT_MAX jak nieskonczonosc jak w algorytmie dikstry
            }
        }
        odl[start.a][start.b] = 1; //ustawiam wartosc (start zawsze bedzie mial wartosc 1)

        //tablice przechowuje informacje ktore pola zostaly odwiedzone
        bool** visited = new bool*[h]; //wykorzystuje do bfs
        bool** vis = new bool*[h]; //wykorzystuje do fillOkolice
        for(int i = 0; i < h; i++)
        {
            visited[i] = new bool[w];
            vis[i] = new bool[w];
        }
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                if(wagi[i][j] == 3)
                    {
                        visited[i][j] = true; //ustawiam wartosci z X na odwiedzone
                        vis[i][j] = true;
                    }
                else
                    {
                        visited[i][j] = false;
                        vis[i][j] = false;
                    }
            }
        }

        //kolejka q bedzie przechowywac kolejnosc pol ktore bede "przeszukiwac"
        queue<Pole> q;

        //wywoluje bfs
        //ustawi mi najkrotsze drogi do poszczegolnych Pol mapy, ktore wykorzystuje do okreslenia odleglosci do Pola stop
        bfs(odl, wagi, visited, vis, w, h, start, stop, q);

        //wyswietlam wynik
        if(odl[stop.a][stop.b] == INT_MAX) //jesli nie ma drogi do stopu, wyswietlam -1
            cout << -1;
        else
            cout << odl[stop.a][stop.b]; //wyswietlam odleglosc do stopu

        //zwalniam pamiec moich tablic
        for (int i = 0; i < h; i++)
        {
            delete [] odl[i];
            delete [] wagi[i];
            delete [] visited[i];
            delete [] vis[i];
        }
        delete [] odl;
        delete [] wagi;
        delete [] visited;
        delete [] vis;
        }
return 0;
}
