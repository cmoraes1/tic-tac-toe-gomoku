// Camilla Moraes - camillamoraes@wustl.edu
// File: TicTacToeFunctions.cpp
// Lab 4
// Source file with functions that relate to the Tic Tac Toe game. Functions print the game board, switches 
// which player is the current player, and checks if a player has one (3 pieces in a row horizontally, vertically, or diagonally).

#include "stdafx.h"
#include "Header.h"
#include "Functions.h"
#include "Game_Piece.h"
#include "Game.h"
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//overridden virtual print method 
void TicTacToeGame::print()
{
	cout << *this << endl;
}

// check if 3 X's or O's are in a vertical, horizontal or diagonal line - check read me for info about function
// implementation
bool TicTacToeGame::done()
{

	//check for 3 X's or O's in a horizontal line - checks if piece type for indices in a horizontal line are equal
	for (int i = 6; i <= 16; i=i+5)
	{
		//indices in horizontal line increase by 1
		if (TicTacToeGame::pieces[i].piece_type != " " && TicTacToeGame::pieces[i].piece_type
			== TicTacToeGame::pieces[i + 1].piece_type && TicTacToeGame::pieces[i + 1].piece_type ==
			TicTacToeGame::pieces[i + 2].piece_type)
		{
			if (TicTacToeGame::pieces[i].piece_type == "X")
			{
				winning_piece = "X";
				GameBase::winning_piece = "X";
			}
			else 
			{
				winning_piece = "O";
				GameBase::winning_piece = "O";
			}
			return true;
		}
	}

	//check for 3 X's or O's in a vertical line -  checks if piece type for indices in a vertical line are equal
	for (int i = 6; i <= 8; ++i)
	{
		//indices in vertical line increase by 5
		if (TicTacToeGame::pieces[i].piece_type != " " && TicTacToeGame::pieces[i].piece_type
			== TicTacToeGame::pieces[i + 5].piece_type && TicTacToeGame::pieces[i + 5].piece_type ==
			TicTacToeGame::pieces[i + 10].piece_type)
		{
			if (TicTacToeGame::pieces[i].piece_type == "X")
			{
				winning_piece = "X";
				GameBase::winning_piece = "X";
			}
			else 
			{
				winning_piece = "O";
				GameBase::winning_piece = "O";
			}
			return true;
		}
	}


	//check for 3 X's or O's in a diagonal line - starting bottom left and moving to the top right 
	if(TicTacToeGame::pieces[TicTacToe_LeftDiagIndex].piece_type != " " && (TicTacToeGame::pieces[TicTacToe_LeftDiagIndex].piece_type ==
		TicTacToeGame::pieces[TicTacToe_LeftDiagIndex *2].piece_type  && TicTacToeGame::pieces[TicTacToe_LeftDiagIndex *2].piece_type  ==
		TicTacToeGame::pieces[TicTacToe_LeftDiagIndex *3].piece_type))
	{
		if (TicTacToeGame::pieces[TicTacToe_LeftDiagIndex].piece_type == "X")
		{
			winning_piece = "X";
			GameBase::winning_piece = "X";
		}
		else 
		{
			winning_piece = "O";
			GameBase::winning_piece = "O";
		}
		return true;
	}

	//check for 3 X's or O's in a diagonal line - starting bottom right and ending at top left 
	if (TicTacToeGame::pieces[TicTacToe_RightDiagIndex].piece_type != " " && (TicTacToeGame::pieces[TicTacToe_RightDiagIndex].piece_type ==
		TicTacToeGame::pieces[TicTacToe_RightDiagIndex +4].piece_type && TicTacToeGame::pieces[TicTacToe_RightDiagIndex +4].piece_type ==
		TicTacToeGame::pieces[TicTacToe_RightDiagIndex *2].piece_type))
	{
		if (TicTacToeGame::pieces[TicTacToe_RightDiagIndex].piece_type == "X")
		{
			winning_piece = "X";
			GameBase::winning_piece = "X";
		}
		else 
		{
			winning_piece = "O";
			GameBase::winning_piece = "O";
		}
		return true;
	}

	return false;
}

