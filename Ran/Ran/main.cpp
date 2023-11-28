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

