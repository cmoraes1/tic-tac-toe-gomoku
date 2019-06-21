// Camilla Moraes - camillamoraes@wustl.edu
// Lab 4
// File: lab4.cpp
// Source file with programs class's constructors and destructors, overrided ostream operators used to print
// the game boards, and main function

#include "stdafx.h"
#include "Header.h"
#include "Functions.h"
#include "Game_Piece.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <memory>

using namespace std;

//GameBase constructor 
GameBase::GameBase()
	: width(GomokuBoardWidth), height(GomokuBoardHeight), current_player(' '), winning_piece(" "), 
	moves_played(InitialMoves), moves_remaining(GameBaseMovesRemaining), total_moves(InitialMoves), longest_string(StringLength)
{}

//GameBase destructor
GameBase::~GameBase()
{}

//TicTacToe constructor
TicTacToeGame::TicTacToeGame()
	: width(TicTacToeBoardWidth), height(TicTacToeBoardHeight), piece_type(" "), current_player('X'), winning_piece(" "),
	player_x_moves({}), player_o_moves({}), moves_remaining(TicTacToeGameMoves), moves_played(InitialMovesPlayed)
{}

//Gomoku constructor
GomokuGame::GomokuGame()
	: width(GomokuBoardWidth), height(GomokuBoardHeight), piece_type(" "), current_player('B'), winning_piece(" "), player_b_moves({}),
	player_w_moves({}), b_vect({}), w_vect({}), moves_remaining(GomokuGameMoves), moves_played(InitialMoves)
{}


//insertion operator that returns the ostream reference passed in for tic tac toe game 
ostream & operator <<(ostream & output, const TicTacToeGame & game)
{
	//use this int when creating an placeholder game piece (x and y coordinates don't matter for placeholder pieces so I made them 0)
	int default_coord = 0;

	//fill game board vector with empty pieces
	for (int i = game.width - 1; i >= 0; i--)
	{
		for (int j = 0; j <= game.height - 1; j++)
		{
			//create index for each piece in board 
			int board_width = TicTacToeBoardWidth;
			int index = board_width * i + j;

			//fill empty with empty pieces as placeholders (x and y coordinates set to 0, piece type is an empty char)
			Game_Piece piece;
			piece.x_coord = default_coord;
			piece.y_coord = default_coord;
			piece.piece_type = " ";
			game.pieces.push_back(piece);
		}
	}

	//print out 5x5 game board 
	for (int i = game.width - 1; i >= 0; i--)
	{
		cout << i << " ";
		for (int j = 0; j <= game.height - 1; j++)
		{
			//get index of each piece on the board 
			int board_width = TicTacToeBoardWidth;
			int index = board_width * i + j;

			//set x and y coordinates of game pieces 
			game.pieces[index].x_coord = j;
			game.pieces[index].y_coord = i;

			//print out each pieces piece tpye (X or O)
			cout << game.pieces[index].piece_type << " ";
		}
		cout << endl;
	}

	cout << "  " << "0 " << "1 " << "2 " << "3 " << "4 ";

	return output;
}

//insertion operator that returns the ostream reference passed in for gomoku game 
ostream & operator <<(std::ostream & output, const GomokuGame & game)
{

	int default_coord = 0;

	for (int i = game.width - 1; i >= 0; i--)
	{
		for (int j = 0; j <= game.height - 1; j++)
		{
			//create index for each piece in board 
			int board_width = GomokuBoardWidth;
			int index = board_width * i + j;

			//fill empty with empty pieces as placeholders (x and y coordinates set to 0, piece type is an empty char)
			Game_Piece piece;
			piece.x_coord = default_coord;
			piece.y_coord = default_coord;
			piece.piece_type = " ";
			game.pieces.push_back(piece);
		}
	}

	//print out 19x19 game board 
	for (int i = game.width - 1; i > 0; --i)
	{
		int two_digit_num = 2;

		//if y coordinate is 2 digits print coordinate on axis without a space after it
		if (std::to_string(i).length() == two_digit_num)
		{
			cout << i;
		}
		//if y coordinate is 1 digit print coordinate on axis with a space after it 
		else
		{
			cout << i << " ";
		}

		for (int j = 1; j <= game.height - 1; j++)
		{
			//get index of each piece on the board 
			int board_width = GomokuBoardWidth;
			int index = board_width * i + j;

			//set x and y coordinates of game pieces 
			game.pieces[index].x_coord = j;
			game.pieces[index].y_coord = i;

			//set column width to be length of longest display string
			cout << setw(game.longest_string);

			//print out each pieces piece tpye (B or W)
			cout << game.pieces[index].piece_type << " ";
		}
		cout << endl;
	}

	cout << "X  " << "1  " << "2  " << "3  " << "4  " << "5  " << "6  " << "7  " << "8  " << "9  " << "10 "
		<< "11 " << "12 " << "13 " << "14 " << "15 " << "16 " << "17 " << "18 " << "19 ";

	return output;
}

int main(int argc, char * argv[])
{

	std::shared_ptr<GameBase> game_ptr = GameBase::game_function(argc, argv);

	std::shared_ptr<GameBase> failed_obj = 0;

	//check if pointer returned from function has a value of 0 (meaning no object was constructed)
	if (game_ptr == failed_obj)
	{
		return usage_message(argv[ProgramName]);
	}
	//if object was constructed (pointer was non-zero), call the object's play method 
	else
	{
		game_ptr->play();
	}
	
	return Success;

}

