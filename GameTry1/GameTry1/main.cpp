#include<iostream>
#include<vector>
#include<graphics.h>
#include<windows.h>
#include<direct.h>
#include<conio.h>
#include<string.h>
#include<string>
#include<fstream>
#pragma comment (lib, "winmm.lib") // mciSendString,quote Windows Multimedia API
#define blocksize 30
#define width 27*blocksize
#define high  25*blocksize
#define exptime 200
#define expsize 29
#define v		1
#define radius	8
#define a		10
using namespace std;
class monster {
public:
	double x, y;
	double xv = 0, yv = 0;
	
	int move = 0;
	int begincount;
	monster(double X, double Y, int COUNT) :x(X), y(Y), begincount(COUNT) {	}
	void changedirection() {
		int op = rand() % 4;
		if (op == 0) {
			xv = v;
			yv = 0;
		}
		else if (op == 1) {
			xv = -v;
			yv = 0;
		}
		else if (op == 2) {
			xv = 0;
			yv = v;
		}
		else {
			xv = 0;
			yv = -v;
		}
	}
	void changeposition() {
		x += xv;
		y += yv;
	}
};
vector<monster> monsters;
double px, py;
double xv, yv;
static int mycount;
static int alive;
int *key;
HWND start_screen;
int music[2];
IMAGE dot;
IMAGE bkimage;
IMAGE block1, block2, block3;// 3 kinds of blocks with diff colors
IMAGE explod1, explod2, explod3, explod4, explod5, explod6, explod7;// exploded process
int dots[high/blocksize][width/blocksize] = { 0 };
void initmonster();
void updatemonster();
void getimage();
void updateuser();
void showexplod(int x, int y);
double dist(double x1, double y1, double x2, double y2);
void collide();
void collide(monster& m);
void update();
void updatedraw();
void drawmap();
void startup();
int main()
{
	getimage();
	startup();
	while (alive) {
		updatemonster();
		updateuser();
		update();
		if (alive == 0) {
			EndBatchDraw();
			mciSendString("close bkmusic.mp3", NULL, 0, NULL);
			monsters.clear();
			getimage();
			startup();
			continue;
		}
		collide();
		updatedraw();
		FlushBatchDraw();
	}

	closegraph();
	return 0;
}
void getimage() {
	loadimage(&bkimage, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\bkimage.jpg"), blocksize, blocksize);
	loadimage(&dot, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\dot.bmp"), blocksize, blocksize);
	loadimage(&block1, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\block1.jpg"), blocksize, blocksize);
	loadimage(&block2, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\block2.jpg"), blocksize, blocksize);
	loadimage(&block3, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\block3.jpg"), blocksize, blocksize);
	loadimage(&explod1, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\explod1.png"), expsize, expsize);
	loadimage(&explod2, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\explod2.png"), expsize, expsize);
	loadimage(&explod3, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\explod3.png"), expsize, expsize);
	loadimage(&explod4, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\explod4.png"), expsize, expsize);
	loadimage(&explod5, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\explod5.png"), expsize, expsize);
	loadimage(&explod6, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\explod6.png"), expsize, expsize);
	loadimage(&explod7, _T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\explod7.png"), expsize, expsize);
}
void startup()
{
	initgraph(width, high);
	px = 285, py = 285;
	xv = 0, yv = 0;
	mycount = 0;
	alive = 1;
	key = &alive;
	BeginBatchDraw();
	//背景音乐播放
	mciSendString("open D:\\VS C++项目\\GameTry1\\GameTry1\\music\\bkmusic.mp3", NULL, 0, NULL);
	mciSendString("play bkmusic.mp3 repeat", NULL, 0, NULL);
	music[0] = 1;
	music[1] = 1;
	drawmap();
	initmonster();
	FlushBatchDraw();

}
void initmonster() {
	int amount = 15;
	while (amount) {
		double X = 12 * blocksize;
		double Y = 12 * blocksize;
		int begincount = rand() % 5;
		monster m(X, Y, begincount);
		m.changedirection();
		monsters.push_back(m);
		amount--;
	}
}
void updatemonster() {
	for (auto &m : monsters) {
		// monster count
		m.begincount--;
		// whether in original room
		if (m.x > 8 * blocksize && m.x < 18 * blocksize) {
			if (m.y > 10 * blocksize && m.y < 14 * blocksize) {
				// ready to leave
				if (m.x > 12 * blocksize + 15 && m.x < 14 * blocksize && m.begincount <= 0) {
					m.yv = -v;
					m.xv = 0;
				}
			}
		}
		// outside the original room
		if (m.xv == 0 && m.yv == 0) {
			m.changedirection();
		}
	}
}
void updateuser() {
	if (_kbhit()) {
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {		//left forward
			xv = (xv < 0 ? (xv > -v ? xv - 0.1 : -v) : xv - 0.1);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {		//right forwards
			xv = (xv > 0 ? (xv < v ? xv + 0.1 : v) : xv + 0.1);
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {			//upwards
			yv = (yv < 0 ? (yv > -v ? yv - 0.1 : -v) : yv - 0.1);
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {		//downwards
			yv = (yv > 0 ? (yv < v ? yv + 0.1 : v) : yv + 0.1);
		}
	}

}
void update() {
	mycount = mycount % 100 + 1;
	if (mycount % 3 == 0 && alive) {
		// update player
		if (xv > 0)
			xv = (xv > 0.2 ? xv - 0.2 : 0);
		else if (xv < 0)
			xv = (xv < -0.2 ? xv + 0.2 : 0);
		if (yv > 0)
			yv = (yv > 0.2 ? yv - 0.2 : 0);
		else if (yv < 0)
			yv = (yv < -0.2 ? yv + 0.2 : 0);
		px += xv;
		py += yv;
		// update monsters
		for (auto &m : monsters) {
			m.changeposition();
			collide(m);
		}
	}

}
void updatedraw() {
	// draw walls and dots
	int row = 0, col = 0;
	for (int i = 0; i < high / blocksize; i++) {
		col = 0;
		for (int j = 0; j < width / blocksize; j++) {
			if (dots[i][j] == 0) {
				putimage(col, row, &dot, SRCCOPY);
			}
			else if (dots[i][j] == 3) {
				putimage(col, row, &bkimage, SRCCOPY);
			}
			col += blocksize;
		}
		row += blocksize;
	}
	// draw monsters
	setfillcolor(WHITE);
	for (auto &m : monsters) {
		m.x = m.x > width ? 0 : (m.x < 0 ? width : m.x);
		m.y = m.y > high ? 0 : (m.y < 0 ? high : m.y);
		fillcircle(m.x, m.y, radius);
	}
	// draw player
	setfillcolor(WHITE);
	px = px > width ? 0 : (px < 0 ? width : px);
	py = py > high ? 0 : (py < 0 ? high : py);
	fillcircle(px, py, radius);
}
void showexplod(int x, int y) // show explod process in (x,y)
{
	x -= blocksize / 2;
	y -= blocksize / 2;
	putimage(x, y, &explod1, SRCCOPY); Sleep(exptime);
	FlushBatchDraw(x, y, x + expsize, y + expsize);
	putimage(x, y, &explod2, SRCCOPY); Sleep(exptime);
	FlushBatchDraw(x, y, x + expsize, y + expsize);
	putimage(x, y, &explod3, SRCCOPY); Sleep(exptime);
	FlushBatchDraw(x, y, x + expsize, y + expsize);
	putimage(x, y, &explod4, SRCCOPY); Sleep(exptime);
	FlushBatchDraw(x, y, x + expsize, y + expsize);
	putimage(x, y, &explod5, SRCCOPY); Sleep(exptime);
	FlushBatchDraw(x, y, x + expsize, y + expsize);
	putimage(x, y, &explod6, SRCCOPY); Sleep(exptime);
	FlushBatchDraw(x, y, x + expsize, y + expsize);
	putimage(x, y, &explod7, SRCCOPY); Sleep(exptime);
	FlushBatchDraw(x, y, x + expsize, y + expsize);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	fillrectangle(x, y, x + expsize, y + expsize); Sleep(exptime);
	FlushBatchDraw(x, y, x + expsize, y + expsize);
	if (IDOK == MessageBox(start_screen, "Do you want to restart?", "You are dead.", MB_OKCANCEL)) {
		alive = 0;
	}
}
double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
void collide() {
	int row = 0, col = 0;
	for (int i = 0; i < high / blocksize; i++) {
		col = 0;
		for (int j = 0; j < width / blocksize; j++) {
			int result = dots[i][j], offset = blocksize / 2;
			if (result == 0) {
				if (abs(px - col - offset) < radius) {
					if (abs(py - row - offset) < radius) {
						dots[i][j] = 3;
					}
				}
			}
			else if (result == 1 || result == 2) {
				if (dist(px, py, col + offset, row + offset) < radius + sqrt(2) * offset) {
					if (abs(px - col - offset) < radius + offset) {
						if (abs(py - row - offset) < radius + offset) {
							px -= xv;
							xv = 0;
						}
					}
					if (abs(py - row - offset) < radius + offset) {
						if (abs(px - col - offset) < radius + offset) {
							py -= yv;
							yv = 0;
						}
					}
				}
			}
			else {
				/*
				showexplod((int)px / blocksize * blocksize, (int)py / blocksize * blocksize);
				xv = 0;
				yv = 0;
				alive = 0;
				*/
			}
			col += blocksize;
		}
		row += blocksize;
	};

}
void collide(monster& m) {
	int row = 0, col = 0;
	for (int i = 0; i < high / blocksize; i++) {
		col = 0;
		for (int j = 0; j < width / blocksize; j++) {
			int result = dots[i][j], offset = blocksize / 2;
			if (result == 1 || result == 2) {
				if (dist(m.x, m.y, col + offset, row + offset) < 1 + radius + sqrt(2) * offset) {
					if (abs(m.x - col - offset) < 1 + radius + offset) {
						if (abs(m.y - row - offset) < 1 + radius + offset) {
							m.x -= m.xv;
							m.xv = 0;
						}
					}
					if (abs(m.y - row - offset) < 1 + radius + offset) {
						if (abs(m.x - col - offset) < 1 + radius + offset) {
							m.y -= m.yv;
							m.yv = 0;
						}
					}
				}
			}
			else if (dist(px, py, m.x, m.y) < radius + radius) {
				showexplod((int)px, (int)py);
				xv = 0;
				yv = 0;
				return;
			}
			col += blocksize;
		}
		row += blocksize;
	};

}
void drawmap() {
	ifstream ifs;
	// open file
	ifs.open(_T("D:\\VS C++项目\\GameTry1\\GameTry1\\image\\map.txt"), ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败！" << endl;
		return;
	}
	string buff;
	int row = 0, col, r = 0, c;
	while (getline(ifs, buff)) {
		col = 0;
		c = 0;
		for (char ch : buff) {
			if (ch == '1') {
				putimage(col, row, &block1, SRCCOPY);
				dots[r][c] = 1;
			}
			else if (ch == '0') {
				dots[r][c] = 0;
				putimage(col, row, &dot, SRCCOPY);
			}
			else if (ch == '2') {
				dots[r][c] = 2;
				putimage(col, row, &block2, SRCCOPY);
			}
			else dots[r][c] = 3;
			col += blocksize;
			c++;
		}
		r++;
		row += blocksize;
	}
	ifs.close();
}
