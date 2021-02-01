#include <iostream>
#include <string>

using namespace std;

bool gameover = false;
string winner;
const int WIDTH = 7;
const int HEIGHT = 6;
int board[HEIGHT][WIDTH];
int turn = 1;
int in;
const string left_padding = "      ";

void reset()
{
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            board[row][col] = 0;
        }
    }
}

void display()
{
    system("cls");
    cout << endl << endl;
    cout << left_padding << "player: " << turn << endl << endl;
    cout << left_padding;
    for (int i = 0; i < WIDTH; i++)
    {
        cout << i << "   ";
    }
    cout << endl;
    for (int row = 0; row < HEIGHT; row++)
    {
        cout << "    | ";
        for (int col = 0; col < WIDTH; col++)
        {
            cout << board[row][col] << " | ";
        }
        cout << endl;
    }
    cout << endl;
}

bool four_in_a_row_right(int row, int col)
{
    int first = board[row][col];
    if (first == 0)
        return false;
    if (first != board[row][col+1])
        return false;
    if (first != board[row][col+2])
        return false;
    if (first != board[row][col+3])
        return false;
    return true;
}
bool four_in_a_row_down(int row, int col)
{
    int first = board[row][col];
    if (first == 0)
        return false;
    if (first != board[row+1][col])
        return false;
    if (first != board[row+2][col])
        return false;
    if (first != board[row+3][col])
        return false;
    return true;
}
bool four_in_a_row_down_right(int row, int col)
{
    int first = board[row][col];
    if (first == 0)
        return false;
    if (first != board[row+1][col+1])
        return false;
    if (first != board[row+2][col+2])
        return false;
    if (first != board[row+3][col+3])
        return false;

    return true;
}
bool four_in_a_row_up_right(int row, int col)
{
    int first = board[row][col];
    if (first == 0)
        return false;
    if (first != board[row-1][col+1])
        return false;
    if (first != board[row-2][col+2])
        return false;
    if (first != board[row-3][col+3])
        return false;
    return true;
}
bool four_in_a_row()
{
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH-3; col++)
        {
            if (four_in_a_row_right(row, col))
                return true;
        }
    }
    for (int row = 0; row < HEIGHT-3; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            if (four_in_a_row_down(row, col))
                return true;
        }
    }
    for (int row = 0; row < HEIGHT-3; row++)
    {
        for (int col = 0; col < WIDTH-3; col++)
        {
            if (four_in_a_row_down_right(row, col))
                return true;
        }
    }
    for (int row = HEIGHT-3; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH-3; col++)
        {
            if (four_in_a_row_up_right(row, col))
                return true;
        }
    }

    return false;
}
bool board_full()
{
    for (int col = 0; col < WIDTH; col++)
    {
        if (board[0][col] == 0)
            return false;
    }
    return true;
}
void input()
{
    while (true)
    {
        cout << left_padding << "Enter column: ";
        cin >> in;
        if (in < 0 || in > (WIDTH-1))
            cout << left_padding << "Input must be between 0 and " << WIDTH-1 << " inclusive" << endl;
        else  if (cin.fail())
        {
         cout << left_padding << "ERROR -- You did not enter an integer" << endl;
         // get rid of failure state
         cin.clear();
         // discard 'bad' character(s)
         cin.ignore(256, '\n');

        }
        else if (board[0][in] != 0)
            cout << left_padding << "Column full" << endl;

        else
            break;


    }
}

void logic()
{

    int row = 0;
    while (board[row+1][in] == 0 && row < HEIGHT-1)
    {
        row++;
    }
    board[row][in] = turn;

    if (four_in_a_row())
    {
        gameover = true;
        switch(turn)
        {
        case 1:
            winner = "1";
            break;
        case 2:
            winner = "2";
            break;
        }
        return;
    }

    if (board_full())
    {
        gameover = true;
        winner = "tie!";
        return;
    }

    if (turn == 1)
        turn = 2;
    else
        turn = 1;
}

int main()
{
    while (!gameover)
    {
        display();
        input();
        logic();
    }
    display();
    cout << "Game over. Winner: " << winner;
    return 0;
}
