
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

To find the shortest distance from the start position to the target position I use two functions: fillNeighbours() and bfs()

fillNeighbours() updates the shortes path to the neighbouring positions of the position I am currently working on/
bfs() uses Breadth-first Search to call the fillNeighbour() function in a certain order. I am calling fillNeighbour() function while searching the Maze and then using a queue which calles this function once again. That is why I need to modify this function somehow.

# To be done
1) A node once visited should not be completely ignored in the calculation.
There may be more than one path to a given point on the map, and the shorter path will not necessarily be selected first
2) Find the case the input the program doesn't work
3) The bfs function can be optimized
4) It can be simplified to the Dijkstra algorithm
5) Do i need 2 arrays to store the information if each position was visited?
6) Wouldn't it be simplier in a class? (Not so many argumnts in my functions)
7) Think about it 
