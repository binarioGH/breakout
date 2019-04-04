#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <list>
using namespace std;

void gotoxy(int x, int y);
void hideCursor(void);
void drawBorders(int bx, int by);
void cls(void); 
class Block{
private:
	int x,y;
public:
	Block(int nx, int ny){
		x = nx;
		y = ny;
		gotoxy(x,y);printf("%c", 178);
	}
	~Block(void){
		gotoxy(x,y);printf("*");
		Sleep(300);
		printf(" ");
	}
	int X(void){return x;}
	int Y(void){return y;}
};

class Paddle{
private:
	int x, y;
	void collition(void);
	void clean(void){
		int nx = 0;
		for(nx;nx <=80;nx++){
			gotoxy(nx,20);printf(" ");
		}
		return;
	}
public:
	Paddle(int _x, int _y){
		x = _x;
		y = _y;
	}
	~Paddle(void){
		int nx = x-3;
		for(nx;nx<=x+3;nx++){
			gotoxy(nx,y);printf(" ");
			Sleep(300);
		}
	}
	int X(void){return x;}
	int Y(void){return y;}
	void move(void);
	void draw(void);
	

};
void Paddle::collition(void){
	if(x-3 <= 2){
		x += 1;
	}
	if(x+3 >= 78){
		x -= 1;
	}
	return;
}

void Paddle::draw(void){
	int ax;
	for(ax=x-3;ax<=x+3;ax++){
		gotoxy(ax,y);printf("%c",223);
	}

	return;
}

void Paddle::move(void){
	if(kbhit()){
		char key = getch();
		switch(key){
			case 97:x-=2;Paddle::clean();break;
			case 100:x+=2;Paddle::clean();break;
		}
	}
	Paddle::collition();
	Paddle::draw();
	return;
}

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
	~Ball(void){
		gotoxy(x,y);printf("*");
		Sleep(300);
		gotoxy(x,y);printf(" ");
	}
	void move(void);
	void display_lives(void){
		gotoxy(24,1);printf("        ");
		gotoxy(24,1);printf("%c: %i",03, lives);
		return;
	}
	int X(void){return x;}
	int Y(void){return y;}
	int XD(void){return xd;}
	int YD(void){return yd;}
	void reload(void){
		lives -= 1;
		display_lives();
		x = 39;
		y = 11;
		xd = 0;
		yd = 1;
		return;
	}
	void changeDirection(int nx, int ny){
		xd = nx;
		yd = ny;
		return;
	}
	int lives = 3;
};
void Ball::move(void){
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
	if(y <= 2){
		y+= yd*-1;
		changeDirection(xd, yd*-1);
	}
	if(y >= 22){
		reload();
	}
	return;
}

int main(int nArgs, char* ARGV[]){
	cls();
	hideCursor();
	drawBorders(32,219);
	Ball b (39, 11);
	b.changeDirection(1,1);
	b.display_lives();
	Paddle p (39,20);
	int totalBlocks = 0;
	list<Block*> blocks;
	list<Block*>::iterator bit; //block iterator
	int x, y;
	//generate blocks
	for(y=4;y<8;y++){
		for(x=36;x<=42;x++){
			blocks.push_back(new Block(x,y));
			totalBlocks += 1;
		}
	}
	gotoxy(12,1);printf("             ");
	gotoxy(12,1);printf("Blocks: %i",totalBlocks);
	while(b.lives > 0 && totalBlocks > 0){
		p.move();
		b.move();
		if((b.X() >= p.X()-3 && b.X() <= p.X()+3) && b.Y() == p.Y()){
			if(b.X() <= p.X() -1 && b.X() >= p.X()-3){
				b.changeDirection(-1, -1); 
			}
			else if(b.X() >= p.X() + 1 && b.X() <= p.X()+3){
				b.changeDirection(1,-1);
			}
			else{
				b.changeDirection(0,-1);
			}
		}
		for(bit=blocks.begin();bit!=blocks.end();bit++){
			if(b.X() == (*bit)->X() && b.Y() == (*bit)->Y()){
				delete(*bit);
				bit = blocks.erase(bit);
				b.changeDirection(b.XD()*-1,b.YD()*-1);
				totalBlocks -= 1;
				gotoxy(12,1);printf("             ");
	            gotoxy(12,1);printf("Blocks: %i",totalBlocks);
			}
		}
		Sleep(100);
	}
	for(bit=blocks.begin();bit!=blocks.end();bit++){
		delete (*bit);
		bit = blocks.erase(bit);
	}
	delete &b;
	delete &p;
	cls();
	drawBorders(32, 219);
	gotoxy(35,11);printf("GAME OVER");
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
