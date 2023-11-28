#include "mylib.h"
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
void inputPlayer()
{
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "----------------------------------";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "|         INPUT YOU NAME         |";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "----------------------------------";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "----------------------------------";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "----------------------------------";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 17, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "|                                |";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 3, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1);
	cin >> player;
}

//Hiển thị tên người chơi
void showPlayer()
{
	setTextColor(YELLOW_COLOR);
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 6, 1);
	for (int i = 0; i < 15; i++)
		cout << char(205);
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 6 + 7 - player.length() / 2, 2);
	cout << player;
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 6, 3);
	for (int i = 0; i < 15; i++)
		cout << char(205);
	setTextColor(WHITE_COLOR);
}

//Hàm hiển thị điểm
void showScore()
{
	setTextColor(YELLOW_COLOR);
	gotoXY(2, 1);
	for (int i = 0; i < 15; i++)
		cout << char(205);
	cout << endl;
	gotoXY(2, 2);
	cout << "   SCORE = " << score << endl;
	gotoXY(2, 3);
	for (int i = 0; i < 15; i++)
		cout << char(205);
	cout << endl;
	setTextColor(WHITE_COLOR);
}

//Hàm hiển thị level
void showLevel()
{
	setTextColor(YELLOW_COLOR);
	gotoXY(WINDOW_RIGHT - 15, 1);
	for (int i = 0; i < 15; i++)
		cout << char(205);
	cout << endl;
	gotoXY(WINDOW_RIGHT - 15, 2);
	cout << "   LEVEL = " << level << endl;
	gotoXY(WINDOW_RIGHT - 15, 3);
	for (int i = 0; i < 15; i++)
		cout << char(205);
	cout << endl;
	setTextColor(WHITE_COLOR);
}

//Hàm bắt đầu game
int menuGame()
{
	int select = 1;
	int key = inputKey();
	while (key != 13)
	{
		while (select == 1)
		{
			setTextColor(RED_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "|      NEW GAME      |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "----------------------";
			}

			setTextColor(WHITE_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "|      CONTINUE      |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "----------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "|    HOW TO PLAY     |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "----------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "|        EXIT        |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "----------------------";
			}

			key = inputKey();
			if (key == 80)
			{
				select = 2;
			}
			else if (key == 72)
			{
				select = 4;
			}
			else if (key == 13)
				break;
		}
		while (select == 2)
		{
			setTextColor(RED_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "|      CONTINUE      |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "----------------------";
			}
			setTextColor(WHITE_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "|    HOW TO PLAY     |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "----------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "|        EXIT        |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "----------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "|      NEW GAME      |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "----------------------";
			}

			key = inputKey();
			if (key == 80)
			{
				select = 3;
			}
			else if (key == 72)
			{
				select = 1;
			}
			else if (key == 13)
				break;
		}
		while (select == 3)
		{
			setTextColor(RED_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "|    HOW TO PLAY     |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "----------------------";
			}
			setTextColor(WHITE_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "|        EXIT        |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "----------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "|      NEW GAME      |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "----------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "|      CONTINUE      |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "----------------------";
			}

			key = inputKey();
			if (key == 80)
			{
				select = 4;
			}
			else if (key == 72)
			{
				select = 2;
			}
			else if (key == 13)
				break;
		}
		while (select == 4)
		{
			setTextColor(RED_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "|        EXIT        |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "----------------------";
			}
			setTextColor(WHITE_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "|      NEW GAME      |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "----------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "|      CONTINUE      |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "----------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "----------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "|    HOW TO PLAY     |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "----------------------";
			}

			key = inputKey();
			if (key == 80)
			{
				select = 1;
			}
			else if (key == 72)
			{
				select = 3;
			}
			else if (key == 13)
				break;
		}
	}
	return select;

}

int main()
{
	noCursorType();
	//Thiết lập màn hình

	SetWindowSize(80, 35);
	DisableResizeWindow();
	ShowScrollbar(false);
	showNameGame();
	setWindowGame();
	getHighScore();
	creatFood();
	bool statut = false;
	int choose = menuGame();


	while (choose != 4)
	{
		clrscr();
		showNameGame();
		setWindowGame();
		statut = false;

		switch (choose)
		{
		case 1:
		{
			deleteSaveGame();
			restartGame();
			inputPlayer();
			clrscr();
			showNameGame();
			setWindowGame();
			setTypeSnake();
			clrscr();
			setWindowGame();
			drawFood();
			showScore();
			showLevel();
			while (!statut)
			{
				Point lastSnake = ran.directionSnake(direction);
				statut = checkGame();
				if (!statut)
				{
					eatFood();
					showPlayer();
					showScore();
					showLevel();
					ran.drawSnake(lastSnake);
				}
				ran.getEvent(direction);
				Sleep(300 / speed);
				if (checkWinGame())
				{
					winGame();
					choose = menuGame();
					break;
				}
				int key = inputKey();
				if (key == 13)
				{
					int select = resumeGame();
					if (select == 1)
					{
						saveGame();
						clrscr();
						setWindowGame();
						showNameGame();
						choose = menuGame();
						break;
					}
					else
					{
						clrscr();
						setWindowGame();
						drawFood();
					}
				}
			}

			break;
		}
		case 2:
			if (continueGame())
			{
				clrscr();
				setWindowGame();
				drawFood();
				showScore();
				showLevel();
				while (!statut)
				{
					Point lastSnake = ran.directionSnake(direction);
					statut = checkGame();
					if (!statut)
					{
						eatFood();
						showPlayer();
						showScore();
						showLevel();
						ran.drawSnake(lastSnake);
					}
					ran.getEvent(direction);
					Sleep(300 / speed);
					if (checkWinGame())
					{
						winGame();
						choose = menuGame();
						break;
					}
					int key = inputKey();
					if (key == 13)
					{
						int select = resumeGame();
						if (select == 1)
						{
							saveGame();
							clrscr();
							setWindowGame();
							showNameGame();
							choose = menuGame();
							break;
						}
						else
						{
							clrscr();
							setWindowGame();
						}
					}
				}
				break;
			}
			else
			{
				clrscr();
				setWindowGame();
				showNameGame();
				gotoXY(25, 17); cout << "------------------------------------";
				gotoXY(25, 18); cout << "|        NO SAVE FOUND!!!!         |";
				gotoXY(25, 19); cout << "|      PLEASE CHOOSE NEW GAME      |";
				gotoXY(25, 20); cout << "------------------------------------";
				Sleep(1000);
				clrscr();
				setWindowGame();
				showNameGame();
				choose = menuGame();
			}
			break;
		case 3:
			howToPlay();
			clrscr();
			setWindowGame();
			showNameGame();
			choose = menuGame();
			break;
		}
		if (statut)
		{
			clrscr();
			setWindowGame();
			showNameGame();
			gameOver();
			restartGame();
			setWindowGame();
			showNameGame();
			choose = menuGame();
			clrscr();
			setWindowGame();
			showNameGame();
		}

	}


	return 0;
}
