#include "ChessGame.h"
#include <cctype>
#include <iostream>

using namespace std;

ChessGame::ChessGame() : board(BoardSize, vector<optional<Piece>>(BoardSize)), currentPlayer(PieceColor::White), gameOver(false)
{
    InitializeBoard();
}

void ChessGame::InitializeBoard()
{
    board = vector<vector<optional<Piece>>>(
        BoardSize,
        vector<optional<Piece>>(BoardSize)
    );

    currentPlayer = PieceColor::White;
    gameOver = false;
    moveHistory.clear();

    // Rows [0 - 1] in Vector are White's pieces
    // Rows [6 - 7] in Vector are Black's pieces

    vector<PieceType> backRow =
    {
        PieceType::Rook,
        PieceType::Knight,
        PieceType::Bishop,
        PieceType::Queen,
        PieceType::King,
        PieceType::Bishop,
        PieceType::Knight,
        PieceType::Rook
    };
    
    // Place the pieces on the board
    for (int column = 0; column < BoardSize; column++)
    {
        board[0][column] = Piece(backRow[column], PieceColor::White);
        board[7][column] = Piece(backRow[column], PieceColor::Black);

        board[1][column] = Piece(PieceType::Pawn, PieceColor::White);
        board[6][column] = Piece(PieceType::Pawn, PieceColor::Black);
    }
}

void ChessGame::DisplayBoard() const
{

    /*This function prints a chessboard display to the terminal.
     * White pieces are displayed with capital letters.
     * Black pieces are displayed with lowercase letters.
    */

    cout << "\n  a b c d e f g h\n";

    for (int row = BoardSize - 1; row >= 0; row--)
    {
        cout << row + 1 << " ";

        for (int column = 0; column < BoardSize; column++)
        {
            if (!board[row][column].has_value())
            {
                cout << ". ";
            }
            else
            {
                char symbol;

                switch (board[row][column]->GetType())
                {
                    case PieceType::King:
                        symbol = 'K';
                        break;

                    case PieceType::Queen:
                        symbol = 'Q';
                        break;
                    
                    case PieceType::Rook:
                        symbol = 'R';
                        break;

                    case PieceType::Bishop:
                        symbol = 'B';
                        break;

                    case PieceType::Knight:
                        symbol = 'N';
                        break;

                    case PieceType::Pawn:
                        symbol = 'P';
                        break;
                }

                if (board[row][column]->GetColor() == PieceColor::Black)
                {
                    symbol = static_cast<char>(tolower(symbol));
                }

                cout << symbol << " ";
            }
        }
        cout << row + 1 << "\n";
    }

    cout << "  a b c d e f g h\n";
}

bool ChessGame::IsLegalMove(int startRow, int startColumn, int endRow, int endColumn)
{
    if (startRow < 0 || startRow >= BoardSize || startColumn < 0 || startColumn >= BoardSize || endRow < 0 || endRow >= BoardSize || endColumn < 0 || endColumn >= BoardSize)
    {
        return false;
    }

    if (!board[startRow][startColumn].has_value())
    {
        return false;
    }

    const Piece& movingPiece = board[startRow][startColumn].value();

    if (movingPiece.GetColor() != currentPlayer)
    {
        return false;
    }

    if (board[endRow][endColumn].has_value() && board[endRow][endColumn]->GetColor() == currentPlayer)
    {
        return false;
    }

    if (!movingPiece.CanMove(startRow, startColumn, endRow, endColumn))
    {
        return false;
    }

    return true;
}