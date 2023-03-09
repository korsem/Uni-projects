
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
