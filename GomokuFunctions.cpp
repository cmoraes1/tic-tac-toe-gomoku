// Camilla Moraes - camillamoraes@wustl.edu
// Lab 4
// File: GomokuFunctions.cpp
// Source file with functions defined in GomokuGame class that control the behavior of the Gomoku game (i.e. print
// the game board, check if a user has won, alternate turns between players, check if there are winnable moves left)

#include "stdafx.h"
#include "Header.h"
#include "Functions.h"
#include "Game_Piece.h"
#include "Game.h"
#include <iostream>

using namespace std; 

//create two vectors (one with all Bs, one with all Ws) that will be used to predict if winnable moves are left
void GomokuGame::fill_vectors()
{
	//fill in all b vector with all B pieces
	for (int i = GomokuBoardWidth - 1; i >= 0; i--)
	{
		for (int j = 0; j <= GomokuBoardHeight - 1; j++)
		{
			//create index for each piece in board 
			int board_width = GomokuBoardWidth;
			int index = board_width * i + j;

			int default_coord = 0;

			//fill vector with B's with initial coordinates being 0,0 (placeholders to fill vector)
			Game_Piece piece;
			//set x and y coordinates of game pieces 
			piece.x_coord = default_coord;
			piece.y_coord = default_coord;
			piece.piece_type = "B";
			GomokuGame::b_vect.push_back(piece);

		}
	}

	//fill all b vector with actual piece coordinates
	for (int i = GomokuBoardWidth - 1; i > 0; --i)
	{

		for (int j = 1; j <= GomokuBoardHeight - 1; j++)
		{
			//get index of each piece on the board 
			int board_width = GomokuBoardWidth;
			int index = board_width * i + j;

			//set x and y coordinates of game pieces 
			GomokuGame::b_vect[index].x_coord = j;
			GomokuGame::b_vect[index].y_coord = i;
		}
	}

	//fill in all w vector with all W pieces (starting with all pieces having coordinates 0,0 just to fill vector)
	for (int i = GomokuBoardWidth - 1; i >= 0; i--)
	{
		for (int j = 0; j <= GomokuBoardHeight - 1; j++)
		{
			//create index for each piece in board 
			int board_width = GomokuBoardWidth;
			int index = board_width * i + j;

			int default_coord = 0;

			//fill empty with empty pieces as placeholders (x and y coordinates set to 0, piece type is an empty char)
			Game_Piece piece;
			//set x and y coordinates of game pieces 
			piece.x_coord = default_coord;
			piece.y_coord = default_coord;
			piece.piece_type = "W";
			GomokuGame::w_vect.push_back(piece);

		}
	}
	//fill all w vector with actual piece coordinates 
	for (int i = GomokuBoardWidth - 1; i > 0; --i)
	{

		for (int j = 1; j <= GomokuBoardHeight - 1; j++)
		{
			//get index of each piece on the board 
			int board_width = GomokuBoardWidth;
			int index = board_width * i + j;

			//set x and y coordinates of game pieces 
			GomokuGame::w_vect[index].x_coord = j;
			GomokuGame::w_vect[index].y_coord = i;
		}
	}

}

void GomokuGame::print() 
{
	cout << *this << endl;

	//fill all B and all W vectors when game begins 
	if (GomokuGame::moves_remaining == GomokuGameMoves)
	{
		fill_vectors();
	}
}

