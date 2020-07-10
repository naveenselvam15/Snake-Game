#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<cstdlib>
#include<list> 

using namespace std;

enum SnakeDir { 
	STOP, LEFT, RIGHT, UP, DOWN
};

struct coordinate
{
	int x;
	int y;
};

class GameBoard
{

private:

	int height;
	int width;
	bool** gameBoard;
	bool isGameOver;
	int fruitX;
	int fruitY;
	int snakeHeadX;
	int snakeHeadY;
	SnakeDir snakeDir = STOP;
	list<coordinate> snake;

public:

	GameBoard(int height = 20, int width = 20)
	{
		this->height = height;
		this->width = width;
		this->isGameOver = false;
		gameBoard = new bool* [height];

		for (int i = 0; i < height; i++)
			gameBoard[i] = new bool[width];

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				gameBoard[i][j] = false;

		snakeHeadX = rand() % height;
		snakeHeadY = rand() % width;
		snake.push_front({ snakeHeadX, snakeHeadY });
		gameBoard[snakeHeadX][snakeHeadY] = true;

		do
		{
			fruitX = rand() % height;
			fruitY = rand() % width;
		} while (gameBoard[fruitX][fruitY]);

	}

	~GameBoard()
	{
		for (int i = 0; i < height; i++)
			delete[] gameBoard[i];

		delete[] gameBoard;

	}

	bool isSnakeGameOver()
	{
		return isGameOver;
	}

	void input()
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'a':
				if(snakeDir != RIGHT || snake.size() == 1 )
					snakeDir = LEFT;
				break;
			case 'd':
				if (snakeDir != LEFT || snake.size() == 1)
					snakeDir = RIGHT;
				break;
			case 'w':
				if (snakeDir != DOWN || snake.size() == 1)
					snakeDir = UP;
				break;
			case 's':
				if (snakeDir != UP || snake.size() == 1)
					snakeDir = DOWN;
				break;
			case 'c': isGameOver = true;
				break;
			}
		}
	}

	void logic()
	{
		if (snakeDir == STOP)
			return;

		if (snakeDir == UP)
			snakeHeadX--;
		else if (snakeDir == DOWN)
			snakeHeadX++;
		else if (snakeDir == LEFT)
			snakeHeadY--;
		else
			snakeHeadY++;

		if (snakeHeadX < 0 || snakeHeadX>=height || snakeHeadY < 0 || snakeHeadY>=width)
		{
			isGameOver = true;
		}

		else if (snakeHeadX == fruitX && snakeHeadY == fruitY)
		{
			gameBoard[snakeHeadX][snakeHeadY] = true;
			snake.push_back({ snakeHeadX, snakeHeadY });
			do
			{
				fruitX = rand() % height;
				fruitY = rand() % width;
			} while (gameBoard[fruitX][fruitY]);
		}
		else if (gameBoard[snakeHeadX][snakeHeadY] == true)
		{
			isGameOver = true;
		}
		else
		{
			gameBoard[snakeHeadX][snakeHeadY] = true;
			snake.push_back({ snakeHeadX, snakeHeadY });

			gameBoard[snake.front().x][snake.front().y] = false;
			snake.pop_front();
		}
	}

	void print()
	{

		system("cls");
		for (int i = 0; i < width + 2; i++)
			printf("#");
		printf("\n");
		for (int i = 0; i < height; i++)
		{
			printf("#");
			for (int j = 0; j < width; j++)
			{
				if (i == fruitX && j == fruitY)
					printf("o");
				else if (gameBoard[i][j])
					printf("+");
				else
					printf(" ");
			}
			printf("#");
			printf("\n");
		}
		for (int i = 0; i < width + 2; i++)
			printf("#");
	}

	
	
};

int main()
{

	GameBoard *snakeGame = new GameBoard();

	while (!(snakeGame->isSnakeGameOver()))
	{
		snakeGame->input();
		snakeGame->logic();
		snakeGame->print();
	}

	return 0;
}