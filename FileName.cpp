#include<windows.h>
#include <cstdlib>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#include<stdio.h>
int create_random(int min, int max) {
	if (min > max) {
		int temp = min; min = max; max = temp;
	}
	return min + rand() % (max - min + 1);
}
struct Point {
	double x, y;
	COLORREF color;
};
COLORREF colors[] = {
	RGB(255,105,180),
	RGB(255,182,193),
	RGB(255,20,147),
	RGB(255,160,200),
	RGB(250,128,180),
	RGB(255,228,225),
	RGB(219,112,147)
};
const int xScreen = 1200;
const int yScreen = 800;

const double PI = 3.1415926535;
const double e = 2.71828;

const int quantity = 506;
const int circles = 210;
const int frames = 20;

Point origin_points[quantity];
Point points[circles * quantity];
IMAGE images[frames];

double  screen_x(double x) {
	return x + xScreen / 2;
}

double screen_y(double y) {
	return -y +yScreen / 2;
}

int creat_random(int x1, int x2) {
	if (x2 > x1)
		return rand() % (x2 - x1 + 1) + x1;
	return x1;
}

void create_data() {
	int index = 0;
	const int max_points = 20000;
	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	double average_distance = 5.0;
	for (double radian = 0.1; radian <= 2 * PI; radian += 0.005) {
		x2 = 16 * pow(sin(radian), 3);
		y2 = 13 * cos(radian) - 5 * cos(2 * radian) - 2 * cos(3 * radian) - cos(4 * radian);

		double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		if (distance > 0.5 && index < quantity) {
			x1 = x2, y1 = y2;
			origin_points[index].x = x2;
			origin_points[index++].y = y2;
		}
	}
	index = 0;
	for (double size = 0.1, lightness = 1.4; size <= 20; size += 0.1) {
		double success_p = 1 / (1 + pow(e, 8 - size / 2));
		if (lightness > 1) lightness -= 0.0025;

		for (int i = 0; i < quantity; ++i) {
			if (index >= max_points) break;
			if (success_p > create_random(0, 100) / 100.0) {
				COLORREF colors[] = { RGB(255,0,0),RGB(255,0,0),RGB(255,120,0),RGB(255,200,80),RGB(200,0,0),RGB(120,0,0),RGB(255,60,60),RGB(180,20,20) };
				int color_count = sizeof(colors) / sizeof(colors[0]);
				COLORREF color = colors[create_random(0, color_count - 1)];
				auto clamp255 = [](double v) { if (v < 0) v = 0; if (v > 255) v = 255; return(int)v; };
				points[index].color = RGB((int)(GetRValue(color) / lightness),
					(int)(GetGValue(color) / lightness),
					(int)(GetBValue(color) / lightness));
				points[index].x = size * origin_points[i].x + create_random(-4, 4);
				points[index++].y = size * origin_points[i].y + create_random(-4, 4);
			}
		}
	}

	int points_size = index;
	for (int frame = 0; frame < frames;++frame) {
		images[frame] = IMAGE(xScreen, yScreen);
		SetWorkingImage(&images[frame]);

		for (index = 0; index < points_size; ++index) {
			double x = points[index].x, y = points[index].y;
			double distance = sqrt(x * x + y * y);
			double distance_increase = -0.0009 * distance * distance + 0.35714 * distance + 5;
			if (average_distance < 0.0001) average_distance = 0.0001;
			double x_increase = distance_increase * x / distance / frames;
			double y_increase = distance_increase * y / distance / frames;

			points[index].x += x_increase;
			points[index].y += y_increase;

			setfillcolor(points[index].color);
			solidcircle(screen_x(points[index].x), screen_y(points[index].y), 1);
		}

	}
	SetWorkingImage();
}

int main() {
	initgraph(xScreen, yScreen);
	BeginBatchDraw();
	srand(time(0));
    create_data();

	bool extend = true, shrink = false;
	int frame = 0 ;
	while (true) {
		if (!GetHWnd()) break;
		if (_kbhit()) break;
		setbkcolor(RGB(20, 10, 20));
		cleardevice();
		putimage(0, 0, &images[frame]);
		for (int i = 0; i < 50; i++) {
			int idx = rand() % quantity;
			double size = 20 + rand() % 5;
			double x = origin_points[idx].x * size + create_random(-10, 10);
			double y = origin_points[idx].y * size + create_random(-10, 10);
			setfillcolor(RGB(255, 150, 190));
			solidcircle((int)screen_x(x), (int)screen_y(y), 1);
		}
		FlushBatchDraw();
		Sleep(20);

		if (extend) {
			if (frame >= frames -1) { shrink = true; extend = false; }
			else ++frame;
		}
		else {
			if (frame == 0) { shrink = false;extend = true; }
			else --frame;
		}
	}


	EndBatchDraw();
	closegraph();
	return 0;
}
