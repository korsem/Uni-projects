#include <iostream>
#include <algorithm>
#include <queue>
#define INT_MAX 2147483647

using namespace std;

//structure Position stores the coordinates of the maze
struct Position {
    int a;
    int b;

    Position()
    {
        a = -1;
        b = -1;
    }
    Position(int a, int b)
    {
        this->a = a;
        this->b = b;
    }
    bool exist()
    {
        if (a != -1 && b != -1)
            return true;
        else
            return false;
    }
};

//== compares two positions
bool operator==(Position &p1, Position &p2)
{
    if (p1.a == p2.a && p1.b == p2.b)
    {
        return true;
    }
    else
        return false;
}

//this function is used to write new values around the field prev into the table dist
//complete the values of the thallium around the field it is currently working on - prev
void fillNeighbours(int **dist, int **weight, bool **vis, int w, int h, Position prev)
{
    vis[prev.a][prev.b] = true;

    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

    for(int i = 0; i < 4; i++)
    {
        int x = prev.a + dx[i];
        int y = prev.b + dy[i];

        if(x >= 0 && x < h && y >= 0 && y < w &&  weight[x][y] != 3)//checking that the new coordinates are within the limits of the array and that Position is not an obstacle
        {

            if(!vis[x][y]) //if Position was not visited, I set the distance as a sum of the distance to the previous position and the value of the current position
            {
                vis[x][y] = true;
                dist[x][y] = dist[prev.a][prev.b] + weight[x][y];
            }
            else //if the position has been already visited I set the value of the dist to a shorter possible value
                dist[x][y] = min(dist[x][y], dist[prev.a][prev.b] + weight[x][y]);

        }
    }
}

//the function adds further fields to the queue, on which I will then call the fillNeighbours function
//the result of this function is a filled dist array
//it is a recursive function
void bfs(int **dist, int **weight, bool **visited, bool **vis, int w, int h, Position prev, Position stop, queue<Position> q)
{
    q.push(prev); //start Position is added to a queue
    visited[prev.a][prev.b] = true; //and is marked as visited
    fillNeighbours(dist, weight, vis, w, h, prev);

        Position current = prev; //auxiliary variable storing the currently used Position
        if(prev.a < h-1)
        {
            if(!visited[prev.a+1][prev.b])
            {
                visited[prev.a + 1][prev.b] = true;
                q.push(Position(prev.a + 1, prev.b));
                current = Position(prev.a + 1,prev.b);
                bfs(dist, weight, visited, vis, w, h, current, stop, q);
            }
        }
        if(prev.b < w-1)
        {
            if(!visited[prev.a][prev.b+1])
            {
                visited[prev.a][prev.b + 1] = true;
                q.push(Position(prev.a, prev.b + 1));
                current = Position(prev.a, prev.b + 1);
                bfs(dist, weight, visited, vis, w, h, current, stop, q);
            }
        }
        if(prev.a > 0)
        {
            if(!visited[prev.a - 1][prev.b])
            {
                visited[prev.a - 1][prev.b] = true;
                q.push(Position(prev.a - 1, prev.b));
                current = Position(prev.a - 1,prev.b);
                bfs(dist, weight, visited, vis, w, h, current, stop, q);
            }
        }
        if(prev.b > 0)
        {
            if(!visited[prev.a][prev.b - 1])
            {
                visited[prev.a][prev.b - 1] = true;
                q.push(Position(prev.a, prev.b - 1));
                current = Position(prev.a, prev.b - 1);
                bfs(dist, weight, visited, vis, w, h, current, stop, q);
            }
        }
        prev = current;

        //according to the order established by a queue the dist array is filled up
        if(prev == stop)
        {
           while (!q.empty())
            {
                Position a = q.front();
                fillNeighbours(dist, weight, vis, w, h, a);
                q.pop();
            }
        }
    }

int main()
{
    int w, h; //width and height of the maze
    cout << "Input size of the maze: first width then height" << endl;
    cin >> w >> h;
    char maze[h][w]; //maze stores the chars meaning what kind of the terrain is certain position in the maze
    Position start; //stores subordinates of the start position
    Position stop; //stores subordinates of the target position
    char c; //char representing the kind of terrain {'X', '_', '.', '0', '1'}
    int x = 0; //stores the number of start positions and target positions (it should be 2)

    cout << "Now you will fill the maze of size " << w << "x" << h << " with characters:" << endl;
    cout << "'X' - inaccessible position," << endl;
    cout << " '_' - regular terrain (value of 1)," << endl;
    cout << "'.' - hard terrain (value of 2), " << endl;
    cout << "'0' - start position (value of 1), " << endl;
    cout << "'1' - target position (value of 1)" << endl;

    //filling the maze
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            cin >> c;
            maze[i][j] = c;
            if(c == '0')
            {
                start = Position(i, j);
                x++;
            }
            else if(c == '1')
            {
                stop = Position(i, j);
                x++;
            }
        }
    }

    //there needs t be exactly one start position and one target position on the maze
    if((x != 2) && (!start.exist() || !stop.exist()))
    {
        cout << "there should be one start position and one target position in the maze" << endl;
        return 1;
    }

    else
    {
        //array stores th values of the positions in the maze
        int **weight = new int*[h];
        for (int i = 0; i < h; i++)
        {
            weight[i] = new int[w];
        }
         for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                if(maze[i][j] == '.')
                    weight[i][j] = 2;
                else if(maze[i][j] == 'X')
                    weight[i][j] = 3; //value of 3 means the position is not accessible
                else
                    weight[i][j] = 1;
            }
        }

        //dist array stores the shortest distances to the certain position
        int **dist = new int*[h];
        for (int i = 0; i < h; i++)
        {
            dist[i] = new int[w];
        }
            for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                dist[i][j] = INT_MAX; //I set the starting values of dist array to INT_MAX
            }
        }
        dist[start.a][start.b] = 1; //I set the value of starting position (the value of it is always 1)

        //these arrays stores the information if the each position was yet visited
        bool** visited = new bool*[h]; //used for bfs
        bool** vis = new bool*[h]; //used for fillNeighbours
        for(int i = 0; i < h; i++)
        {
            visited[i] = new bool[w];
            vis[i] = new bool[w];
        }
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                if(weight[i][j] == 3)
                    {
                        visited[i][j] = true; //I set the value of inaccessible position to visited
                        vis[i][j] = true;
                    }
                else
                    {
                        visited[i][j] = false;
                        vis[i][j] = false;
                    }
            }
        }

        //the q queue will store the order of the fields to be "searched"
        queue<Position> q;

        //bfs function will set the values of the shortest distances to the each positions of the maze that I use to set the value from the start position to the stop position
        bfs(dist, weight, visited, vis, w, h, start, stop, q);

        //result
        if(dist[stop.a][stop.b] == INT_MAX)
            cout << "No path from the start position to the target position" << endl;
        else
            cout << dist[stop.a][stop.b];

        //free the memory
        for (int i = 0; i < h; i++)
        {
            delete [] dist[i];
            delete [] weight[i];
            delete [] visited[i];
            delete [] vis[i];
        }
        delete [] dist;
        delete [] weight;
        delete [] visited;
        delete [] vis;
        }
return 0;
}
