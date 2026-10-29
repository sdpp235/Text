#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

#define WIDE 60         //宽
#define HIGH 20         //高

int kx = 0;
int ky = 0;

struct FOOD {
	int M;
	int N;
}food;

struct BODY {                        //这是结构体struct，这储存着每节身体的X,Y坐标
	int X;
	int Y;

};
struct SNAKE {                             //这储存整条蛇
	struct BODY body[WIDE * HIGH];           //数组用来放每节身体的X，Y坐标
	int size;                                //用来表示现在有多少节身体。
}snake;

int score = 0;

void gotoxy(int x, int y);
void initsnake();
void initFood();
void playGame();
void drawBorder();                      //边界
void updateScore();                     //分数


void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);     //19到27是控制光标位置,如果是需要反复调用可以把它封装。
}

void drawBorder() {
	int i;
	for (i = 0;i < WIDE + 2; i++) {
		gotoxy(i, 0);
		printf("=");
	}
	for (i = 0;i < WIDE + 2; i++) {
		gotoxy(i, HIGH + 1);
		printf("=");
	}
	for (i = 1;i <= HIGH; i++) {
		gotoxy(0,i);
		printf("|");
		gotoxy(WIDE + 1, i);
		printf("|");
	}
}
void updateScore() {
	gotoxy(WIDE + 5, 2);
	printf("Score: %d", score);
}


void initFood() {
	food.N = rand() % (WIDE-2) + 1;                //0-58
	food.M = rand() % (HIGH-2) + 1;	
}

void initsnake() {
	snake.size = 2;
	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;
	snake.body[1].X = WIDE / 2 + 1;
	snake.body[1].Y = HIGH / 2 ;
	return;
}


void initUI() {
	COORD coord;
	coord.X = snake.body[0].X;
	coord.Y = snake.body[0].Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("@");
	coord.X = snake.body[1].X;
	coord.Y = snake.body[1].Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("o");
    coord.X = 0;
	coord.Y = HIGH + 2;
	
}

void playGame()
{
	char key = 'd';
	kx = 1; ky = 0;
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDE &&
		snake.body[0].Y >= 0 && snake.body[0].Y < HIGH)
	{
		if (_kbhit()) {
			key = _getch();
		}
		switch (key)
		{
		case'w': if (ky != 1) { kx = 0; ky = -1; }break;
		case's': if (ky != -1) { kx = 0; ky = 1; }break;
		case'a': if (kx != 1) { kx = -1; ky = 0; }break;
		case'd': if (kx != -1) { kx = 1; ky = 0; }break;
		default:
			break;
		}
		int oldX = snake.body[0].X;
		int oldY = snake.body[0].Y;
		int oldTailX = snake.body[snake.size - 1].X;
		int oldTailY = snake.body[snake.size - 1].Y;
		int eaten = 0;

		if (oldX == food.N && oldY == food.M) {
			initFood();
			snake.size++;
			score += 10;
			updateScore();
			eaten = 1;
		}
		for (int i = snake.size - 1; i > 0; i--) {
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		snake.body[0].X += kx;
		snake.body[0].Y += ky;

		for (int i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X && snake.body[0].Y == snake.body[i].Y)
			{
				gotoxy(0, HIGH + 1);
				printf("GAMEOVER!!! Final Score: %d", score);

				return;
			}
		}
		if (eaten == 0) {
			gotoxy(oldTailX, oldTailY);printf(" ");
		}
		gotoxy(oldX, oldY); printf("o");
		if (score >= 20) {                                             //可改墙破所需要的分数
			static int broken = 0;
			if (!broken) {
				broken = 1;
				for (int i = 0; i < WIDE + 2;i++)
				{
					gotoxy(i, 0); printf(" ");
					gotoxy(i, HIGH + 1); printf(" ");
				}
				for (int i = 0; i < HIGH ;i++)
				{
					gotoxy(0,i); printf(" ");
					gotoxy(WIDE+1, i); printf(" ");
				}
				gotoxy(WIDE / 2 - 6, HIGH / 2);
				printf("墙壁被破！！！\n");
				Sleep(800);
				gotoxy(WIDE / 2 - 6, HIGH / 2);
				printf("               ");
			}
		}
			gotoxy(snake.body[0].X, snake.body[0].Y); printf("@");
			gotoxy(food.N, food.M);printf("*");

		Sleep(150);

	}
	gotoxy(0, HIGH + 1);
	printf("HIT THE WALL! Final Score: %d", score);
}

	int main(void)
{
	srand(time(NULL));
	initsnake();
	initFood();
	system("cls");
	gotoxy(snake.body[0].X, snake.body[0].Y);printf("@");
	gotoxy(snake.body[1].X, snake.body[1].Y);printf("o");
	gotoxy(food.N, food.M);
	printf("*");
	gotoxy(0, HIGH + 1);printf("press any key to start!!!");
	_getch();
	system("cls");
	drawBorder();
	updateScore();
	playGame();
	_getch();
	return 0;
}
