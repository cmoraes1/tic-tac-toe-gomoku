// Camilla Moraes - camillamoraes@wustl.edu
// Lab 4
// File: Game.h
// Header file with all classes, the GameBase class (base class), TicTactoeGame class (derived class), and 
// GomokuGame class (derived class) 

#pragma once

#ifndef GAME_H
#define GAME_H

#include "Game_Piece.h"
#include <vector>
#include <string>
#include <memory>

//Base Game Class
class GameBase {
protected:
	int width; 
	int height;
	char current_player;
	std::string winning_piece;
	int moves_played;
	int moves_remaining;
	int total_moves;
	int longest_string; 
public:
	GameBase();
	virtual ~GameBase();
	mutable std::vector<Game_Piece> pieces;
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;
	int prompt(unsigned int & x, unsigned int & y);
	int play(); 
	static std::shared_ptr<GameBase> game_function(int i, char * arr[]);
};

//Tic Tac Toe Game Class
class TicTacToeGame: public GameBase {
private:
	int width; 
	int height; 
	std::string piece_type;
	char current_player;
	std::string winning_piece;
	std::vector<std::pair<int, int>> player_x_moves;
	std::vector<std::pair<int, int>> player_o_moves;
	int moves_remaining;
	int moves_played;
public:
	TicTacToeGame();
	mutable std::vector<Game_Piece> pieces;
	friend std::ostream & operator <<(std::ostream & output, const TicTacToeGame & game);
	void print(); //overriden print function 
	virtual bool done(); 
	virtual bool draw(); 
	virtual int turn();
	//virtual bool quit();
};

//Gomoku Game Class
class GomokuGame : public GameBase {
private:
	int width;
	int height;
	std::string piece_type;
	char current_player;
	std::string winning_piece;
	std::vector<std::pair<int, int>> player_b_moves;
	std::vector<std::pair<int, int>> player_w_moves;
	mutable std::vector<Game_Piece> b_vect;
	mutable std::vector<Game_Piece> w_vect;
	int moves_remaining;
	int moves_played;
public:
	GomokuGame();
	void print(); 
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	friend std::ostream & operator <<(std::ostream & output, const GomokuGame & game);
	void fill_vectors();
};

#endif  /* GAME_h */