//function to determine if a player has won the game
bool GomokuGame::done()
{
	//check for 5 B's or W's in a horizontal line - checks if piece type for indices in a horizontal line are equal
	for (int i = 21; i <= 399; ++i)
	{

		//indices in horizontal line increase by 1
		if (GomokuGame::pieces[i].piece_type != " " && GomokuGame::pieces[i].piece_type
			== GomokuGame::pieces[i + 1].piece_type && GomokuGame::pieces[i + 1].piece_type ==
			GomokuGame::pieces[i + 2].piece_type && GomokuGame::pieces[i + 2].piece_type ==
			GomokuGame::pieces[i + 3].piece_type && GomokuGame::pieces[i + 3].piece_type ==
			GomokuGame::pieces[i + 4].piece_type)
		{
			if (GomokuGame::pieces[i].piece_type == "B")
			{
				winning_piece = "B";
				GameBase::winning_piece = "B";
			}
			else
			{
				winning_piece = "W";
				GameBase::winning_piece = "W";
			}
			return true;
		}
	}

	//check for 5 B's or W's in a vertical line -  checks if piece type for indices in a vertical line are equal
	for (int i = 21; i <= 399; ++i)
	{
		//indices in vertical line increase by 5
		if (GomokuGame::pieces[i].piece_type != " " && GomokuGame::pieces[i].piece_type
			== GomokuGame::pieces[i + 20].piece_type && GomokuGame::pieces[i + 20].piece_type ==
			GomokuGame::pieces[i + 40].piece_type && GomokuGame::pieces[i + 40].piece_type ==
			GomokuGame::pieces[i + 60].piece_type && GomokuGame::pieces[i + 60].piece_type ==
			GomokuGame::pieces[i + 80].piece_type)
		{
			if (GomokuGame::pieces[i].piece_type == "B")
			{
				winning_piece = "B";
				GameBase::winning_piece = "B";
			}
			else
			{
				winning_piece = "W";
				GameBase::winning_piece = "W";
			}
			return true;
		}
	}


	//check for 5 B's or W's in a diagonal line
	for (int i = 21; i <= 399; ++i)
	{
		//starting at bottom left index and moving to the top right
		if (GomokuGame::pieces[i].piece_type != " " && GomokuGame::pieces[i].piece_type
			== GomokuGame::pieces[i + 21].piece_type && GomokuGame::pieces[i + 21].piece_type ==
			GomokuGame::pieces[i + 42].piece_type && GomokuGame::pieces[i + 42].piece_type ==
			GomokuGame::pieces[i + 63].piece_type && GomokuGame::pieces[i + 63].piece_type ==
			GomokuGame::pieces[i + 84].piece_type)
		{
			if (GomokuGame::pieces[i].piece_type == "B")
			{
				winning_piece = "B";
				GameBase::winning_piece = "B";
			}
			else
			{
				winning_piece = "W";
				GameBase::winning_piece = "W";
			}
			return true;
		}

		// starting bottom right and moving to top left 
		if (GomokuGame::pieces[i].piece_type != " " && GomokuGame::pieces[i].piece_type
			== GomokuGame::pieces[i + 19].piece_type && GomokuGame::pieces[i + 19].piece_type ==
			GomokuGame::pieces[i + (19*2)].piece_type && GomokuGame::pieces[i + (19*2)].piece_type ==
			GomokuGame::pieces[i + (19*3)].piece_type && GomokuGame::pieces[i + (19*3)].piece_type ==
			GomokuGame::pieces[i + (19*4)].piece_type)
		{
			if (GomokuGame::pieces[i].piece_type == "B")
			{
				winning_piece = "B";
				GameBase::winning_piece = "B";
			}
			else
			{
				winning_piece = "W";
				GameBase::winning_piece = "W";
			}
			return true;
		}
	
	}
		
	return false;
}

