#include "consoleWindow.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
//Nguyệt
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

//Trần

//Hàm hiển thị tên game
void showNameGame()
{
	setTextColor(WHITE_COLOR);
	gotoXY(1, 0);
	for (int i = WINDOW_LEFT; i <= WINDOW_RIGHT; i++)
		cout << char(220);

	for (int i = 1; i < WINDOW_TOP; i++)
	{
		gotoXY(1, i); cout << char(221);
	}
	for (int i = 1; i < WINDOW_TOP; i++)
	{
		gotoXY(WINDOW_RIGHT, i); cout << char(222);
	}
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, 1);  cout << " ___     _     _        ____     _     _        _    _  ____";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, 2); cout << "|   \\   / \\   | \\  |   |        / \\   | \\  |   | \\  / ||    ||";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, 3); cout << "|___/  /___\\  |  \\ |    ----   /___\\  |  \\ |   |  \\/  ||    ||";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, 4); cout << "|   \\ /     \\ |   \\|    ____| /     \\ |   \\|   |      ||____||";
}

//Hàm khởi tạo kích thước cửa sổ console
void setWindowGame()
{
	gotoXY(WINDOW_LEFT, WINDOW_TOP);
	for (int i = 0; i < WINDOW_RIGHT; i++)
	{
		cout << char(220);
	}
	for (int i = 0; i < WINDOW_BOTTOM - 5; i++)
	{
		gotoXY(WINDOW_LEFT, WINDOW_TOP + i);
		cout << char(221) << endl;
	}
	gotoXY(WINDOW_LEFT, WINDOW_BOTTOM);
	for (int i = 0; i < WINDOW_RIGHT; i++)
	{
		cout << char(223);
	}
	for (int i = 0; i < WINDOW_BOTTOM - 5; i++)
	{
		gotoXY(WINDOW_RIGHT, WINDOW_TOP + i);
		cout << char(222) << endl;
	}

}
//Hàm kiểm tra rắn có chạm tường hay tự cắn không
bool checkGame()
{
	//Kiểm tra chạm biên
	if (ran.snake[0].y == WINDOW_TOP)
		return true;
	if (ran.snake[0].y == WINDOW_BOTTOM)
		return true;
	if (ran.snake[0].x == WINDOW_LEFT)
		return true;
	if (ran.snake[0].x == WINDOW_RIGHT)
		return true;
	for (int i = 3; i < ran.length; i++)
		if ((ran.snake[0].x == ran.snake[i].x) && (ran.snake[0].y == ran.snake[i].y))
			return true;
	return false;
}

