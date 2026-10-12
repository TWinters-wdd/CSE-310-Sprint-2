#pragma once

enum class PieceType
{
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn
};

enum class PieceColor
{
    White,
    Black
};

class Piece
{
    private:
        PieceType type;
        PieceColor color;

    public:
        Piece(PieceType pieceType, PieceColor pieceColor);

        PieceType GetType() const;
        PieceColor GetColor() const;

        bool CanMove(int startRow, int startColumn, int endRow, int endColumn) const;
};