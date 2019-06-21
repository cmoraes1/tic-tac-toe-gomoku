// Camilla Moraes - camillamoraes@wustl.edu
// File: Functions.cpp
// Lab 3
// Source file with function definition for usage message function telling the user how to run the program as well
// as functions defined in the Game Base class (i.e. play, game_function, and prompt function) 

#include "stdafx.h"
#include "Header.h"
#include "Functions.h"
#include "Game_Piece.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include <memory>

using namespace std;

//usage message that tells the user how to correctly run the program
int usage_message(char * programName) 
{
	cout << "usage: " << programName << " <TicTacToe> or <Gomoku>" << endl;
	return InvalidNumberOfArguments;
}

//function that determines whether to continue playing the game or whether it has ended due to no more moves 
//winnable remaining, a tie game, or the user entering quit 
int GameBase::play()
{
	print();

	//while there is no winner and moves still remain continue calling turn function
	while (done() == false && draw() == false)
	{
		turn();
	}

	//if a player has won 
	if (done() == true)
	{
		cout << "Player " << winning_piece << " wins!" << endl;
		return Success;
	}
	//if no moves remain but neither player won -- tie game
	else if (draw() == true)
	{
		cout << "Game Over! There is no winner." << endl;
		cout << "Number of moves played: " << GameBase::moves_played << endl;
		cout << "Number of moves remaining: " << GameBase::total_moves - GameBase::moves_played << endl;
		return GameOverWithoutWinner;
	}

	return Success;
}

//function that dynamically constructs an object of derived TicTacToe or Gomoku game
shared_ptr<GameBase> GameBase::game_function(int i, char * arr[])
{

	//error val pointer to indicate to object was constructed 
	shared_ptr<GameBase> error_val = 0;

	//check for correct number of command line arguments
	if (i != NumArguments)
	{
		cout << "Invalid number of arguments" << endl;
	}
	else
	{
		string file_name = arr[FileName];

		//make sure user input is "TicTacToe" or "Gomoku"
		if (file_name != "TicTacToe" && file_name != "Gomoku")
		{
			cout << "Incorrect file name" << endl;
		}
		//construct object of TicTacToe game
		else if(file_name == "TicTacToe")
		{
			shared_ptr<GameBase> tic_tac_toe_game = make_shared<TicTacToeGame>();
			return tic_tac_toe_game;
		}
		//construct object of Gomoku game 
		else if (file_name == "Gomoku")
		{
			shared_ptr<GameBase> gomoku_game = make_shared<GomokuGame>();
			return gomoku_game;
		}
		else
		{
			//return pointer (whose value is 0) indicating no object was constructed 
			return error_val;
		}
	}

	return error_val;

}

