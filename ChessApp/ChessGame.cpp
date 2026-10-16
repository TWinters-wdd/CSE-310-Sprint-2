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
    // Checks that all the coordinates given are inside the board
    if (startRow < 0 || startRow >= BoardSize || startColumn < 0 || startColumn >= BoardSize || endRow < 0 || endRow >= BoardSize || endColumn < 0 || endColumn >= BoardSize)
    {
        return false;
    }

    // Checks that the starting square contains a piece
    if (!board[startRow][startColumn].has_value())
    {
        return false;
    }

    const Piece& movingPiece = board[startRow][startColumn].value();

    // Prevent current player from moving the opponent's piece
    if (movingPiece.GetColor() != currentPlayer)
    {
        return false;
    }

    // Prevent piece from moving onto a square occupied by another piece of the same color.
    if (board[endRow][endColumn].has_value() && board[endRow][endColumn]->GetColor() == currentPlayer)
    {
        return false;
    }

    // Checks whether the movement pattern is valid.
    if (!movingPiece.CanMove(startRow, startColumn, endRow, endColumn))
    {
        return false;
    }

    return true;
}

bool ChessGame::MakeMove(int startRow, int startColumn, int endRow, int endColumn)
{
    // Check if the move the player wants to make is legal
    if (!IsLegalMove(startRow, startColumn, endRow, endColumn))
    {
        return false;
    }

    // Copies the piece from the starting square to the destination square and then empties the original square.
    board[endRow][endColumn] = board[startRow][startColumn];
    board[startRow][startColumn].reset();

    // Stores each move description in the following format: (1, 4) -> (3,4) where the first pair of numbers is the starting row and column and the last are the ending row and column.
    string moveDescription = "(" + to_string(startRow) + "," + to_string(startColumn) + ") -> (" + to_string(endRow) + "," + to_string(endColumn) + ")";

    // Adds the move to the move-history vector.
    moveHistory.push_back(moveDescription);

    // Switches the current player after a successful move
    if (currentPlayer == PieceColor::White)
    {
        currentPlayer = PieceColor::Black;
    }
    else
    {
        currentPlayer = PieceColor::White;
    }

    return true;
}

bool ChessGame::IsGameOver() const
{
    return gameOver;
}