#ifndef GAME_H_
#define GAME_H_

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include <string>
#include <vector>
#include <map>
#include <regex>
//#include "ChessPiece.h"
#include "Option.h"


using namespace std;

enum class MoveOutcome {
	PawnPromote,
	BlackWin,
	WhiteWin,
	InvalidMove,
	ValidMove,
	StaleMate
};

class Game {
private:
	vector<vector<Option<ChessPiece>>> board;
	vector<bool> haveRooksMoved;
	const unsigned short int boardSize = 8;
	vector<string> movesHistory;
	int moveCount = 0;
	Color turn = Color::White;
	const map<char, unsigned short int> letterPositions{ {'a',0},{'b',1},{'c',2},{'d',3},{'e',4},{'f',5},{'g',6},{'h',7} };
public:
	Game();

	//position is a actual chess board position like E3 (so position is like [a-hA-H][0-9])
	//return actual position in matrix of position (ex. get_actual_postion("E3") => (5,4) )
	const tuple<unsigned short int, unsigned short int> getActualPostion(string position);

	const vector< tuple<unsigned short int, unsigned short int>> getAllPossibleMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> checkCastles(Color color);

	void castle(Color color, bool big);

	const vector< tuple<unsigned short int, unsigned short int>> getAllCorrectMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> getAllBishopMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> getAllRookMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> getAllQueenMoves(const unsigned short int i, const unsigned short int j);

	const vector< tuple<unsigned short int, unsigned short int>> getMoves(const short int i, const short int j, const short int k, const short int l, const Color color);

	const bool historyHelper(const unsigned short int i, const unsigned short int j, const unsigned short int toi, const unsigned short int toj);

	const bool isKingInCheck(Color color);

	const bool noValidMoves(Color color);

	const bool hasKingMoved(Color color);

	const MoveOutcome promote(const short int i, const short int j, ChessPiece piece);

	const tuple<unsigned short int, unsigned short int> getPromotedPawnPositions();

	const tuple<unsigned short int, unsigned short int> getKingPosition(Color color);

	const bool ifEnPassant(const unsigned short int i, const unsigned short int j);

	const MoveOutcome move(tuple<unsigned short int, unsigned short int> from, tuple<unsigned short int, unsigned short int> to);

	const MoveOutcome endMove();

	void addHistory(const unsigned short int i, const unsigned short int j, const unsigned short int toi, const unsigned short int toj);

	~Game();

	const unsigned short int getSize() {
		return this->boardSize;
	}

	Option<ChessPiece> getSquare(unsigned short int i, unsigned short int j) {
		return this->board.at(i).at(j);
	}

};


#endif // !'GAME_H_'