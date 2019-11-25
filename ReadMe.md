#Quantum-Minesweeper

###Overview
It is a game, where you need to open all cells of the field and do not blow on the mine. But mines change their position with some period. 

![](https://github.com/albashuk/Quantum-Minesweeper/blob/master/1.jpg)

###General structure
The game takes the size of field and length of the period between changes like input information. Then, at the beginning and in the future changes, it repeatedly changes field by set_bombs(). At the same time, a player can open a cell. If there is a mine, the game ended. If it is an empty cell, then open some block with this cell inside by dfs() and reset the field view by change_textures(). If all cells are opened, the player wins, and the game is ended.

###Main functions
- change_textures() – change the view of the field dependence on opened cells and mines positions;
- set_bombs() – reset whole undiscovered part of the field by placing mines in random unopened cells. The new number of mines linearly depended on the size of the undiscovered part;
- dfs() – DFS algorithm on the cells of the field where you with probability 1/2 can step in each of four possible directions. It helps to open absolutely different blocks of cells. 

###Future improvements
Make that some opened cells become undiscovered with time and speed of undiscovering is growing with time. It has to makes the game more interesting.
