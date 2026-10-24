#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<math.h>
int flag = 0;//设置全局变量，目的是判断黑白方
int ChessMap[20][20] = { 0 };
void initGame() {
	initgraph(800, 640, SHOWCONSOLE);
	IMAGE bk;
	loadimage(&bk, "./res/blue.white.bk.jpg", 800, 640);
	putimage(0, 0, &bk);
	for (int i = 1;i < 16;i++) {
		line(0, i * 40, 600, i * 40);
		line(i * 40, 0, i * 40, 640);
	}
	setlinestyle(PS_SOLID, 2);
	line(640, 0, 640, 640);
	setbkmode(0);
	settextcolor(RED);
	outtextxy(680, 20, "玩家1: 原神");
	outtextxy(680, 560, "玩家2 :鸣潮");
}

//判定胜利 横线
int judge(int MapX, int MapY){
	int temp = ChessMap[MapX][MapY];
	if (temp == 0) return 0;
	for (int m = MapX - 4, n = MapY; m <= MapX ; m++) {
		if (m >= 1 && m + 4 <= 15 && temp == ChessMap[m][n] && temp == ChessMap[m + 1][n] && temp == ChessMap[m + 2]
			[n] && temp == ChessMap[m + 3][n] && temp == ChessMap[m + 4][n] )
			return 1;
}
	//竖线
	for (int m = MapX , n = MapY-4; n <= MapY; n++) {
		if (m >= 1 && m + 4 <= 15 && temp == ChessMap[m][n] && temp == ChessMap[m][n+1] && temp == ChessMap[m]
			[n+2] && temp == ChessMap[m][n+3] && temp == ChessMap[m][n+4])
			return 1;
	}
	//左斜线 x+ y+
	for (int m = MapX -4, n = MapY - 4; m<MapX, n <= MapY;m++, n++) {
		if (m >= 1 && m + 4 <= 15 && temp == ChessMap[m][n] && temp == ChessMap[m +1][n + 1] && temp == ChessMap[m + 2]
			[n + 2] && temp == ChessMap[m + 3][n + 3] && temp == ChessMap[m + 4][n + 4])
			return 1;
	}
    //右斜线x+ y-
	for (int m = MapX - 4,n = MapY +4; m < MapX, n >= MapY;m++, n--) {
		if (m >= 1 && m + 4 <= 15 && temp == ChessMap[m][n] && temp == ChessMap[m+1][n - 1] && temp == ChessMap[m + 2]
			[n - 2] && temp == ChessMap[m + 3][n - 3] && temp == ChessMap[m + 4][n - 4])
			return 1;
	}
	return 0;
}

void PlayGame() {
	int ChessX = -1, ChessY = -1;
	int MapX = 0, MapY = 0;
	MOUSEMSG Msg;


	HWND hwnd = GetHWnd();//



	while (true) {
		Msg = GetMouseMsg();
		for (int i = 1;i <= 15;i++) {
			for (int j = 1;j <= 15;j++) {
				if (abs(Msg.x - i * 40) < 20 && abs(Msg.y - j * 40) < 20) {
					ChessX = i * 40;
					ChessY = j * 40;
					MapX = i;
					MapY = j;
				}
			}
		}
		if (Msg.uMsg == WM_LBUTTONDOWN) {
			if (ChessMap[MapX][MapY] != 0) {
				MessageBox(hwnd, "这里有棋子了，请到其他位置！！！", "五子棋", MB_OK);
			}
			if (MapX >= 1 && MapX <= 15 && MapY >= 1 && ChessMap[MapX][MapY] == 0) {
				if (flag % 2 == 0) {
					setfillcolor(BLACK);
					solidcircle(ChessX, ChessY, 10);
					ChessMap[MapX][MapY] = 1;
				}
				else {
					setfillcolor(WHITE);
					solidcircle(ChessX, ChessY, 10);
					ChessMap[MapX][MapY] = 2;
				}
				flag++;//循环
				if (judge(MapX, MapY)) {
					if (1 == flag % 2) {
						MessageBox(hwnd, "玩家1:黑棋胜利", "Game Over", MB_OK);
						return;
					}
					else {
						MessageBox(hwnd, "玩家2:白棋胜利", "Game Over", MB_OK);
						return;
			}
		}
		
			}
		}
		if (Msg.uMsg == WM_CLOSE) { closegraph(); return; }




	}
}

int main() {
	initGame();
	PlayGame();
	ExMessage msg;
	int ChessX = -1, ChessY = -1;
	while (true) {
		if (peekmessage(&msg)) {
			if (msg.message == WM_CLOSE) { closegraph(); return 0; }
			if (msg.message == WM_LBUTTONDOWN) {
				for (int i = 1;i <= 15;i++) {
					for (int j = 1;j <= 15;j++) {
						if (abs(msg.x - i * 40) < 20 && abs(msg.y - j * 40) < 20) {
							ChessX = i * 40;
							ChessY = j * 40;
						}
					}
				}
			}


			printf("ChessX=%d,ChessY=%d\n", ChessX, ChessY);
			printf("%d %d\n", msg.x, msg.y);
			solidcircle(ChessX, ChessY, 10);
			fflush(stdout);
		}
		else if (msg.message == WM_RBUTTONDOWN) {
			for (int i = 1;i <= 15;i++) {
				for (int j = 1;j <= 15;j++) {
					if (abs(msg.x - i * 40) < 20 && abs(msg.y - j * 40) < 20) {
						ChessX = i * 40;
						ChessY = j * 40;
					}
				}
			}
			printf("ChessX=%d,ChessY=%d\n", ChessX, ChessY);
			printf("%d %d\n", msg.x, msg.y);
			fflush(stdout);
		}
	}
return 0;
}

