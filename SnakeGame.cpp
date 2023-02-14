/*
Snake Game Created By: Ilyaas Mohamed
Student ID: 108985201
*/
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h> 
#include <fstream>
using namespace std;
int gameOver = 0;
int score = 0;
string name;
    int width = 20;
    int height = 20;
    int x, y, FoodX, FoodY;
    int tailX[100], tailY[100];
    int nTail;
    enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirecton dir;

void Start()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    FoodX = rand() % width;
    FoodY = rand() % height;
    score = 0;
}
void Map()
{
    system("cls");
    cout << endl;
    cout << " ";
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << " |";
            if (i == y && j == x)
                cout << "O";
            else if (i == FoodY && j == FoodX)
                cout << "X";
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

            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }

    cout << " ";
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;
    cout << " Score : " << score<<"\t*X = 10*" << endl;
    cout << " Player: " << name << endl;
}
void movement()
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
            gameOver = true;
            break;
        default:
            break;
        }
    }
}
void tail()
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
    if (x > width || x < 0 || y > height || y < 0)//Demo here in presentation
        gameOver = true;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == FoodX && y == FoodY)
    {
        srand(time(0));
        score += 10;
        FoodX = rand() % width;
        FoodY = rand() % height;
        nTail++;
    }
}
void writeScores(string fileName) {
    ofstream outFile;
    outFile.open(fileName,ios::app);
    if (!outFile)
        cout << "File cannot be opened." << endl;
    else {
        outFile << "----------------------------------" << endl;
        outFile << "\t" << "Name" << "\t" << "Score" << endl;
        outFile << "\t" << name << "\t\t" << score << endl; 
        outFile << "----------------------------------" << endl;
    }
    outFile.close();
}
int main()
{
    cout << "Enter Name to the Database" << name << endl;
    cin >> name;
    system("pause");
    Start();
    while (!gameOver)
    {
        Map();
        movement();
        tail();
        Sleep(10);
    }
    writeScores("Scores.txt");
    if (gameOver == 1) {
        system("cls");
        cout << "Game Over...All Scores are stored in Scores.txt"<<endl<<"THANKS FOR PLAYING" << endl;
        system("pause");
    }
    return 0;
}