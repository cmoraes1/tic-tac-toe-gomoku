// Camilla Moraes - camillamoraes@wustl.edu
// Lab 4
// File: Header.h
// Header file with all enums relating to program inforamtion (success and erorr values, program info) and 
// values used in Tic Tac Toe and Gomoku games (board dimensions, number of moves in game, valid piece coordinates, etc)

#pragma once

#ifndef HEADER_H
#define HEADER_H

//success and error values 
enum ErrorValues {
	Success, 
	InvalidNumberOfArguments,
	UserQuitGame,
	BadlyFormattedInput,
	ErrorExtractingCoordinates,
	BoardSpotFilled,
	GameOverWithoutWinner
};

//program info
enum Info {
	ProgramName,
	FileName,
	NumArguments
};

//info about Tic Tac Toe (board dimensions, important board indices, etc)
enum TicTacToeGameInfo {
	InitialMovesPlayed = 0,
	ZeroMovesRemaining = 0,
	LowerLimit = 1,
	UpperLimit = 3,
	TicTacToeBoardWidth = 5,
	TicTacToeBoardHeight = 5,
	TicTacToe_LeftDiagIndex = 6,
	TicTacToe_RightDiagIndex = 8,
	TicTacToeGameMoves = 9
};

//info about Gomoku (board dimensions, important board indices, etc)
enum GomokuGameInfo {
	InitialMoves = 0,
	GomokuBoardWidth = 20,
	GomokuBoardHeight = 20,
	GomokuGameMoves = 361,
	Gomoku_LeftDiagIndex = 21,
	Gomoku_RightDiagIndex = 39
};

//info about Game Base class 
enum GameInfo {
	GameBaseTotalGameMoves = 0,
	StringLength = 2,
	GameBaseMovesRemaining = 10 //arbitrary number - set to 9 or 361 once game starts depending on if user is playing TicTacToe or Gomoku
};

#endif /* HEADER_H */
