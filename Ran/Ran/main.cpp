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


//Đổi chỗ và sắp xếp bảng xếp hạng
void swap(HighScore& a, HighScore& b)
{

	HighScore temp;
	temp.name = b.name;
	b.name = a.name;
	a.name = temp.name;

	temp.score = b.score;
	b.score = a.score;
	a.score = temp.score;
}
void selectionSort()
{

	for (int i = 0; i < table.amount - 1; i++)
	{
		for (int j = i + 1; j < table.amount; j++)
			if (table.people[j].score > table.people[i].score)
			{
				swap(table.people[i], table.people[j]);
			}
	}
}

//Lấy thông tin bằng xếp hạng
void getHighScore()
{
	ifstream inFile;
	table.amount = 0;
	inFile.open("highscore.txt");
	if (inFile)
	{
		
		while (!inFile.eof())
		{
			inFile >> table.people[table.amount].name;
			inFile >> table.people[table.amount].score;
			table.amount++;
		}
		table.amount--;
	}
}

//Thay đổi bảng xếp hạng
void changeHighScore()
{
	ofstream outFile;
	outFile.open("highscore.txt",ios::trunc);
	if (score != 0)
	{
		if (table.amount == 0)
		{
			table.amount = 1;
			table.people[0].name = player;
			table.people[0].score = score;
		}
		else if (table.amount < 5)
		{
			table.people[table.amount].name = player;
			table.people[table.amount].score = score;
			table.amount++;
			selectionSort();
		}
		else if (table.amount == 5)
		{
			int temp;
			if (score > table.people[4].score)
			{
				table.people[4].name = player;
				table.people[4].score = score;
				selectionSort();
			}

		}
	}
	for (int i = 0; i < table.amount; i++)
	{
		outFile << table.people[i].name << "\t" << table.people[i].score << endl;
	}

	outFile.close();
}

//Hiển thị bảng xếp hạng
void showHighScore()
{
	changeHighScore();
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 10); cout << "---------------------------";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 9);  cout << "|        HIGH SCORE       |";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 8);  cout << "---------------------------";

	for (int i = 0; i < table.amount; i++)
	{
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 7 + i * 3);     cout << "---------------------------";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6 + i * 3); cout << "|  " << table.people[i].name << "\t \t" << table.people[i].score;
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 12, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6 + i * 3); cout << "|";
		gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5 + i * 3); cout << "---------------------------"; \
	}
	Sleep(1000);

}

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

//Hàm tạo thức ăn
void creatFood()
{
	srand(time(0));
	food.x = WINDOW_LEFT + 1 + rand() % (WINDOW_RIGHT - WINDOW_LEFT - 1);
	food.y = WINDOW_TOP + 1 + rand() % (WINDOW_BOTTOM - WINDOW_TOP - 1);
}

//Hàm hiển thị thức ăn
void drawFood()
{
	setTextColor(CYAN_COLOR);

	gotoXY(food.x, food.y);
	cout << ran.snakeType;
	setTextColor(WHITE_COLOR);
}

//Hàm xử lý khi rắn ăn mồi
void eatFood()
{
	if (ran.snake[0].x == food.x && ran.snake[0].y == food.y)
	{
		ran.length++;
		creatFood();
		drawFood();
		score++;
		if ((score != 0) && (score % 10 == 0))
		{
			level++;
			speed *= 2;
		}

	}

}

//Hàm bắt đầu lại
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