//checks if there are moves remaining in the game or if there are no winnable moves left in the game 
bool GomokuGame::draw()
{

	if (GameBase::moves_remaining == 0)
	{
		return true;
	}

	//boolean starts as false each time function is called and is only set to true if winning moves are left
	bool winning_moves = false;

	//find more info about this implementation in ReadMe.txt
	//check if there are 5 B's (in all B vector) or 5 W's (in all W vector) in a horizontal line 
	for (int i = 21; i <= 399; ++i)
	{

		//indices in horizontal line increase by 1
		if ((GomokuGame::b_vect[i].piece_type == GomokuGame::b_vect[i + 1].piece_type &&
			GomokuGame::b_vect[i + 1].piece_type == GomokuGame::b_vect[i + 2].piece_type &&
			GomokuGame::b_vect[i + 2].piece_type == GomokuGame::b_vect[i + 3].piece_type &&
			GomokuGame::b_vect[i + 3].piece_type == GomokuGame::b_vect[i + 4].piece_type) ||
			(GomokuGame::w_vect[i].piece_type == GomokuGame::w_vect[i + 1].piece_type &&
				GomokuGame::w_vect[i + 1].piece_type == GomokuGame::w_vect[i + 2].piece_type &&
				GomokuGame::w_vect[i + 2].piece_type == GomokuGame::w_vect[i + 3].piece_type &&
				GomokuGame::w_vect[i + 3].piece_type == GomokuGame::w_vect[i + 4].piece_type))
		{
			winning_moves = true;
			break;
		}
	}

	//check if there are 5 B's (in all B vector) or 5 W's (in all W vector) in a vertical line 
	for (int i = 21; i <= 399; ++i)
	{
		//indices in vertical line increase by 20
		if ((GomokuGame::b_vect[i].piece_type
			== GomokuGame::b_vect[i + 20].piece_type && GomokuGame::b_vect[i + 20].piece_type ==
			GomokuGame::b_vect[i + 40].piece_type && GomokuGame::b_vect[i + 40].piece_type ==
			GomokuGame::b_vect[i + 60].piece_type && GomokuGame::b_vect[i + 60].piece_type ==
			GomokuGame::b_vect[i + 80].piece_type) ||
			(GomokuGame::w_vect[i].piece_type
				== GomokuGame::w_vect[i + 20].piece_type && GomokuGame::w_vect[i + 20].piece_type ==
				GomokuGame::w_vect[i + 40].piece_type && GomokuGame::w_vect[i + 40].piece_type ==
				GomokuGame::w_vect[i + 60].piece_type && GomokuGame::w_vect[i + 60].piece_type ==
				GomokuGame::w_vect[i + 80].piece_type))
		{
			winning_moves = true;
			break;
		}
	}

	//check if there are 5 B's (in all B vector) or 5 W's (in all W vector) in a diagonal line 
	for (int i = 21; i <= 399; ++i)
	{
		//starting at bottom left index and moving to the top right - indices increase by 21
		if ((GomokuGame::b_vect[i].piece_type
			== GomokuGame::b_vect[i + 21].piece_type && GomokuGame::b_vect[i + 21].piece_type ==
			GomokuGame::b_vect[i + 42].piece_type && GomokuGame::b_vect[i + 42].piece_type ==
			GomokuGame::b_vect[i + 63].piece_type && GomokuGame::b_vect[i + 63].piece_type ==
			GomokuGame::b_vect[i + 84].piece_type) || (GomokuGame::w_vect[i].piece_type
				== GomokuGame::w_vect[i + 21].piece_type && GomokuGame::w_vect[i + 21].piece_type ==
				GomokuGame::w_vect[i + 42].piece_type && GomokuGame::w_vect[i + 42].piece_type ==
				GomokuGame::w_vect[i + 63].piece_type && GomokuGame::w_vect[i + 63].piece_type ==
				GomokuGame::w_vect[i + 84].piece_type))
		{
			winning_moves = true;
			break;
		}

		// starting bottom right and moving to top left - indices increase by 19 
		if ((GomokuGame::b_vect[i].piece_type
			== GomokuGame::b_vect[i + 19].piece_type && GomokuGame::b_vect[i + 19].piece_type ==
			GomokuGame::b_vect[i + (19 * 2)].piece_type && GomokuGame::b_vect[i + (19 * 2)].piece_type ==
			GomokuGame::b_vect[i + (19 * 3)].piece_type && GomokuGame::b_vect[i + (19 * 3)].piece_type ==
			GomokuGame::b_vect[i + (19 * 4)].piece_type) || (GomokuGame::w_vect[i].piece_type
				== GomokuGame::w_vect[i + 19].piece_type && GomokuGame::w_vect[i + 19].piece_type ==
				GomokuGame::w_vect[i + (19 * 2)].piece_type && GomokuGame::w_vect[i + (19 * 2)].piece_type ==
				GomokuGame::w_vect[i + (19 * 3)].piece_type && GomokuGame::w_vect[i + (19 * 3)].piece_type ==
				GomokuGame::w_vect[i + (19 * 4)].piece_type))
		{
			winning_moves = true;
			break;
		}

	}

	//return false if there are (winnable) moves remaining in the game
	if (winning_moves == true && GomokuGame::moves_remaining != 0 )
	{
		return false;
	}

	GameBase::moves_remaining = ZeroMovesRemaining;
	return true; 
}

