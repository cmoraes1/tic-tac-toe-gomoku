// Camilla Moraes - camillamoraes@wustl.edu
// Lab 4
// File: Game_Piece.h
// Header file with information about game pieces 

#pragma once

#ifndef GAME_PIECE_H
#define GAME_PIECE_H
#include <istream>
#include <ostream>
#include <string>

struct Game_Piece {
	int x_coord;
	int y_coord;
	std::string piece_type;
};

#endif /* GAME_PIECE_ H*/