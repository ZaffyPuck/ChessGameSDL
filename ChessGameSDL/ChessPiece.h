#pragma once

enum class Color {
	White, 
	Black
};
enum class Type {
	Pawn, 
	Knight, 
	Bishop, 
	Rook, 
	Queen, 
	King
};

class ChessPiece {
private:
	Color color;
	Type type;
public:
	ChessPiece(Color color, Type type);
	ChessPiece();

	const Color getColor();
	const Type getType();

	void setColor(Color color);
	void setType(Type type);

	bool operator==(ChessPiece const& other) const;
	bool operator <(const ChessPiece& piece) const;
};