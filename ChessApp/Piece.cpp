#include "Piece.h"

Piece::Piece(PieceType pieceType, PieceColor pieceColor) : type(pieceType), color(pieceColor)
{
}

PieceType Piece::GetType() const
{
    return type;
}

PieceColor Piece::GetColor() const
{
    return color;
}

bool Piece::CanMove(int startRow, int startColumn, int endRow, int endColumn) const
{
    // Movement rules will be added here later.
    return false;
}