#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include "change2rightAngle.h"
#define normalball_number  10
#define superball_number  10

double fin_main_radius = 8;
double fin_cent_radius = 3;
double ratio = 400;//缩放比例
double a = 0.07;//加速度
double circleVelocity = 0.7;
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
typedef struct normalBall{
	double distance;
	double angle;
	double x;
	double y;
	double radius;
	int kind;
}NORMALBALL;

CENTRALBALL centball;
MAINBALL mainball;
NORMALBALL normalball[normalball_number];
NORMALBALL superball[superball_number];

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
	for(int i = 0;i < normalball_number;i++){
		normalball[i].distance = 70;
		normalball[i].angle = 36 * i;
		normalball[i].radius = 2;
		change2rightAngle(centball.x,centball.y,normalball[i].distance,normalball[i].angle,&normalball[i].x,&normalball[i].y);
	}
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
	//if(centball.radius>fin_cent_radius) centball.radius =fin_cent_radius * ratio / mainball.distance;
	if(mainball.radius>fin_main_radius) mainball.radius =fin_main_radius * ratio / mainball.distance;
	for(int i = 0;i < normalball_number;i++){
		normalball[i].radius = 4 * ratio / mainball.distance;
	}
	change2rightAngle(centball.x,centball.y,mainball.distance,mainball.angle,&mainball.x,&mainball.y);
	if(mainball.angle==360) mainball.angle = 0;
	if(mainball.distance < mainball.radius + centball.radius ) mainball.velocity = -mainball.velocity -a;
	if(mainball.velocity == 0) mainball.velocity = a;
	
	if(kbhit()){
		char ch = getch();
		if(ch == ' '){
				mainball.angle += circleVelocity;	
		}		
	}
	//centball.x -= 0.1;
	//centball.y += 0.2;
	mainball.distance -= mainball.velocity;
	mainball.velocity += a;
}

void printAll(){
	cleardevice();
	for(int i = 0;i < normalball_number;i++){
		circle(normalball[i].x,normalball[i].y,normalball[i].radius);
	}
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