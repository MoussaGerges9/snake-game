#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
using namespace std;

int width, hight, fruitX, fruitY, snakX, snakY, tail, tailX[100], tailY[100], score;
bool lose;
enum direction { Top = 1, Down, Right, Left };
direction dir;


void shift(int arr[], int size)
{
	for (int i = size - 2; i >= 0; i--)
	{
		arr[i + 1] = arr[i];
	}
}


void frutt()
{
	width = 60;
	hight = 25;
	srand(time(NULL));
	fruitX = rand() % (width - 2) + 1;
	fruitY = rand() % (hight - 2) + 1;
}


void setup()
{
	frutt();
	snakX = width / 2;
	snakY = hight / 2;
	tail = 0;
	score = 0;
	lose = false;
}


void draw()
{
	system("cls");
	for (int y = 0; y < hight; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (y == 0 || y == hight - 1)
				cout << "*";
			else if (x == 0 || x == width - 1)
				cout << "*";
			else if (y == snakY && x == snakX)
				cout << "@";
			else if (y == fruitY && x == fruitX)
				cout << "$";
			else
			{
				bool prtail = false;
				for (int z = 0; z < tail; z++)
				{
					if (tailX[z] == x && tailY[z] == y)
					{
						cout << "o";
						prtail = true;
						break;
					}
				}
				if (!prtail)
					cout << " ";
			}

		}
		cout << endl;
	}
	cout << "Player score: " << score << endl;
}


void input()
{
	if (_kbhit())
	{
		char c = _getch();
		switch (c)
		{
		case 'w': dir = Top; break;
		case 's': dir = Down; break;
		case 'd': dir = Right; break;
		case 'a': dir = Left; break;
		case 'x': exit(0);
		}
	}
}


void move()
{
	shift(tailX, 100);
	shift(tailY, 100);
	tailX[0] = snakX;
	tailY[0] = snakY;
	switch (dir)
	{
	case Top:
		snakY--;
		break;
	case Down:
		snakY++;
		break;
	case Right:
		snakX++;
		break;
	case Left:
		snakX--;
		break;
	}
	if (snakY >= hight || snakY <= 0 || snakX >= width || snakX <= 0)
		lose = true;

	for (int i = 0; i < tail; i++)
	{
		if (snakX == tailX[i] && snakY == tailY[i])
			lose = true;
	}

	if (snakX == fruitX && snakY == fruitY)
	{
		frutt();
		score++;
		tail++;
	}

}


int main()
{
	setup();
	while (!lose)
	{
		draw();
		input();
		move();
	}
	system("pause");
	return 0;
}