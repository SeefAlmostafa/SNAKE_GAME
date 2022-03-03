#pragma once
using namespace std;
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <time.h>



enum symbol { SNAKESHEAD = 0, SNAKESTAIL, SNAKESWALL, SNAKESFRUIT };
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum MenuStatus { PLAY = 1, INFO, MAXSCORE, NEWSYMBOL, EXIT, NONE = -1 };
enum SetterStatus { DEFAULT = 0, NEW };

class Snake {
private:
	bool gameOver;
	char symbol[4];
	const int width;
	const int height;
	int x, y;
	int fruitX, fruitY;
	int tailX[100], tailY[100];
	int nTail;
	int score;
	eDirection dir;
	int player;

public:
	Snake();
	inline int get_score() const { return score; }
	inline int get_width() const { return width; }
	inline int get_height() const { return height; }
	void printMenu();
	void set_player(int&);
	void set_Symbol(SetterStatus);
	char get_Symbol(int) const;
	void print_Symbol();
	void init_Tails();
	void Menu();
	void Run();
	void improve_screen();
	void refresh_menu();


protected:
	void Exit();
	void Info();
	void Setup();
	void Draw();
	void Input();
	void Move();
	void Logic();
	void GenerateFood();
	void GameOver();
	void set_cursor(bool);
	void clearScreen();

};

