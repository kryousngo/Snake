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