//function that alternates players turn and places each players piece on the board  
int GomokuGame::turn()
{
	//set game base width and height to be width and height of gomoku game board
	GameBase::height = GomokuBoardHeight;
	GameBase::width = GomokuBoardWidth;

	cout << endl;

	// variables to pass into prompt function (values of these variables don't matter since they get 
	// replaced with user's input 
	unsigned int x = 0;
	unsigned int y = 0;

	//alternate whose turn it is each time function is called 
	if (GomokuGame::current_player == 'B')
	{
		cout << "Current player: Black Stone" << endl;
		prompt(x, y);

		int valid_board_width = GomokuBoardWidth;
		int index = valid_board_width * y + x;

		//set x and y coordinates of piece to the coordinates user entered
		GomokuGame::pieces[index].x_coord = x;
		GomokuGame::pieces[index].y_coord = y;

		//check if spot at coordinates entered by user already has a piece in it
		if (GomokuGame::pieces[index].piece_type != " ")
		{
			cout << "The spot you chose is already filled." << endl;
			return BoardSpotFilled;
		}
		//if spot is empty
		else
		{
			GomokuGame::pieces[index].piece_type = "B";
			int x_coord = GomokuGame::pieces[index].x_coord;
			int y_coord = GomokuGame::pieces[index].y_coord;

			//add piece to vector of all b's and w's
			GomokuGame::b_vect[index].piece_type = "B";
			GomokuGame::w_vect[index].piece_type = "B";

			if (GameBase::moves_remaining != ZeroMovesRemaining)
			{
				moves_remaining = moves_remaining - 1;
				GameBase::moves_played++;
				moves_played++;

				//add coordinates to vector storing players moves
				GomokuGame::player_b_moves.push_back(make_pair(x_coord, y_coord));
				print();
				cout << endl;

				//print out all coordinates stored in vector to display players moves
				cout << "Black Stones Moves: ";
				for (unsigned int i = 0; i < player_b_moves.size(); ++i)
				{
					cout << player_b_moves[i].first << "," << player_b_moves[i].second << "; ";
				}
				cout << endl;
			}

		}

		GomokuGame::current_player = 'W';
	}
	else if (GomokuGame::current_player == 'W')
	{
		cout << "Current player: White Stone" << endl;
		prompt(x, y);

		int valid_board_width = GomokuBoardWidth;
		int index = valid_board_width * y + x;

		//set x and y coordinates of piece to the coordinates user entered
		GomokuGame::pieces[index].x_coord = x;
		GomokuGame::pieces[index].y_coord = y;

		//check if spot at coordinates entered by user already has a piece in it
		if (GomokuGame::pieces[index].piece_type != " ")
		{
			cout << "The spot you chose is already filled." << endl;
			return BoardSpotFilled;
		}
		//if spot is empty
		else
		{
			GomokuGame::pieces[index].piece_type = "W";
			int x_coord = GomokuGame::pieces[index].x_coord;
			int y_coord = GomokuGame::pieces[index].y_coord;

			//add piece to vector of all b's and w's
			GomokuGame::b_vect[index].piece_type = "W";
			GomokuGame::w_vect[index].piece_type = "W";

			if (GameBase::moves_remaining != ZeroMovesRemaining)
			{
				moves_remaining = moves_remaining - 1;
				GameBase::moves_played++;
				moves_played++;

				//add coordinates to vector storing players moves
				GomokuGame::player_w_moves.push_back(make_pair(x_coord, y_coord));
				print();
				cout << endl;

				//print out all coordinates stored in vector to display players moves
				cout << "White Stones Moves: ";
				for (unsigned int i = 0; i < player_w_moves.size(); ++i)
				{
					cout << player_w_moves[i].first << "," << player_w_moves[i].second << "; ";
				}
				cout << endl;
			}

		}

		GomokuGame::current_player = 'B';
	}

	return Success;

}