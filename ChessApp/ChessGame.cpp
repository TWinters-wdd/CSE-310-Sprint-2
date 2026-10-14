#include "ChessGame.h"
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