//Hàm chọn hình còn rắn
void setTypeSnake()
{
	int select = 1;
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 10); cout << "---------------------------";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 9);  cout << "|    CHOOSE SNAKE TYPE    |";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 8);  cout << "---------------------------";
	int key = inputKey();
	while (key != 13)
	{
		while (select == 1)
		{
			setTextColor(RED_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 7); cout << "---------------------------";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "|      HEART      " << char(3) << "       |";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "---------------------------";

			setTextColor(WHITE_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "|      DIAMOND    " << char(4) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "|      CLUB       " << char(5) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "|      SPADE      " << char(6) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 6); cout << "|      SQUARE     " << char(254) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 7); cout << "---------------------------";
			}

			key = inputKey();
			if (key == 80)
			{
				select = 2;
				break;
			}
			else if (key == 72)
			{
				select = 5;
				break;
			}
			else if (key == 13)
				break;
		}
		while (select == 2)
		{
			setTextColor(RED_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "---------------------------";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "|      DIAMOND    " << char(4) << "       |";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "---------------------------";

			setTextColor(WHITE_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 7); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "|      HEART      " << char(3) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "|      CLUB       " << char(5) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "|      SPADE      " << char(6) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 6); cout << "|      SQUARE     " << char(254) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 7); cout << "---------------------------";
			}

			key = inputKey();
			if (key == 80)
			{
				select = 3;
				break;
			}
			else if (key == 72)
			{
				select = 1;
				break;
			}
			else if (key == 13)
				break;
		}
		while (select == 3)
		{
			setTextColor(RED_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "---------------------------";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "|      CLUB       " << char(5) << "       |";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "---------------------------";

			setTextColor(WHITE_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 7); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "|      HEART      " << char(3) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "|      DIAMOND    " << char(4) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "|      SPADE      " << char(6) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 6); cout << "|      SQUARE     " << char(254) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 7); cout << "---------------------------";
			}
			key = inputKey();
			if (key == 80)
			{
				select = 4;
				break;
			}
			else if (key == 72)
			{
				select = 2;
				break;
			}
			else if (key == 13)
				break;
		}
		while (select == 4)
		{
			setTextColor(RED_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "---------------------------";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "|      SPADE      " << char(6) << "       |";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "---------------------------";

			setTextColor(WHITE_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 7); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "|      HEART      " << char(3) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "|      DIAMOND    " << char(4) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "|      CLUB       " << char(5) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 6); cout << "|      SQUARE     " << char(254) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 7); cout << "---------------------------";


			}
			key = inputKey();
			if (key == 80)
			{
				select = 5;
				break;
			}
			else if (key == 72)
			{
				select = 3;
				break;
			}
			else if (key == 13)
				break;
		}
		while (select == 5)
		{
			setTextColor(RED_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 5); cout << "---------------------------";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 6); cout << "|      SQUARE     " << char(254) << "       |";
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 7); cout << "---------------------------";

			setTextColor(WHITE_COLOR);
			{
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 7); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "|      HEART      " << char(3) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "---------------------------";

				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "|      DIAMOND    " << char(4) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 0); cout << "|      CLUB       " << char(5) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 1); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 2); cout << "---------------------------";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 3); cout << "|      SPADE      " << char(6) << "       |";
				gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 14, (WINDOW_BOTTOM + WINDOW_TOP) / 2 + 4); cout << "---------------------------";

			}
			key = inputKey();
			if (key == 80)
			{
				select = 1;
				break;
			}
			else if (key == 72)
			{
				select = 4;
				break;
			}
			else if (key == 13)
				break;
		}

	}
	if (select == 1)
		ran.setSnakeType(char(3));
	if (select == 2)
		ran.setSnakeType(char(4));
	if (select == 3)
		ran.setSnakeType(char(5));
	if (select == 4)
		ran.setSnakeType(char(6));
	if (select == 5)
		ran.setSnakeType(char(254));
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

