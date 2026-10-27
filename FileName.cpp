#include<stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

#define WIDE 60         //宽
#define HIGH 20         //高

struct FOOD {
	int M;
	int N;
}food;

int score = 0;

void gotoxy(int x, int y);
void initsnake();
void initFood();

void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);     //19到27是控制光标位置
}





void initFood() {
	food.N = rand() % (WIDE-2) + 1;                //0-58
	food.M = rand() % (HIGH-2) + 1;
	

}
struct BODY {                        //这是结构体struct，这储存着每节身体的X,Y坐标
	int X;
	int Y;

};
struct SNAKE {                             //这储存整条蛇
	struct BODY body[WIDE * HIGH];           //数组用来放每节身体的X，Y坐标
	int size;                                //用来表示现在有多少节身体。
}snake;

void initsnake() {
	snake.size = 2;
	snake.body[0].X = WIDE / 2;
	snake.body[0].Y = HIGH / 2;
	snake.body[1].X = WIDE / 2 + 1;
	snake.body[1].Y = HIGH / 2;
	return;
}
int main (void) 
{
	srand(time(NULL));                    //播种

	initsnake();
	initFood();


	gotoxy(snake.body[0].X, snake.body[0].Y);
	printf("@");
	gotoxy(food.N, food.M);
	printf("*");





	getchar();                  //教程是system("pause")，但我查资料后确定getchar();更通用，起卡屏的作用。
	return 0;
}
