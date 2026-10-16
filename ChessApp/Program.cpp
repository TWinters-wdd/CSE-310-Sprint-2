#include "ChessGame.h"
#include <cctype>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    ChessGame game;

    // Continue displaying the board and accepting moves until the game ends.
    while (!game.IsGameOver())
    {
        game.DisplayBoard();

        cout << "Enter your move as: start column, start row, "
                "end column, end row\n";
        cout << "Example: e 2 e 4\n";
        cout << "Enter q to quit: ";

        char startColumn;
        int startRow;
        char endColumn;
        int endRow;

        // Read the starting column first so the user can quit with just 'q'.
        cin >> startColumn;

        if (tolower(static_cast<unsigned char>(startColumn)) == 'q')
        {
            cout << "Game ended.\n";
            break;
        }

        // Read the remaining three values for the move.
        if (!(cin >> startRow >> endColumn >> endRow))
        {
            cout << "Invalid input. Use a format such as: e 2 e 4\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Convert uppercase column letters to lowercase.
        startColumn = static_cast<char>(
            tolower(static_cast<unsigned char>(startColumn)));

        endColumn = static_cast<char>(
            tolower(static_cast<unsigned char>(endColumn)));

        // Confirm that both columns are valid chess columns.
        if (startColumn < 'a' || startColumn > 'h' || endColumn < 'a' || endColumn > 'h')
        {
            cout << "Invalid column. Use a through h.\n";
            continue;
        }

        // Confirm that both rows are valid chess rows.
        if (startRow < 1 || startRow > 8 || endRow < 1 || endRow > 8)
        {
            cout << "Invalid row. Use numbers 1 through 8.\n";
            continue;
        }

        // Convert user-friendly coordinates into 0-based board indexes.
        startRow--;
        endRow--;

        int startColumnIndex = startColumn - 'a';
        int endColumnIndex = endColumn - 'a';

        if (game.MakeMove(startRow, startColumnIndex,
                          endRow, endColumnIndex))
        {
            cout << "Move succeeded.\n";
        }
        else
        {
            cout << "Invalid move. Try again.\n";
        }
    }

    // Show the final board before the program exits.
    game.DisplayBoard();
        
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
