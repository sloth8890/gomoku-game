# Gomoku In The Mist
## Introduction
The following codebase is implementation for 2023 COMP2017 Assignemnt 1. This assignment required students to implement extend version of gomoku game with extra features. 

## Rules of the Game
For those who do not know the rule for normal Gomoku click the following [Link](https://en.wikipedia.org/wiki/Gomoku).

Gomoku in the Mist is a new game based on Gomoku. It inherits all the rules from Gomoku and it introduces a game component called Mist. Mist blocks the visibility of both players and it covers the whole board except a 7 × 7 square hole (See Figure below). Players can only see through the hole that is not covered by the Mist, however, the placement of stone is not blocked by the Mist at all. If the centre of the hole is so close to the border of the board that the hole cannot fit into the board, simply ignore the part that cannot fit.

Initially, the hole of the Mist locates at the centre of the board before the first move. The Mist (hole) changes after every placement of a stone. The position of hole depends on the previous placement of a stone. If a numerical coordinate system is used, the following rules apply:

$x_{mist} = 1 + (5x^2_{stone} + 3x_{stone} + 4) \% 19$

$ y_{mist} = 1 + (4y^2_{stone} + 2y_{stone} − 4) \% 19$

% is the modulo operator.

$(x_{mist}, y_{mist})$ denotes the position of the **hole**'s centre and $(x_{stone}, y_{stone})$ denotes the position of the previous placed stone. 


To denote position on the board, a coordinate \<C>\<R> can be specified. While it is natural to utilise a 19 × 19 purely numerical coordinate system, the Go style system is preferred. In particular, for a Go coordinate \<C>\<R>, \<C> is a column character ranging from A (the first English upper letter) to S (the nineteenth English upper letter); \<R> is a row number ranging from 1 to 19.

In a numerical coordinate system, columns are denoted by numbers instead of characters. In particu- lar, the n-th English upper letter is equivalent to a number n. E.g. Column character A is equivalent to column number 1. See the numerical numbering in Figure drawn below.

```
19 @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
18 @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
17 @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
16 @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
15 @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
14 @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
13 @ @ @ @ @ @ . . . . . . . @ @ @ @ @ @ 
12 @ @ @ @ @ @ . . . . . . . @ @ @ @ @ @ 
11 @ @ @ @ @ @ . . . . . . . @ @ @ @ @ @ 
10 @ @ @ @ @ @ . . . A . . . @ @ @ @ @ @ 
9  @ @ @ @ @ @ . . . . . . . @ @ @ @ @ @  
8  @ @ @ @ @ @ . . . . . . . @ @ @ @ @ @  
7  @ @ @ @ @ @ . . . . . . . @ @ @ @ @ @  
6  @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @  
5  @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @  
4  @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @  
3  @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @  
2  @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @  
1  @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
   A B C D E F G H I J K L M N O P Q R S 
```

## End game condition


A winner is decided when that player achieves a line of five stones with the same colour, either horizontally, vertically or diagonally, or the opposing player has `resign`ed the game. A message will be displayed

`[Black|White] wins!`

The game will also end when no more stones can be placed A message will be displayed

`Wow, a tie!`

At the end of the game, the `history` command should be called silently to display all the moves. Finally, an exit message will be provided

`Thank you for playing!`

The controller will terminate with exit code 0 if a player wins or there is a tie. `term` command will not lead to the end game.

## Commands

- who

`who` commands can be eexecuted to show who is the current player. One character will be displayed, either `B` for Black stone or `W` for White stone. 

This command can be executed at **any time**.

- term

`term` command forces the controller to terminate with exit code 1. This command can be executed ay any time. This command will suppress history moves messages and the exit message. 


- resign

`resign` command can be executed by a player to resign from the game. This command will cause the current player to end the game and lose. The other player will win the game. This command can be executed at any time.

- view

`view` command can be executed by a player to view the current board. The controller will respond with a one-line output, consisting of two strings separated by a comma.

The first string denotes the centre coordinate of the 7 × 7 **hole** that is not covered by the **Mist**.

The second string denotes the status of grid points in the hole. That is, whether each point is occu- pied by a black stone, a white stone, not occupied or off-board. This string is the concatenation of rows’ status (from the greatest row number 19 to the least row number 1), and each row starts with
the lowest column (from A to S). 

```
 1  2  3  4  5  6  7
 8  9 10 11 12 13 14 
15 16 17 18 19 20 21 
22 23 24 25 26 27 28 
29 30 31 32 33 34 35 
36 37 38 39 40 41 42 
43 44 45 46 47 48 49


```


`#`, `o` ,`.`,`x` denotes black, white, empty and off-board.

If the **hole** is partially off-board, then the grid points that are off-board should be represented by $x$. See [Example 4](#example4).

This command can be executed at any time.


- place \<C>\<R>

`place` command can be executed by a player to place a stone on the Go board according to the Go coordinate \<C>\<R>. If the placement is successful, the controller will not respond with any output and silently alternate the player. However, if the given placement is invalid, then it will respond with a one-line error message without alternating the player. If the placement (e.g. `Z100`) cannot be recognised as a valid board coordinate, then it outputs `Invalid coordinate`. If the placement can be recognised as a valid board coordinate however the coordinate is occupied, then it outputs `Occupied coordinate`.

This command can be executed at any time. 

Placements in the **Mist** are allowed.

- history

`history` command can be executed to obtain all history of moves in Go coordinates \<C>\<R>. In particular, a one-line output formed by a sequence of the Go coordinates. For example, if Black first places a stone at `A1`, then White at `B2`, followed by Black at `C3` and finally White at `D4`, the history requested at this point should read `A1B2C3D4`. This command can be executed at any time.

## Example

### Example1 

```java
who
B
term
```

### Example2 

```
who 
B
place 
A1
who 
W
resign
Black wins!
A1
Thank you for playing!
```
### Example3 

```
place A1
place B2
place C3
place D4
history
A1B2C3D4
term
```
### Example4 

```
view
J10,.................................................
place A1
view
M3,..........................................xxxxxxx
place B2
view
L17,xxxxxxx..........................................
place C3
view
B1,xx.....xx..#..xx.o...xx#....xxxxxxxxxxxxxxxxxxxxx
place D4
view
B12,xx.....xx.....xx.....xx.....xx.....xx.....xx.....
history
A1B2C3D4
term
```

### Example5

```
place A1
place B1
place A2
place B2
place A3
place B3
place A4
place B4
place A5
Black wins!
A1B1A2B2A3B3A4B4A5
Thank you for playing!
```