//function that checks if game is over due to a tie or a win 
bool TicTacToeGame::draw()
{

	if (GameBase::moves_remaining == 0)
	{
		return true; 
	}

	//return false if there are moves remaining in the game
	if (TicTacToeGame::moves_remaining != 0)
	{
		return false;
	}

	GameBase::moves_remaining = ZeroMovesRemaining;
	return true;

}

//function that alternates whose turn it is and contains code to place players piece onto game board
int TicTacToeGame::turn()
{

	//set game base width and height to be width and height of tic tac toe game board
	GameBase::width = TicTacToeBoardWidth;
	GameBase::height = TicTacToeBoardHeight;

	cout << endl;

	// variables to pass into prompt function (values of these variables don't matter since they get 
	// replaced with user's input 
	unsigned int x = 0;
	unsigned int y = 0;

	//alternate whose turn it is each time function is called 
	if (TicTacToeGame::current_player == 'X')
	{
		cout << "Current player is Player X" << endl;
		prompt(x, y);

		int valid_board_width = TicTacToeBoardWidth;
		int index = valid_board_width * y + x;

		//set x and y coordinates of piece to the coordinates user entered
		TicTacToeGame::pieces[index].x_coord = x;
		TicTacToeGame::pieces[index].y_coord = y;

		//check if spot at coordinates entered by user already has a piece in it
		if (TicTacToeGame::pieces[index].piece_type != " ")
		{
			cout << "The spot you chose is already filled." << endl;
			return BoardSpotFilled;
		}
		//if spot is empty
		else
		{
			TicTacToeGame::pieces[index].piece_type = "X";
			int x_coord = TicTacToeGame::pieces[index].x_coord;
			int y_coord = TicTacToeGame::pieces[index].y_coord;

			if (GameBase::moves_remaining != 0)
			{
				moves_remaining = moves_remaining - 1;
				GameBase::moves_played++;
				GameBase::moves_remaining = GameBase::moves_remaining - 1;
				moves_played++;

				//add coordinates to vector storing players moves
				TicTacToeGame::player_x_moves.push_back(make_pair(x_coord, y_coord));
				print();
				cout << endl;

				//print out all coordinates stored in vector to display players moves
				cout << "Player X Moves: ";
				for (unsigned int i = 0; i < player_x_moves.size(); ++i)
				{
					cout << player_x_moves[i].first << "," << player_x_moves[i].second << "; ";
				}
				cout << endl;

			}

		}

		TicTacToeGame::current_player = 'O';

	}
	else if (TicTacToeGame::current_player == 'O')
	{
		cout << "Current player is Player O" << endl;
		prompt(x, y);

		int valid_board_width = TicTacToeBoardWidth;
		int index = valid_board_width * y + x;

		//set x and y coordinates of piece to the coordinates user entered
		TicTacToeGame::pieces[index].x_coord = x;
		TicTacToeGame::pieces[index].y_coord = y;

		//check if spot at coordinates entered by user already has a piece in it
		if (TicTacToeGame::pieces[index].piece_type != " ")
		{
			cout << "The spot you chose is already filled." << endl;
			return BoardSpotFilled;
		}
		//if spot is empty
		else
		{
			TicTacToeGame::pieces[index].piece_type = "O";
			int x_coord = TicTacToeGame::pieces[index].x_coord;
			int y_coord = TicTacToeGame::pieces[index].y_coord;

			if (GameBase::moves_remaining != 0)
			{
				moves_remaining = moves_remaining - 1;
				GameBase::moves_remaining = GameBase::moves_remaining - 1;
				GameBase::moves_played++;
				moves_played++;

				//add coordinates to vector storing players moves
				TicTacToeGame::player_o_moves.push_back(make_pair(x_coord, y_coord));
				print();
				cout << endl;

				//print out all coordinates stored in vector to display players moves
				cout << "Player O Moves: ";
				for (unsigned int i = 0; i < player_x_moves.size(); ++i)
				{
					cout << player_o_moves[i].first << "," << player_o_moves[i].second << "; ";
				}
				cout << endl;
			}

		}

		TicTacToeGame::current_player = 'X';
	}

	return Success;

}

