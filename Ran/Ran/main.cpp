


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
	outFile.open("highscore.txt", ios::trunc);
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


