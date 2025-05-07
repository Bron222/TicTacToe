#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <limits>

using namespace std;

//-------------------------FUNCTION PROTOTYPES----------------------------------
void clearScreen(); //clears the screen
int randomNumber(); //random # generator
void displayGame(); //fills 2D array and displays game board
void userPrompts(string&, string&); //get user & computer's name - variables passed by reference
void playerTurn(int&, int&); //sequence of player turn - pass variables row/col into this
void computerTurn(int&, int&); //sequence of computer's turn - pass variables row/col by reference
string winner(char[][3]); //determines winner or tie

//--------------------------GLOBAL DECLARATIONS---------------------------------
const int ROWS = 3; //# of rows in 2D array
const int COLS = 3; //# of columns in 2D array
char board[ROWS][COLS]; //2D array of game board
string name, computer, win; //holds user & computer's name and the winner/loser statement
int counter = 0; //to measure the # of turns
bool okay = false; //bool to determine if game is over
//-------------------------------------------------------------------------------

int main()
{
    //-------------------------MAIN'S HOUSEKEEPING---------------------------------

    unsigned int seed = time(0);  // pulls the integer time from the system at the time of program execution for random#generator
    srand(seed);  // sets the "starting" point within the random number table

    int row, col; //user board position input
    string playAgain; //user input for main's do-while loop
    //---------------------------------------------------------------------------

    do
    {
        //fills the array with '*'
        for (int i = 0; i < ROWS; i++)
        {
            for (int c = 0; c < COLS; c++)
            {
                board[i][c] = '*';
            }
        }
        //---------SET UP--------------
        clearScreen();
        displayGame();
        userPrompts(name, computer);
        clearScreen();
        displayGame();
        //-----------------------------

        //==========PLAY===================
        playerTurn(row, col); //turn 1
        clearScreen();
        displayGame();
        computerTurn(row, col); //turn 2
        clearScreen();
        displayGame();

        playerTurn(row, col); //turn 3
        clearScreen();
        displayGame();
        computerTurn(row, col); //turn 4
        clearScreen();
        displayGame();

    while(okay ==false)
    {

        playerTurn(row, col); //turn 5, winner function called after each play to determine winner or tie, rest of turn are inside loop
        clearScreen();
        displayGame();
        win = winner(board);
        if (okay)
        {
            cout << win;
        }
        if (okay ==false)
        {

            computerTurn(row, col); //turn 6
            clearScreen();
            displayGame();
            win = winner(board);
            if (okay)
            {
                cout << win;
            }
        }
    }
    cout << "Play again? Type \"yes\" or \"no\"\n\n";
    cin >> playAgain;
    while (playAgain != "no" && playAgain != "yes")
    {
        cout << "\n\nInvalid input. Type \"yes\" or \"no\"\n\n";
        cin >> playAgain;
    }
    } while (playAgain == "yes");

    return 0;
}
//=========================FUNTION DEFINITIONS==================================
//==============================================================================
void clearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
//==============================================================================
//==============================================================================
int randomNumber(int) //random number generator
{
    const int MIN = 0;   // the minimum random number to calculate, can be set to any int value lower than MAX
    const int MAX = 2;   // the maximum random number to calculate

    int randomNum;  // to hold the a random number


    //Calculate two random numbers between MIN and MAX, inclusive
    randomNum = (rand() % (MAX - MIN + 1)) + MIN;

    return randomNum;
    //randomNum will now hold a random number and return to call
}
//==============================================================================
//==============================================================================
void displayGame()
{
    //game display and user prompts
    cout << "WELCOME TO TIC-TAC-TOE!\n"
        << "=======================\n"
        << "  Player vs. Computer\n\n";

    cout << setw(7) << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "     -----------\n";
    cout << setw(7) << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "     -----------\n";
    cout << setw(7) << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n\n";
}
//==============================================================================
//==============================================================================
void userPrompts(string& name, string& computer)
{
    cout << "\nPlease enter a name for Player 1: ";
    getline(cin, name);
    cout << "\nPlease enter a name for the Computer: ";
    getline(cin, computer);
    cout << endl;
}
//==============================================================================
//==============================================================================
void playerTurn(int& row, int& col)
{
    // player1 turn
    do
    {
        row = 0;
        col = 0;
        cout << name << ", enter the number for the row followed by the number for column to place the \"X\" in that position.\n";

        //---- ROW INPUT ----
        while (true)
        {
            cout << "\nEnter the row (1-3): ";
            if (cin >> row && row >= 1 && row <= 3)
            {
                --row; // Adjust for 0-based indexing
                break; // Good input
            }
            else
            {
                cout << "Invalid input. Please enter an integer between 1 and 3.\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            }
        }

        // ---- COLUMN INPUT ----
        while (true)
        {
            cout << "\nEnter the column (1-3): ";
            if (cin >> col && col >= 1 && col <= 3)
            {
                --col; // Adjust for 0-based indexing
                break; // Good input
            }
            else
            {
                cout << "Invalid input. Please enter an integer between 1 and 3.\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            }
        }

        if (board[row][col] == 'X' || board[row][col] == 'O')
        {
            clearScreen();
            displayGame();
            cout << "Try again! That spot has already been chosen.\n\n";
        }
    } while (board[row][col] == 'X' || board[row][col] == 'O');

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean up any extra input
    cout << "\n\n";
    board[row][col] = 'X';
    counter++;
    row = 0;
    col = 0;

}
//==================================================================================
//==================================================================================
void computerTurn(int& row, int& col)
{
    cout << "\nPress Enter to let " << computer << " have a turn.\n\n";
    cin.get();
    do
    {
        row = randomNumber(row);
        col = randomNumber(col);

    } while (board[row][col] == 'X' || board[row][col] == 'O');

    board[row][col] = 'O';
    counter++;
    row = 0;
    col = 0;
}
//====================================================================================
//====================================================================================
string winner(char board[][3])
{
    string result0 = "\n";
    string result1 = "\n\nCongratulations! YOU WON!\n\n\n\n";
    string result2 = "\n\nSorry, you lost!\n\n\n\n";
    string result3 = "\n\nIT'S A TIE!\n\n\n\n";

    char z = 'X'; //for player1 to win

    //row for win

    if (board[0][0] == z && board[0][1] == z && board[0][2] == z) //row 1
    {
        okay = true;
        return result1;
    }
    else if (board[1][0] == z && board[1][1] == z && board[1][2] == z) //row 2
    {
        okay = true;
        return result1;
    }

    else if (board[2][0] == z && board[2][1] == z && board[2][2] == z) //row 3
    {
        okay = true;
        return result1;
    }

    //columns for win

    else if (board[0][0] == z && board[1][0] == z && board[2][0] == z) //column 1
    {
        okay = true;
        return result1;
    }

    else if (board[0][1] == z && board[1][1] == z && board[2][1] == z) //column 2
    {
        okay = true;
        return result1;
    }

    else if (board[0][2] == z && board[1][2] == z && board[2][2] == z) //column 3
    {
        okay = true;
        return result1;
    }

    //diagonals for win
    else if (board[0][0] == z && board[1][1] == z && board[2][2] == z) //diagonal L > R
    {
        okay = true;
        return result1;
    }

    else if (board[0][2] == z && board[1][1] == z && board[2][0] == z) //diagonal R > L
    {
        okay = true;
        return result1;
    }

    //-----------------------------------------------------------------------------------------

    z = 'O'; //for computer to win

    //row for win

    if (board[0][0] == z && board[0][1] == z && board[0][2] == z) //row 1
    {
        okay = true;
        return result2;
    }

    else if (board[1][0] == z && board[1][1] == z && board[1][2] == z) //row 2
    {
        okay = true;
        return result2;
    }

    else if (board[2][0] == z && board[2][1] == z && board[2][2] == z) //row 3
    {
        okay = true;
        return result2;
    }

    //columns for win

    else if (board[0][0] == z && board[1][0] == z && board[2][0] == z) //column 1
    {
        okay = true;
        return result2;
    }

    else if (board[0][1] == z && board[1][1] == z && board[2][1] == z) //column 2
    {
        okay = true;
        return result2;
    }

    else if (board[0][2] == z && board[1][2] == z && board[2][2] == z) //column 3
    {
        okay = true;
        return result2;
    }

    //diagonals for win
    else if (board[0][0] == z && board[1][1] == z && board[2][2] == z) //diagonal L > R
    {
        okay = true;
        return result2;
    }

    else if (board[0][2] == z && board[1][1] == z && board[2][0] == z) //diagonal R > L
    {
        okay = true;
        return result2;
    }

    if (counter == 9)
    {
        okay = true;
        return result3;
    }
    return result0;
}
