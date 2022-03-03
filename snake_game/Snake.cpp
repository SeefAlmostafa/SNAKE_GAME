#include "Snake.h"


Snake::Snake() :width(20), height(20) { Setup(); }

void Snake::printMenu() {
	if (player == NONE) {
		cout << "(1)....... PLAYING.......(1)" << endl;
		cout << "(2)....... SHOWINFO......(2)" << endl;
		cout << "(3)....... MYSCORE.......(3)" << endl;
		cout << "(4)....... NewSymbols....(4)" << endl;
		cout << "(5)....... EXIT..........(5)" << endl;
	}
}

void Snake::set_Symbol(SetterStatus s) {
	char symbol[4];
	if (s == DEFAULT) {
		this->symbol[SNAKESHEAD] = 'O';
		this->symbol[SNAKESTAIL] = 'o';
		this->symbol[SNAKESWALL] = '\xB2';
		this->symbol[SNAKESFRUIT] = '\xDC';
	}
	else {
		cout << "Enter the symbols" << endl;
		for (int i = 0; i < 4; i++) {
			cout << "symbol[" << i + 1 << "]:";
			cin >> symbol[i];

			this->symbol[i] = symbol[i];
		}
		cout << "\n";
	}
}

char Snake::get_Symbol(int index) const {
	return symbol[index];
}

void Snake::print_Symbol() {
	for (int i = 0; i < 4; i++) {
		cout << get_Symbol(i) << "\n";
	}
}

void Snake::init_Tails() {
	for (int i = 0; i < 100; i++) {
		tailX[i] = 0;
		tailY[i] = 0;
	}
}

void Snake::improve_screen() {
	system("cls");
	clearScreen();
}

void Snake::set_player(int& player) {
	cout << "\nEnter a choice:";
	cin >> player;

	improve_screen();

	switch (player) {

	case INFO:
		Info();
		cout << "Press Enter to move to Menu:";
		if (cin.ignore())
			refresh_menu();
		break;

	case PLAY:
		Run(); break;

	case MAXSCORE:
		cout << "MaxScore:" << get_score() << "\n";
		cout << "Press Enter to move to Menu:";
		cin.ignore();

		if (cin.ignore())
			refresh_menu();
		break;

	case NEWSYMBOL:
		char mode;
		set_Symbol(NEW);
		gameOver = false;
		cout << "Do You want to play with the new Symbols... [Y/N]";
		cin >> mode;
		mode == 'Y' || mode == 'y' ? Run() : refresh_menu();
		break;
	case EXIT:
		Exit(); break;

	default:
		cout << "\nWrong Input:\n"; break;
	}
}

void Snake::Menu() {
	printMenu();
	set_player(player);
}

void Snake::Info() {
	cout << "=================================================\n";
	cout << "press 'W' to move Up" << endl
		<< "press 'S' to move Down" << endl
		<< "press 'A' to move Left" << endl
		<< "press 'D' to move Right" << endl
		<< "press 'x' to pause the game" << endl
		<< "press 'm' to stop the game" << endl;
	cout << "symbols of the game:" << endl
		<< "snakes_head:" << symbol[SNAKESHEAD] << endl
		<< "snakes_tail:" << symbol[SNAKESTAIL] << endl
		<< "snakes_wall:" << symbol[SNAKESWALL] << endl
		<< "snakes_fruit:" << symbol[SNAKESFRUIT] << endl << endl;
	cout << "Devolver Name: Seef Almosatfa" << endl;
	cout << "=================================================\n";

	cin.ignore();
}

void Snake::Exit() {
	gameOver = true;
}


void Snake::Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	score = 0;
	nTail = 0;

	player = NONE;
	GenerateFood();
	set_Symbol(DEFAULT);
	init_Tails();

}

void Snake::Draw() {
	for (int i = 0; i < width + 2; i++) {
		cout << symbol[SNAKESWALL];
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width + 1; j++) {
			if (j == 0 || j == width) {
				cout << symbol[SNAKESWALL];
			}
			if (i == y && j == x) {
				cout << symbol[SNAKESHEAD];
			}
			else if (i == fruitY && j == fruitX) {
				cout << symbol[SNAKESFRUIT];
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << symbol[SNAKESTAIL];
						print = true;
					}

				}
				if (!print) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++) {
		cout << symbol[SNAKESWALL];
	}
	cout << endl;
	cout << "Score:" << score << endl;
}

void Snake::Input() {

	if (_kbhit()) {
		switch (_getch()) {
		case 'a': if (dir != RIGHT) { dir = LEFT; }
				break;
		case 'd': if (dir != LEFT) { dir = RIGHT; }
				break;
		case 'w': if (dir != DOWN) { dir = UP; }
				break;
		case 's': if (dir != UP) { dir = DOWN; }
				break;
		case 'x': dir = STOP;
			break;
		case 'm': Exit();
			break;
		}
	}
}


void Snake::Move() {
	switch (dir) {
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
}

void Snake::Logic() {

	if (dir != STOP) {
		for (int i = nTail; i > 0; i--) {
			tailX[i] = tailX[i - 1];
			tailY[i] = tailY[i - 1];
		}

		tailX[0] = x;
		tailY[0] = y;

		Move();


		if (x >= width) x = 0;  else if (x < 0) x = width - 1;
		if (y >= height) y = 0; else if (y < 0) y = height - 1;

		for (int i = 0; i < nTail; i++) {
			if (tailX[i] == x && tailY[i] == y) {
				gameOver = true;
			}
		}

		if (x == fruitX && y == fruitY) {
			score += 10;
			nTail++;
			GenerateFood();
		}

	}
}



void Snake::set_cursor(bool visible) {
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Snake::clearScreen() {
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Snake::GenerateFood() {
	srand(time(NULL));


	fruitX = rand() % (width - 2) + 1;
	fruitY = rand() % (height - 2) + 1;



}

void Snake::refresh_menu() {
	improve_screen();
	player = NONE;
	Setup();
	Menu();
}

void Snake::GameOver() {
	char mode;
	if (gameOver) {
		cout << "GAMEOVER ! Do You want to play again Y/N" << endl;
		cin >> mode;

		if (mode == 'y' || mode == 'Y') {
			gameOver = false;
			Setup();
			Run();
		}
		else
			refresh_menu();
	}
	return;
}


void Snake::Run() {
	improve_screen();

	set_cursor(false);
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		if (!gameOver)
			clearScreen();
		Sleep(36);
	}
	GameOver();
}


// Not Fixed - Bug:
// FruitX und FruitY should have diffrent pos than tailX[i] & tailY[i]

