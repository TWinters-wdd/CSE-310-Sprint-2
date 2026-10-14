#include "Piece.h"
#include <cstdlib>

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
    int rowDifference = endRow - startRow;
    int columnDifference = endColumn - startColumn;

    int absoluteRowDifference = std::abs(rowDifference);
    int absoluteColumnDifference = std::abs(columnDifference);

    if (rowDifference == 0 && columnDifference == 0)
    {
        return false;
    }

    switch (type)
    {
        case PieceType::King:
            return absoluteRowDifference <= 1 && absoluteColumnDifference <= 1;

        case PieceType::Rook:
            return rowDifference == 0 || columnDifference == 0;

        case PieceType::Bishop:
            return absoluteRowDifference == absoluteColumnDifference;

        case PieceType::Queen:
            return rowDifference == 0 || columnDifference == 0 || absoluteRowDifference == absoluteColumnDifference;

        case PieceType::Knight:
            return (absoluteRowDifference == 2 && absoluteColumnDifference == 1) || (absoluteRowDifference == 1 && absoluteColumnDifference == 2);

        case PieceType::Pawn:
        {
            int direction;

            if (color == PieceColor::White)
            {
                direction = 1;
            }
            else
            {
                direction = -1;
            }

            if (columnDifference == 0 && rowDifference == direction)
            {
                return true;
            }

            if (columnDifference == 0 && rowDifference == 2 * direction && startRow == (color == PieceColor::White ? 1 : 6))
            {
                return true;
            }

            return false;
        }
    }

    return false;
}