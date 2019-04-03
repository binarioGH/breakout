#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <list>
using namespace std;

void gotoxy(int x, int y);
void hideCursor(void);
void drawBorders(int bx, int by);
void cls(void);

class Ball{
private:
	int x,y;
	int xd=0, yd=1;
	void collition(void);
public:
	Ball(int _x, int _y){
		x = _x;
		y = _y;
	}
	~Ball(void){}
	void move(void);
	int X(void){return x;}
	int Y(void){return y;}
	int XD(void){return xd;}
	int YD(void){return yd;}
	void changeDirection(int nx, int ny){
		xd = nx;
		yd = ny;
		return;
	}
};
void Ball::move(void){
	gotoxy(20,24);printf("                ");
	gotoxy(20,24);printf("X: %i, Y; %i",x,y);
	gotoxy(x,y);printf("%c", 32);
	x += xd;
	y += yd;
	Ball::collition();
	gotoxy(x,y);printf("%c", 79);
	return; 
}
void Ball::collition(void){
	if(x >= 78 || x <= 2){
		x+= xd*-1;
		changeDirection(xd*-1, yd);
	}
	if(y >= 22 || y <= 2){
		y+= yd*-1;
		changeDirection(xd, yd*-1);
	}
	return;
}

int main(int nArgs, char* ARGV[]){
	cls();
	hideCursor();
	drawBorders(32,219);
	Ball b (39, 11);
	b.changeDirection(1,1);
	while(true){
		b.move();
		Sleep(100);
	}
	return 0;
}

void gotoxy(int x, int y){

	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
	return;
}

void hideCursor(void){
	HANDLE hCon; 
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 0;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hCon,&cci);
	return;
}
void drawBorders(int bx, int by){
	int x=2,y=2;
	for(x=2;x<=78;x++){
		y = 2;
		gotoxy(x,y);printf("%c", bx);
		y = 22;
		gotoxy(x,y);printf("%c",bx);
	}
	for(y=2;y<=22;y++){
		x=2;
		gotoxy(x,y);printf("%c", by);
		x=78;
		gotoxy(x,y);printf("%c", by);
	}
	return;
}

void cls(void){
	int x,y;
	for(y=0;y<=24;y++){
		for(x=0;x<=80;x++){
			gotoxy(x,y);printf("%c", 32);
		}
	}
	return;
}