#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include "change2rightAngle.h"

double a = 0.4;//加速度
double circleVelocity = 0.5;
double maxDistance = 300;
double program_x = 600;
double program_y = 600;
typedef struct centralBall{
	double x;
	double y;
	double radius;
}CENTRALBALL;
typedef struct mainBall{
	double distance;
	double angle;
	double x;
	double y;
	double radius;
	double velocity;
}MAINBALL;

CENTRALBALL centball;
MAINBALL mainball;

void defaultData(){
	centball.x = program_x/2;
	centball.y = program_y/2;
	centball.radius = 30;
	mainball.distance = maxDistance;
	mainball.angle = 0;
	mainball.radius = 10;
	mainball.velocity = 0;
	IMAGE bkgrd_img;
	IMAGE sun_img;
	IMAGE r_sun_img;
	change2rightAngle(centball.x,centball.y,mainball.distance,mainball.angle,&mainball.x,&mainball.y);//初始化值
	initgraph(program_x,program_y);
	
	//setbkcolor(WHITE);
	//cleardevice();
	loadimage(&bkgrd_img,_T("./img/background.jpg"));
	loadimage(&sun_img,_T("./img/sun.jpeg"));
	loadimage(&r_sun_img,_T("./img/sunAfter.jpg"));
	//putimage(0,0,&bkgrd_img);
	//putimage(0,0,&r_sun_img, NOTSRCERASE); 
	//putimage(0,0,&sun_img);
}
void logicFunction(){
	change2rightAngle(centball.x,centball.y,mainball.distance,mainball.angle,&mainball.x,&mainball.y);

	if(mainball.angle==360) mainball.angle = 0;
	if(mainball.distance < mainball.radius + centball.radius + mainball.velocity) mainball.velocity = -mainball.velocity -a;
	if(mainball.distance >= maxDistance) mainball.velocity = a;
	
	if(kbhit()){
		char ch = getch();
		if(ch == ' '){
				mainball.angle += circleVelocity;	
		}		
	}
	
	mainball.distance -= mainball.velocity;
	mainball.velocity += a;
}

void printAll(){
	cleardevice();
	circle(centball.x, centball.y,centball.radius);
	circle(mainball.x,mainball.y,mainball.radius); 
	line(centball.x,centball.y,mainball.x,mainball.y);
	setlinecolor(WHITE);
	
	Sleep(20);
	
	logicFunction();
}

void start_up(){
	defaultData();
	getch();
	BeginBatchDraw();
	while(1){
		printAll();
		FlushBatchDraw();
	}
	EndBatchDraw();
	getch();
	closegraph();

}