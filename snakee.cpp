
// snake game in console using c++
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
#define rep(i,x,y) for(int i=x; i<y; i++)
bool isgameOver; // stste of game
const int widthofboard = 20; // for snake board
const int heightofboard = 20;
int x, y, xfruit, yfruit, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};//possible direction
eDirecton dir;
void Setup()
{
    isgameOver = false;
    dir = STOP;
    x = widthofboard / 2;
    y = heightofboard / 2;
    xfruit = rand() % widthofboard;
    yfruit = rand() % heightofboard;
    score = 0;
}
void Draw()
{
    system("cls"); 
    rep(i,0, widthofboard + 2)
        cout << "#";
    cout << endl;

    for (int i = 0; i < heightofboard; i++)
    {
        for (int j = 0; j < widthofboard; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == yfruit && j == xfruit)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == widthofboard - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < widthofboard + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit())

    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            isgameOver = true;
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //if (x > widthofboard || x < 0 || y > heightofboard || y < 0)
    //  isgameOver = true;
    if (x >= widthofboard) x = 0; else if (x < 0) x = widthofboard - 1;
    if (y >= heightofboard) y = 0; else if (y < 0) y = heightofboard - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            isgameOver = true;

    if (x == xfruit && y == yfruit)
    {
        score += 10;
        xfruit = rand() % widthofboard;
        yfruit = rand() % heightofboard;
        nTail++;
    }
}
int main()
{
    Setup();
    while (!isgameOver)
    {
        Draw();
        Input();
        Logic();
        // Sleep(10); 
    }
    return 0;
}