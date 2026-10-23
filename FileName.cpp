#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
void initGame() {
	initgraph(800, 640,SHOWCONSOLE);
	loadimage(NULL, ("D:/blue.bk.jpg"));
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

int main() {
	initGame();
	ExMessage msg;
	while (true) {
		if (peekmessage(&msg)) {
			if (msg.message == WM_LBUTTONDOWN) {
				printf("左键 %d %d\n", msg.x, msg.y);
				fflush(stdout);
			}
			if (msg.message == WM_RBUTTONDOWN) {
				printf("右键 %d %d\n", msg.x, msg.y);
				fflush(stdout);
			}
			if (msg.message == WM_CLOSE) break;
			
		}
	}
	getchar();
	return 0;
}

	
	/*initgraph(800, 600);	
	IMAGE wzq;
	loadimage(&wzq, ("D:/blue.bk.jpg"));
	putimage(0, 0, &wzq);
	setlinecolor(WHITE);
	for (int i=0;i < 16;i++) {
		line(0, i * 40, 600, i * 40);
		line(i * 40, 0, i * 40, 640);
		line(640, 0, 640, 640);
	}
	setbkmode(0);
	settextcolor(RED);
	outtextxy(680, 20,"玩家1: 原神");
	outtextxy(680, 560,"玩家2 鸣潮");*/