//prompt user to enter coordinates for game piece or quit game 
int GameBase::prompt(unsigned int & x, unsigned int & y)
{
	string coordinate = " ";

	//set number of moves equal to 9 (# of spots on board) if game being played is tic tac toe
	if (GameBase::width == TicTacToeBoardWidth && GameBase::height == TicTacToeBoardHeight)
	{
		GameBase::total_moves = TicTacToeGameMoves;
		GameBase::moves_remaining = TicTacToeGameMoves;
	}
	//set number of moves equal to 361 (# of spots on board) if game being played is Gomoku
	else if (GameBase::width == GomokuBoardWidth && GameBase::height == GomokuBoardHeight)
	{
		GameBase::total_moves = GomokuGameMoves;
		GameBase::moves_remaining = GomokuGameMoves;
	}

	//prompt user to type "quit" or a string representing a valid coordinate "0,0"
	cout << "Enter a valid coordinate (i.e. 1,1) or enter quit if you wish to stop playing." << endl;

	getline(cin, coordinate);

	//end game is user enters "quit" 
	if (coordinate == "quit")
	{
		cout << endl;

		cout << "User has chosen to quit game." << endl;

		//set moves_remaining to 0 now that the game is over
		GameBase::moves_remaining = ZeroMovesRemaining;
		return UserQuitGame;
	}

	//make sure coordinates are properly formatted in tic tac toe game 
	if (GameBase::width == TicTacToeBoardWidth && GameBase::height == TicTacToeBoardHeight)
	{
		//comma_location represents the location of the comma in a properly formatted string of coordinates
		unsigned int comma_location = 1;

		//variable to keep track of number of commas to check for errors in input
		unsigned int comma_count = 0;

		//exact number of commas correct input should have
		unsigned int correct_count = 1;

		//max length of valid coordinate
		unsigned int max_coord_len = 3;

		//loop through user input string to count number of commas 
		for (unsigned int i = 0; i < coordinate.length(); ++i)
		{
			if (coordinate.at(i) == ',')
			{
				comma_count++;
			}
		}

		//check if there is an error in the users input 
		if (comma_count > correct_count || coordinate.length() < max_coord_len || coordinate.at(comma_location) != ',' || coordinate.at(comma_location - 1) == ' ' || coordinate.at(comma_location + 1) == ' ')
		{
			cout << "Unable to extract coordinates. Please make sure you input follows the following format: 1,1" << endl;
			//repeatedly call function until coordinate is valid or quit is pressed
			prompt(x, y);
			return BadlyFormattedInput;
		}
		//replace comma with a space if input is well formatted
		else if (coordinate.at(comma_location) == ',')
		{
			coordinate.at(comma_location) = ' ';
		}
	}
	//make sure coordinates are properly formatted in gomoku game 
	else if (GameBase::width == GomokuBoardWidth && GameBase::height == GomokuBoardHeight)
	{

		//set comma location (location of comma in coordinates) to be 0 initially 
		unsigned int comma_location = 0;
		
		//count number of commas to check for errors in input
		unsigned int comma_count = 0;

		//correct number of commas valid input should have
		unsigned int correct_comma_count = 1;

		//min length of valid input
		unsigned int min_input_length = 3;

		//invalid comma location
		unsigned int comma_err = 0;

		//loop through user input string to get location of the comma
		for (unsigned int i = 0; i < coordinate.length(); ++i)
		{
			if (coordinate.at(i) == ',')
			{
				coordinate.at(i) = ' ';
				comma_location = i;
				comma_count++;
			}
		}

		//check if the is an error in users input 
		if (comma_count > correct_comma_count || coordinate.length() < min_input_length || comma_location == comma_err || comma_location == coordinate.length() || comma_location == coordinate.length() - 1 || coordinate.at(comma_location + 1) == ' ' || coordinate.at(comma_location - 1) == ' ')
		{
			cout << "Unable to extract coordinates due to an error in your input. " << endl;
			//repeatedly call function until coordinate is valid or quit is pressed
			prompt(x, y);
			return BadlyFormattedInput;
		}

	}

	istringstream iss(coordinate);

	//extract x and y coordinates user entered into unsigned integers passed into program 
	if (iss >> x && iss >> y)
	{

		int error_val = 0;

		//i wrote this if statement to fix a bug where a game piece with coordinates 0,0 was being added
		if (x == error_val || y == error_val)
		{
			cout << "The coordinate you entered is not valid." << endl;;
			//repeatedly call function until coordinate is valid or quit is pressed
			prompt(x, y);
			return BadlyFormattedInput;
		}

		//checking coordinate boundaries for tic tac toe 
		if (GameBase::width == TicTacToeBoardWidth && GameBase::height == TicTacToeBoardHeight)
		{
			//check if coordinates entered are out of bounds of inner 3 x 3 board 
			if (x < LowerLimit || x > UpperLimit || y < LowerLimit || y > UpperLimit)
			{
				cout << "The coordinate you entered is not valid." << endl;;
				//repeatedly call function until coordinate is valid or quit is pressed
				prompt(x, y);
			}
		}
		//checking coordiante boundaries for gomoku
		else if (GameBase::width == GomokuBoardWidth && GameBase::height == GomokuBoardHeight)
		{
			//check if coordinates entered are out of bounds of 19 x 19 board
			if (x < 1 || y < 1 || x > 19 || y > 19)
			{
				cout << "The coordinate you entered is not valid." << endl;;
				//repeatedly call function until coordinate is valid or quit is pressed
				prompt(x, y);
			}
		}
	}
	else 
	{
		cout << "Unable to extract coordinates" << endl;
		prompt(x, y);
		return ErrorExtractingCoordinates;
	}

	return Success;

}

