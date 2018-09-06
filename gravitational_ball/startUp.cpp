#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "change2rightAngle.h"
#define normalball_number  10
#define superball_number  10


double ratio = 250;//缩放比例
double angleVelocity = 1.5;//两球之间角增加量
double minDistance = 400;//最近边界（开始缩放边界）
double maxDistance = 400;//最远边界
double program_x = 600;
double program_y = 600;//屏幕大小
typedef struct centPoint{
	double x;
	double y;
	double angle;
	double radius;
}CENTPOINT;//中心圆点
typedef struct Ball{
	double acceleration;
	double distance;
	double angle;
	double x;
	double y;
	double radius;
	double final_radius;
	double velocity;
}BALL;//中心球，操作球

typedef struct normalBall{
	double distance;
	double angle;
	double x;
	double y;
	double radius;
	int kind;
}NORMALBALL;//障碍球，道具

BALL centball;
BALL mainball;
CENTPOINT centpoint;
NORMALBALL normalball[normalball_number];
NORMALBALL superball[superball_number];

void defaultData(){
	centpoint.angle = 0;
	centpoint.radius = 24;
	centball.angle = 180;
	centball.distance = 250;
	centball.final_radius = 20;
	centball.velocity = 0;
	centball.acceleration = 0.12;
	mainball.angle = 0;
	mainball.distance = 200;
	mainball.final_radius = 4;
	mainball.velocity = 0;
	mainball.acceleration = 0.07;
	
}
void logicFunction(){
	
	centball.radius = centball.final_radius * ratio / (mainball.distance + centball.distance);
	mainball.radius = mainball.final_radius * ratio / (mainball.distance + centball.distance);
	
	change2rightAngle(program_x/2,program_y/2,centpoint.radius,centpoint.angle,&centpoint.x,&centpoint.y);
	change2rightAngle(centpoint.x,centpoint.y,mainball.distance,mainball.angle,&mainball.x,&mainball.y);
	change2rightAngle(centpoint.x,centpoint.y,centball.distance,centball.angle,&centball.x,&centball.y);

	for(int i = 0;i < normalball_number ;i++){
		normalball[i].angle = 36*i;
		normalball[i].distance = 50 * ratio / (mainball.distance + centball.distance);;
		normalball[i].radius = 4 * ratio / (mainball.distance + centball.distance);
		change2rightAngle(centball.x,centball.y,normalball[i].distance,normalball[i].angle,&normalball[i].x,&normalball[i].y);
	}
	
	if(centball.distance + mainball.distance < centball.radius + mainball.radius){
		centball.velocity = -centball.velocity;
		mainball.velocity = -mainball.velocity;
	}
	if(centball.distance + mainball.distance > maxDistance){
		centball.velocity = centball.acceleration;
		mainball.velocity = mainball.acceleration; 
	}
	if(_kbhit()){
		char ch = _getch();
		if(ch == ' '){
				mainball.angle += angleVelocity;
				centball.angle += angleVelocity;
				if(centball.distance + mainball.distance > minDistance) centpoint.angle += angleVelocity;
		}		
	}
	centball.distance -= centball.velocity;
	centball.velocity += centball.acceleration;
	//if(centball.distance + mainball.distance > minDistance){
		mainball.distance -= mainball.velocity;
		mainball.velocity += mainball.acceleration;
	//}
	
}

void printAll(){
	cleardevice();
	//for(int i = 0;i < normalball_number;i++){
	//	circle(normalball[i].x,normalball[i].y,normalball[i].radius);
	//}
	setfillcolor(WHITE);
	for(int i = 0;i < normalball_number;i++){
		fillcircle(normalball[i].x,normalball[i].y,normalball[i].radius);
	}
	fillcircle(centball.x, centball.y,centball.radius);
	fillcircle(mainball.x,mainball.y,mainball.radius);
	line(centball.x,centball.y,mainball.x,mainball.y);
	setlinecolor(WHITE);
	
	Sleep(15);
	
	
}

void start_up(){
	defaultData();
	initgraph(program_x,program_y);
	_getch();
	BeginBatchDraw();
	while(1){
		logicFunction();
		printAll();
		FlushBatchDraw();
	}
	EndBatchDraw();
	_getch();
	closegraph();

}