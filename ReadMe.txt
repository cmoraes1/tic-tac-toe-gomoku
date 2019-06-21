Camilla Moraes - camillamoraes@wustl.edu
Lab 4
Team Members: Camilla Moraes - completed lab on my own 
______________________________________________________________________________________________________________________________

Program Summary:

This program allows users to play a game of Tic Tac Toe or Gomoku. In Tic Tac Toe, users either place an X or O
on a 3 by 3 board with the end goal of getting 3 of their pieces in a row, whether it is horzontally, vertically, 
or diagonally. In Gomoku, users have a 19 by 19 board and can either place a B (black stone) or W (white stone).
In order to win, they need to get 5 pieces in a row, horizontally, vertically, or diagonally. In both games the
user can enter quit at any given point if they no longer want to play the game. 

______________________________________________________________________________________________________________________________

How to play:

To play Tic Tac Toe, enter the following into the command line: lab4 TicTacToe
To play Gomoku, enter the following into the command line: lab4 Gomoku
______________________________________________________________________________________________________________________________

Design Choices:

1. I made a vector to hold all 25 pieces on the 5x5 board. Because the outer 16 pieces are never filled and remain
empty throughout the entire game, I initially thought I would just create a vector of 9 pieces that held the
pieces in the inner 3x3 board. However, I changed my mind because I think that even though the outer 16 squares
are never filled, they should still be represented as empty pieces with x and y coordinates. 

2. For the done() function I am checking if 3 or 5 pieces (dependeing on if game is tic tac toe or gomoku)
in a horizontal, vertical, or diagonal line on the board arethe same by checking if the piece type at at certain 
indices are equal. Although I have an enum that represents the index bottom left corner of the 3 x 3 board or 19 x 19 board
and an enum that represents the index of bottom right corner of the 3 x 3 or the 19 x 19 board, I increment these values by certain amounts 
(different depending on horizontal, vertical or diagonal case) in order to get the index of the piece that we want 
to compare the current piece with. I technically could make an enum or declare an integer to represent the numbers 
that I am incrementing the indices by, but this would involve a lot of variable or enum declarations that aren't 
completely necessary. The same holds for the draw() function. I increment each index by a certain value (i.e. 
horizontal indices increase by 1, vertical indices increase by 20) depending on if its horizontal, vertical or
diagonal, and while I could create enums for all of these values to avoid using actual numbers in my code, it would
not really improve the readability of my code since I am essentially just increment a value, which can be explained
in comments above the code. 

3. I stored all pieces of a players pieces in a vector based on their respective indices, which I calculated for
each piece using the following equation: board_width * y + x;. I multiplied the width of the board by the
y coordinate of the piece added to the x coordinate of the piece so that each piece had a unique index and could
be accessed from the vector. 

4. I chose to use a shared_ptr instead of the new operator to construct an object of the derived TicTacToeGame
and GomokuGame classes because using shared_ptr takes care of destroying the object automatically, whereas I 
would've have to call delete on the object on my own if I used the new operator. Additionally, I didn't have to
worry about catching the bad_alloc exception since this only occurs with the new operator. Therefore, using
shared_ptr seemed like an easier, simpler and safer solution. 

5. My logic for determining if there were any winnable moves left in Gomoku changed while writing the program. Initially,
I wrote code in my draw function that looped through every adjacent 5 spots in a row (horizontally, vertically, and
diagonally) on the board and first checked if they were all empty. If all 5 spots next to each other were empty, then
this meant there were winnable moves left. Then, I looped through all 5 adjacent spots on the board again and 
counted the number of empty spaces, the number of W's, and the number of B's. If there number of W's + the number
of empty spaces OR the number of B's + the number of empty spaces were equal to 5, then this meant there were winnable
moves left. After writing most of this code, I found a lot of bugs in my code that made me reconsider my logic
and try to come up with a more efficient and simpler solution. I created two vectors and filled one of them (called
b_vect) with all B's, and the other one (called w_vect) with all W's. Every time the user enters a coordinate
onto the game board, this piece is also updated in both of the vectors. I wrote code in my draw function that is
similar to my done function. I loop through both of the vectors and check if there are 5 of the same piece in a row
horizontally, vertically or diagonally in both of the vectors, and if there are that means that there are winnable
moves left. 

______________________________________________________________________________________________________________________________

Error Values:

Success: returned when program runs successfully
InvalidNumberOfArguments: returned when user enters too many or too few command line arguments 
UserQuitGame: returned when user chooses to quit game
BadlyFormattedInput: returned when user enters coordinates that are not properly formatted 
ErrorExtractingCoordinates: returned if there is an error extracting coordinates entered
BoardSpotFilled: returned if user enters coordinate where there is already a piece on the board
GameOverWithoutWinner: returned if there is a tie 
______________________________________________________________________________________________________________________________

Test Cases:

Wrong number of command line arguments:

Inputs Tested:
lab4
lab4 Tic Tac Toe
lab4 Gomoku testing command line args

Output:
Invalid number of arguments
usage: lab4 <TicTacToe> or <Gomoku>


Incorrect command line arguments:

Inputs Tested:
lab4 alskjdfalksdjf
lab4 Tictactoe
lab4 GomoKu

Output:
Incorrect file name
usage: lab4 <TicTacToe> or <Gomoku>

Unproperly formatted coordinates:

Inputs Tested: 
1, 1
1     , 1
, 1
123123123
23,12345

Output:
Unable to extract coordinates. Please make sure you input follows the following format: 1,1
Enter a valid coordinate (i.e. 1,1) or enter quit if you wish to stop playing.

Out of bounds coordinates:

TicTacToe Inputs Tested:
4,4
0,0
20,25

Output:
The coordinate you entered is not valid.
Enter a valid coordinate (i.e. 1,1) or enter quit if you wish to stop playing.

Gomoku Inputs Tested:
20,0
0,0
40,50

Output:
The coordinate you entered is not valid.
Enter a valid coordinate (i.e. 1,1) or enter quit if you wish to stop playing.

Special characters entered as coordinates (i.e. backslash):

Inputs Tested:
,/\
,,,,

Output:
Unable to extract coordinates. Please make sure you input follows the following format: 1,1
Enter a valid coordinate (i.e. 1,1) or enter quit if you wish to stop playing.

Attempting to add a piece to the board in a spot that's already filled:

Input:
* Any set of coordinates on the board where a piece has already been placed *

Output:
The spot you chose is already filled.
Current player is Player O
Enter a valid coordinate (i.e. 1,1) or enter quit if you wish to stop playing.

