#pragma once

#include "Piece.h"
#include <optional>
#include <string>
#include <vector>

class ChessGame
{
    private:
        static constexpr int BoardSize = 8;

        std::vector<std::vector<std::optional<Piece>>> board;
        PieceColor currentPlayer;
        bool gameOver;
        std::vector<std::string> moveHistory;

    public:
        ChessGame();

        void InitializeBoard();

        void DisplayBoard() const;

        bool IsLegalMove(int startRow, int startColumn, int endRow, int endColumn);

        bool MakeMove(int startRow, int startColumn, int endRow, int endColumn);

        bool IsGameOver() const;

        void SaveGameToFile(const std::string& fileName) const;
};
