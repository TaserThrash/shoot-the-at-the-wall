#include <iostream>
#include "windows.h"
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

ofstream file;

BOOL scpt(int x,int y){
	COORD c;
	c.X=x;
	c.Y=y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void rect(int x,int yy,int w,int h,string c){
	string cc="";
	for(int i=0;i<w;i++){
		cc+=c;
	}
	for(int y=0;y<h;y++){
		scpt(x,yy+y);
		cout << cc;
	}
}

void line(float x,float y,int d,float r,string c,char cc){
	for(int i=0;i<d;i++){
		if(!(x>=0 && x<600 && y>=0 && y<100)){
			break;
		}
		scpt(x,y);
		cout << c+cc;
		x+=sin(r);
		y+=cos(r);
	}
}

void linee(float x,float y,int d,float vx,float vy,string c,char cc){
	for(int i=0;i<d;i++){
		if(!(x>=0 && x<600 && y>=0 && y<100)){
			break;
		}
		scpt(x,y);
		cout << c+cc;
		x+=vx;
		y+=vy;
	}
}

float x=10;
float y=90;
float r=0;
float vy=0;
float vx=0;
float ty=50;
float tvy=1;
int shots=0;
int hits=0;

int main(){
	while(true){
		x=10;
		y=90;
		r=3.1415926*0.945;
		tvy=1;
		while(!(GetAsyncKeyState(VK_SPACE) < 0)){
			linee(x,y,10,vx,vy," ",' ');
			line(300,ty,10,0,"",' ');
			ty+=tvy;
			r+=(GetAsyncKeyState(VK_LEFT) < 0)*0.05;
			r-=(GetAsyncKeyState(VK_RIGHT) < 0)*0.05;
			y-=GetAsyncKeyState(VK_UP) < 0;
			y+=GetAsyncKeyState(VK_DOWN) < 0;
			vx=sin(r)*1;
			vy=cos(r)*1;
			if(ty<0){
				tvy*=-1;
			}
			if(ty>90){
				tvy*=-1;
			}
			linee(x,y,10,vx,vy,"",char(219));
			line(300,ty,10,0,"",char(219));
			scpt(0,0);
			cout << "HITS: " << hits << "  SHOTS: " << shots;
			for(int j=0;j<600;j++){
				scpt(0,0);
			}
		}
		vx=sin(r)*1.5;
		vy=cos(r)*1.5;
		while(y<100 && x<600){
			linee(x,y,10,vx,vy," ",' ');
			line(300,ty,10,0,"",' ');
			x+=vx*3;
			y+=vy*3;
			tvy*=1.001;
			vy+=0.0075;
			ty+=tvy;
			vx-=0.0075*vx>0.025;
			//vx+=0.01;
			if(ty<0){
				tvy=1;
			}
			if(ty>90){
				tvy=-1;
			}
			if(sin(r)>0){
				r-=0.01;
			}
			if(abs(x-300)<8 && y+cos(r)*5<ty+10 && y+cos(r)*5>ty){
				hits++;
				break;
			}
			linee(x,y,10,vx,vy,"",char(219));
			line(300,ty,10,0,"",char(219));
			for(int j=0;j<600;j++){
				scpt(0,0);
			}
		}
		shots++;
		line(300,ty,10,0,"",' ');
	}
}
