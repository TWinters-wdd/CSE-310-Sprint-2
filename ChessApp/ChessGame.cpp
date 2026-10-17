#include "ChessGame.h"
#include <cctype>
#include <iostream>

using namespace std;

// Creates a new chess game and prepares an initial board.
ChessGame::ChessGame()
    : board(BoardSize, vector<optional<Piece>>(BoardSize)),
      currentPlayer(PieceColor::White),
      gameOver(false)
{
    InitializeBoard();
}

void ChessGame::InitializeBoard()
{
    // Rebuild the board as an 8-by-8 collection of empty squares.
    // Each optional<Piece> is empty until a piece is placed on that square.
    board = vector<vector<optional<Piece>>>(
        BoardSize,
        vector<optional<Piece>>(BoardSize)
    );

    // Reset the parts of the game that can change during play.
    currentPlayer = PieceColor::White;
    gameOver = false;
    moveHistory.clear();

    // Rows 0 and 1 contain White's pieces.
    // Rows 6 and 7 contain Black's pieces.
    // The middle four rows remain empty at the start of the game.

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

    // Place the major pieces and pawns for both players.
    // The loop uses the same back-row arrangement for each color.
    for (int column = 0; column < BoardSize; column++)
    {
        board[0][column] =
            Piece(backRow[column], PieceColor::White);

        board[7][column] =
            Piece(backRow[column], PieceColor::Black);

        board[1][column] =
            Piece(PieceType::Pawn, PieceColor::White);

        board[6][column] =
            Piece(PieceType::Pawn, PieceColor::Black);
    }
}

void ChessGame::DisplayBoard() const
{
    /*
     * Displays the board from the current player's perspective.
     *
     * The board data itself is not changed. Instead, this function
     * changes the order in which rows and columns are printed.
     * White sees White's side at the bottom, while Black sees
     * Black's side at the bottom.
     */

    const bool viewingWhiteSide =
        currentPlayer == PieceColor::White;

    // Print the column labels across the top of the board.
    // The labels reverse when the board is viewed from Black's side.
    cout << "\n  ";

    for (int displayColumn = 0;
         displayColumn < BoardSize;
         displayColumn++)
    {
        int boardColumn;

        if (viewingWhiteSide)
        {
            boardColumn = displayColumn;
        }
        else
        {
            boardColumn = BoardSize - 1 - displayColumn;
        }

        cout << static_cast<char>('a' + boardColumn) << " ";
    }

    cout << "\n";

    // Print each displayed row from top to bottom.
    for (int displayRow = 0;
         displayRow < BoardSize;
         displayRow++)
    {
        int boardRow;

        // Convert the displayed row into the corresponding board row.
        if (viewingWhiteSide)
        {
            boardRow = BoardSize - 1 - displayRow;
        }
        else
        {
            boardRow = displayRow;
        }

        cout << boardRow + 1 << " ";

        // Print each square in the current displayed row.
        for (int displayColumn = 0;
             displayColumn < BoardSize;
             displayColumn++)
        {
            int boardColumn;

            // Convert the displayed column into the corresponding
            // column in the stored board.
            if (viewingWhiteSide)
            {
                boardColumn = displayColumn;
            }
            else
            {
                boardColumn = BoardSize - 1 - displayColumn;
            }

            // Empty squares are displayed as periods.
            if (!board[boardRow][boardColumn].has_value())
            {
                cout << ". ";
            }
            else
            {
                // Select a letter based on the piece's type.
                char symbol = '?';

                switch (board[boardRow][boardColumn]->GetType())
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

                // Display Black pieces as lowercase letters so the two
                // colors can be distinguished in the terminal.
                if (board[boardRow][boardColumn]->GetColor()
                    == PieceColor::Black)
                {
                    symbol = static_cast<char>(
                        tolower(static_cast<unsigned char>(symbol))
                    );
                }

                cout << symbol << " ";
            }
        }

        cout << boardRow + 1 << "\n";
    }

    // Print the column labels again below the board.
    cout << "  ";

    for (int displayColumn = 0;
         displayColumn < BoardSize;
         displayColumn++)
    {
        int boardColumn;

        if (viewingWhiteSide)
        {
            boardColumn = displayColumn;
        }
        else
        {
            boardColumn = BoardSize - 1 - displayColumn;
        }

        cout << static_cast<char>('a' + boardColumn) << " ";
    }

    cout << "\n";
}

bool ChessGame::IsLegalMove(int startRow, int startColumn,
                            int endRow, int endColumn)
{
    // First, make sure none of the coordinates are outside the board.
    if (startRow < 0 || startRow >= BoardSize ||
        startColumn < 0 || startColumn >= BoardSize ||
        endRow < 0 || endRow >= BoardSize ||
        endColumn < 0 || endColumn >= BoardSize)
    {
        return false;
    }

    // A move cannot begin from an empty square.
    if (!board[startRow][startColumn].has_value())
    {
        return false;
    }

    const Piece& movingPiece =
        board[startRow][startColumn].value();

    // The current player can only move pieces of their own color.
    if (movingPiece.GetColor() != currentPlayer)
    {
        return false;
    }

    // A piece cannot move onto a square occupied by a friendly piece.
    if (board[endRow][endColumn].has_value() &&
        board[endRow][endColumn]->GetColor() == currentPlayer)
    {
        return false;
    }

    // Ask the Piece object whether the movement pattern is valid.
    // Board-specific rules, such as blocked paths, can be added later.
    if (!movingPiece.CanMove(startRow, startColumn,
                             endRow, endColumn))
    {
        return false;
    }

    return true;
}

bool ChessGame::MakeMove(int startRow, int startColumn, int endRow, int endColumn)
{
    // Validate the move before changing any board data.
    if (!IsLegalMove(startRow, startColumn, endRow, endColumn))
    {
        return false;
    }

    // Copy the moving piece to the destination square.
    // If an opponent's piece is there, this also performs a capture.
    board[endRow][endColumn] = board[startRow][startColumn];

    // The original square is now empty.
    board[startRow][startColumn].reset();

    // Store a text description of the move for later display or file saving.
    string moveDescription =
        "(" + to_string(startRow) + ","
        + to_string(startColumn) + ") -> ("
        + to_string(endRow) + ","
        + to_string(endColumn) + ")";

    moveHistory.push_back(moveDescription);

    // Switch the turn after a successful move.
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
    // Report whether another part of the game has marked the game as over.
    return gameOver;
}