//Hàm tạm dùng game
int resumeGame()
{
	clrscr();
	setWindowGame();
	showNameGame();
	int select = 1;
	int key = inputKey();
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 7); cout << "------------------------------------";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 6); cout << "|              RESUME              |";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 5); cout << "------------------------------------";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "|                                  |";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "------------------------------------";
	while (key != 13)
	{

		while (select == 2)
		{
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 8, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "YES";
			setTextColor(RED_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 8, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "YES";
			setTextColor(WHITE_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "NO";
			key = inputKey();
			if (key == 77 || key == 75)
			{
				select = 1;
				break;
			}
			else if (key == 13)
				break;
		}
		while (select == 1)
		{
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 8, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "YES";
			setTextColor(RED_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4); cout << "NO";
			setTextColor(WHITE_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 4);
			key = inputKey();
			if (key == 77 || key == 75)
			{
				select = 2;
				break;
			}
			else if (key == 13)
				break;
		}
	}
	return select;
}

//Hàm lưu game
void saveGame()
{
	clrscr();
	setWindowGame();
	showNameGame();
	int select = 1;
	int key = inputKey();
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 3); cout << "------------------------------------";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 2); cout << "|       DO YOU WANT TO SAVE?       |";
	gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 15, (WINDOW_BOTTOM + WINDOW_TOP) / 2 - 1); cout << "------------------------------------";

	while (key != 13)
	{

		while (select == 1)
		{
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 5, (WINDOW_BOTTOM + WINDOW_TOP) / 2); cout << "YES";
			setTextColor(RED_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 5, (WINDOW_BOTTOM + WINDOW_TOP) / 2); cout << "YES";
			setTextColor(WHITE_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2); cout << "NO";
			key = inputKey();
			if (key == 77 || key == 75)
			{
				select = 2;
				break;
			}
			else if (key == 13)
				break;
		}
		while (select == 2)
		{
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 - 5, (WINDOW_BOTTOM + WINDOW_TOP) / 2); cout << "YES";
			setTextColor(RED_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2); cout << "NO";
			setTextColor(WHITE_COLOR);
			gotoXY((WINDOW_RIGHT + WINDOW_LEFT) / 2 + 10, (WINDOW_BOTTOM + WINDOW_TOP) / 2); cout << "NO";
			key = inputKey();
			if (key == 77 || key == 75)
			{
				select = 1;
				break;
			}
			else if (key == 13)
				break;
		}
	}
	if (select == 1)
	{
		ofstream outFile;
		outFile.open("save.txt");

		outFile << player << endl;
		outFile << score << endl;
		outFile << level << endl;
		outFile << speed << endl;

		switch (direction)
		{
		case RIGHT:
			outFile << 0 << endl;
			break;
		case LEFT:
			outFile << 1 << endl;
			break;
		case UP:
			outFile << 2 << endl;
			break;
		case DOWN:
			outFile << 3 << endl;
		}

		outFile << int(ran.snakeType) << endl;
		outFile << int(ran.length) << endl;
		for (int i = 0; i < ran.length; i++)
		{
			outFile << ran.snake[i].x << " " << ran.snake[i].y << endl;
		}
		outFile << food.x << " " << food.y << endl;
		outFile.close();
	}

}

//Hàm xóa đi phần game đã lưu
void deleteSaveGame()
{
	int result = remove("save.txt");
}

//Hàm tiếp tục game
bool continueGame()
{
	ifstream inFile;
	inFile.open("save.txt");
	if (!inFile)
		return false;
	inFile >> player;
	inFile >> score;
	inFile >> level;
	inFile >> speed;
	int d;
	inFile >> d;
	switch (d)
	{
	case 0:
		direction = RIGHT;
		break;
	case 1:
		direction = LEFT;
		break;
	case 2:
		direction = UP;
		break;
	case 3:
		direction = DOWN;
	}

	inFile >> d;
	ran.snakeType = char(d);
	inFile >> ran.length;
	for (int i = 0; i < ran.length; i++)
	{
		inFile >> ran.snake[i].x >> ran.snake[i].y;
	}
	inFile >> food.x >> food.y;
	inFile.close();
	return true;

}


//Hàm hiển thị hướng dẫn
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

bool checkWinGame()
{
	if (score == 100)
		return true;
	else
		return false;
}

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
