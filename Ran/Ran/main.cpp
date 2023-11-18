#include "consoleWindow.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int WINDOW_TOP = 5;
const int WINDOW_BOTTOM = 35;
const int WINDOW_LEFT = 1;
const int WINDOW_RIGHT = 80;
enum DIRECTION { RIGHT, LEFT, UP, DOWN };
struct HighScore {
	int score;
	string name;
};
struct TableHighScore
{
	int amount;
	HighScore people[5];
};
TableHighScore table;
struct Point
{
	int x;
	int y;
};
class Snake
{
public:
	Point snake[100];
	int length;
	char snakeType;
	Snake()
	{
		snakeType = 254;
		length = 3;
		snake[0].x = (WINDOW_RIGHT + WINDOW_LEFT) / 2 + 1;
		snake[1].x = (WINDOW_RIGHT + WINDOW_LEFT) / 2;
		snake[2].x = (WINDOW_RIGHT + WINDOW_LEFT) / 2 - 1;
		snake[0].y = snake[1].y = snake[2].y = (WINDOW_TOP + WINDOW_BOTTOM) / 2;
	}
	void setSnakeType(int type)
	{
		snakeType = char(type);
	}
	void drawSnake(Point lastSnake)
	{
		setTextColor(YELLOW_COLOR);
		for (int i = 0; i < length; i++)
		{
			gotoXY(snake[i].x, snake[i].y);
			cout << snakeType;
		}
		gotoXY(lastSnake.x, lastSnake.y);
		cout << " " << endl;
		setTextColor(WHITE_COLOR);
	}
	Point directionSnake(DIRECTION direction)
	{
		Point lastSnake = snake[length - 1];
		for (int i = length - 1; i >= 1; i--)
		{
			snake[i] = snake[i - 1];
		}
		switch (direction)
		{
		case RIGHT:
			snake[0].x++;
			break;
		case LEFT:
			snake[0].x--;
			break;
		case UP:
			snake[0].y--;
			break;
		case DOWN:
			snake[0].y++;
			break;
		}
		return lastSnake;
	}
	void getEvent(DIRECTION& direction)
	{
		int key = inputKey();
		if (key == 80)
		{
			if (direction != UP)
				direction = DOWN;
		}
		else if (key == 72)
		{
			if (direction != DOWN)
				direction = UP;
		}
		else if (key == 77)
		{
			if (direction != LEFT)
				direction = RIGHT;
		}
		else if (key == 75)
			if (direction != RIGHT)
				direction = LEFT;
	}
};

string player = "";
int score = 0;
int level = 1;
int speed = 1;
DIRECTION direction = RIGHT;
Snake ran;
Point food;

//Hàm nhập thông tin người chơi

int main()
{

}