//Hàm kết thúc game
void gameOver()
{
	showNameGame();
	int key = inputKey();
	while (key != 13)
	{
		key = inputKey();
		setTextColor(CYAN_COLOR);
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "|          YOUR SCORE           |";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|               " << score;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 0); cout << "---------------------------------";
		Sleep(100);
		setTextColor(YELLOW_COLOR);
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "|          YOUR SCORE           |";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|               " << score;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 0); cout << "---------------------------------";
		Sleep(100);


	}
	setTextColor(WHITE_COLOR);
	clrscr();
	setWindowGame();
	showNameGame();
	setTextColor(YELLOW_COLOR);
	key = 11;
	while (key != 13)
	{
		key = inputKey();
		setTextColor(YELLOW_COLOR);
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << " _____      __     _    _  _____   _____           _____  ____" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|     |    /  \\   | \\  / ||       |     |\\       /|      |    \\" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2); cout << "|   ____  /____\\  |  \\/  ||_____  |     | \\     / |_____ |  __/" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "|     |  /      \\ |      ||       |     |  \\   /  |      |  \\" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "|_____| /        \\|      ||_____  |_____|   \\_/   |_____ |   \\" << endl;
		Sleep(100);
		setTextColor(CYAN_COLOR);
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << " _____      __     _    _  _____   _____           _____  ____" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|     |    /  \\   | \\  / ||       |     |\\       /|      |    \\" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2); cout << "|   ____  /____\\  |  \\/  ||_____  |     | \\     / |_____ |  __/" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "|     |  /      \\ |      ||       |     |  \\   /  |      |  \\" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 30, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "|_____| /        \\|      ||_____  |_____|   \\_/   |_____ |   \\" << endl;
		Sleep(100);
	}
	key = KEY_NONE;
	setTextColor(WHITE_COLOR);
	clrscr();
	setWindowGame();
	showNameGame();
	showHighScore();
	while (key != 13)
	{
		key = inputKey();
	}
	clrscr();
}
//Hàm bắt đầu lại-----Quang
void restartGame()
{
	ran.snakeType = 254;
	ran.length = 3;
	ran.snake[0].x = (WINDOW_RIGHT + WINDOW_LEFT) / 2 + 1;
	ran.snake[1].x = (WINDOW_RIGHT + WINDOW_LEFT) / 2;
	ran.snake[2].x = (WINDOW_RIGHT + WINDOW_LEFT) / 2 - 1;
	ran.snake[0].y = ran.snake[1].y = ran.snake[2].y = (WINDOW_TOP + WINDOW_BOTTOM) / 2;
	score = 0;
	level = 1;
	speed = 1;
	player = "";
}
//Hàm Hướng dẫn chơi game-----Quang
void howToPlay()
{
	clrscr();
	setWindowGame();
	showNameGame();
	int key = inputKey();
	while (key != 13)
	{
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "_____________________________________";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "| __________________________________ |";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "||                                  ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "||           HOW TO PLAY            ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "||          -------------           ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|| You move to eat food, for each   ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "||  food you will get one point.    ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "||  If you touch the wall or touch  ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "||     yourself then YOU LOSE!!     ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "||    If you get 100 points then    ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "||            YOU WIN!!             ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "||__________________________________||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 6); cout << "|____________________________________|";
		key = inputKey();

	}
	key = 11;
	while (key != 13)
	{
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "_____________________________________";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "| __________________________________ |";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "||                                  ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "||           HOW TO PLAY            ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "||          -------------           ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "||    RIGHT KEY   :    MOVE RIGHT   ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "||    LEFT KEY    :    MOVE LEFT    ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "||    UP KEY      :    MOVE UP      ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "||    DOWN KEY    :    MOVE DOWN    ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "||    ENTER KEY   :    SELECT       ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "||                                  ||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "||__________________________________||";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 16, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 6); cout << "|____________________________________|";
		key = inputKey();
	}
}
//Hàm kiểm tra thắng-----Quang
bool checkWinGame()
{
	if (score == 100)
		return true;
	else
		return false;
}
//Hàm Hiển thị thắng trong game-----Quang
void winGame()
{
	clrscr();
	showNameGame();
	setWindowGame();
	int key = inputKey();
	while (key != 13)
	{
		key = inputKey();
		setTextColor(YELLOW_COLOR);
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "      ____                                   " << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "\\  / |    | |    |   \\            / | |\\   |" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2);     cout << " \\/  |    | |    |    \\    /\\    /  | | \\  |" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << " /   |    | |    |     \\  /  \\  /   | |  \\ |" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "/    |____| |____|      \\/    \\/    | |   \\|" << endl;
		Sleep(100);
		setTextColor(CYAN_COLOR);
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "      ____                                   " << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "\\  / |    | |    |   \\            / | |\\   |" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2);     cout << " \\/  |    | |    |    \\    /\\    /  | | \\  |" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << " /   |    | |    |     \\  /  \\  /   | |  \\ |" << endl;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 20, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "/    |____| |____|      \\/    \\/    | |   \\|" << endl;
		Sleep(100);
	}

	setTextColor(WHITE_COLOR);
	clrscr();
	setWindowGame();
	showNameGame();
	setTextColor(YELLOW_COLOR);
	key = 11;
	while (key != 13)
	{
		key = inputKey();
		setTextColor(CYAN_COLOR);
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "|          YOUR SCORE           |";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|               " << score;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 0); cout << "---------------------------------";
		Sleep(100);
		setTextColor(YELLOW_COLOR);
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "|          YOUR SCORE           |";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "---------------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|               " << score;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "|";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 0); cout << "---------------------------------";
		Sleep(100);

	}
	setTextColor(WHITE_COLOR);
	clrscr();
	setWindowGame();
	showNameGame();
	showHighScore();
	while (key != 13)
	{
		key = inputKey();
	}
	clrscr();
}

int main()
{

}
