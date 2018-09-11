#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include "change2rightAngle.h"
#define normalball_number  10
#define superball_number  10
#define randomball_number 30 //随机球总数
#define randomball_angle 360

double ratio = 300;//缩放比例
double superRatio = 1.4;//从下网上撞到小球的速度突增倍数
double angleVelocity = 0.75;//两球之间角增加量
double minDistance = 400;//最近边界（开始缩放边界）
double maxDistance = 400;//最远边界
double program_x = 900;
double program_y = 900;//屏幕大小
IMAGE bkgImg;//背景图片
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
NORMALBALL randomball[randomball_number];
int random_distance[randomball_number];
int random_angle[randomball_angle];

void creatRandom(int num[],int cnt){
	int x;
	srand(unsigned(time(NULL)));
	for(int i=0;i<cnt;i++){
		leap:x=rand()%cnt; 
		for(int j=0;j<i;j++){
			if(num[j]==x){
				goto leap;
			}
		}
		num[i]=x;
		printf("%d ",num[i]); 
	}
	printf("\n");
}

void defaultData(){
	centpoint.angle = 0;
	centpoint.radius = 24;
	centball.angle = 180;
	centball.distance = 250;
	centball.final_radius = 20;
	centball.velocity = 0;
	centball.acceleration = 0.04;
	mainball.angle = 0;
	mainball.distance = 200;
	mainball.final_radius = 4;
	mainball.velocity = 0;
	mainball.acceleration = 0.02;

	centball.radius = centball.final_radius * ratio / (mainball.distance + centball.distance);
	mainball.radius = mainball.final_radius * ratio / (mainball.distance + centball.distance);
	
	change2rightAngle(program_x/2,program_y/2,centpoint.radius,centpoint.angle,&centpoint.x,&centpoint.y);
	change2rightAngle(centpoint.x,centpoint.y,mainball.distance,mainball.angle,&mainball.x,&mainball.y);
	change2rightAngle(centpoint.x,centpoint.y,centball.distance,centball.angle,&centball.x,&centball.y);
	
	creatRandom(random_angle,randomball_angle);
	creatRandom(random_distance,randomball_number);
//随机球密度，半径控制器
	for(int i = 0;i < randomball_number;i++){
		random_distance[i] *= 5; 
	}
//	
	for(int i = 0;i < randomball_number;i++){
		randomball[i].kind = 1;
		randomball[i].angle = random_angle[i];
		randomball[i].distance = 20 * random_distance[i] * ratio / (mainball.distance + centball.distance);
		randomball[i].radius = 4 * ratio / (mainball.distance + centball.distance);
		change2rightAngle(centball.x,centball.y,randomball[i].distance,randomball[i].angle,&randomball[i].x,&randomball[i].y);
	}
	for(int i = 0;i < normalball_number;i++){
		normalball[i].kind = 1;
		normalball[i].angle = 36*i;
		normalball[i].distance = 50 * ratio / (mainball.distance + centball.distance);
		normalball[i].radius = 4 * ratio / (mainball.distance + centball.distance);
		change2rightAngle(centball.x,centball.y,normalball[i].distance,normalball[i].angle,&normalball[i].x,&normalball[i].y);
	}
	
}
void logicFunction(){
	
	centball.radius = centball.final_radius * ratio / (mainball.distance + centball.distance);
	mainball.radius = mainball.final_radius * ratio / (mainball.distance + centball.distance);
	
	change2rightAngle(program_x/2,program_y/2,centpoint.radius,centpoint.angle,&centpoint.x,&centpoint.y);
	change2rightAngle(centpoint.x,centpoint.y,mainball.distance,mainball.angle,&mainball.x,&mainball.y);
	change2rightAngle(centpoint.x,centpoint.y,centball.distance,centball.angle,&centball.x,&centball.y);

	for(int i = 0;i < randomball_number;i++){
		randomball[i].angle = random_angle[i];
		randomball[i].distance = 5 * random_distance[i] * ratio / (mainball.distance + centball.distance);
		randomball[i].radius = 8 * ratio / (mainball.distance + centball.distance);
		change2rightAngle(centball.x,centball.y,randomball[i].distance,randomball[i].angle,&randomball[i].x,&randomball[i].y);
	}

	for(int i = 0;i < normalball_number;i++){
		normalball[i].angle = 36*i;
		normalball[i].distance = 50 * ratio / (mainball.distance + centball.distance);
		normalball[i].radius = 4 * ratio / (mainball.distance + centball.distance);
		change2rightAngle(centball.x,centball.y,normalball[i].distance,normalball[i].angle,&normalball[i].x,&normalball[i].y);
	}
	//中心球环
	for(int i = 0;i< normalball_number;i++){
		//碰到球且速度向下
		if((sqrt(pow((normalball[i].x - mainball.x),2)+pow((normalball[i].y - mainball.y),2)) < normalball[i].radius + mainball.radius) && (mainball.velocity > 0) && (normalball[i].kind != -1)){
			centball.velocity = -centball.velocity * 0.98;
			mainball.velocity = -mainball.velocity * 0.98;
			normalball[i].kind = -1;
		}else if((sqrt(pow((normalball[i].x - mainball.x),2)+pow((normalball[i].y - mainball.y),2)) < normalball[i].radius + mainball.radius) && (mainball.velocity < 0) && (normalball[i].kind != -1)){
		//碰到球且速度向上
			centball.velocity *= superRatio;
			mainball.velocity *= superRatio;
			normalball[i].kind = -1;
		}
	}
	//随机球
	for(int i = 0;i< randomball_number;i++){
		//碰到球且速度向下
		if((sqrt(pow((randomball[i].x - mainball.x),2)+pow((randomball[i].y - mainball.y),2)) < randomball[i].radius + mainball.radius) && (mainball.velocity > 0) && (randomball[i].kind != -1)){
			centball.velocity = -centball.velocity * 0.98;
			mainball.velocity = -mainball.velocity * 0.98;
			randomball[i].kind = -1;
		}else if((sqrt(pow((randomball[i].x - mainball.x),2)+pow((randomball[i].y - mainball.y),2)) < randomball[i].radius + mainball.radius) && (mainball.velocity < 0) && (randomball[i].kind != -1)){
		//碰到球且速度向上
			centball.velocity *= superRatio;
			mainball.velocity *= superRatio;
			randomball[i].kind = -1;
		}
	}
	//碰撞中心球
	if(sqrt(pow((centball.x - mainball.x),2)+pow((centball.y - mainball.y),2)) < centball.radius + mainball.radius){
		_getch();
		centball.velocity = -centball.velocity;
		mainball.velocity = -mainball.velocity;
		
	}
	//球边界
	if(centball.distance > maxDistance){
		centball.velocity = centball.acceleration;
		mainball.velocity = mainball.acceleration; 
	}
	if(_kbhit()){
		char ch = _getch();
		if(ch == ' '){
				mainball.angle += angleVelocity;
				centball.angle += angleVelocity;
				//if(centball.distance + mainball.distance > minDistance) centpoint.angle += angleVelocity;
		}		
	}
	centball.distance -= centball.velocity;
	centball.velocity += centball.acceleration;
	
	mainball.distance -= mainball.velocity;
	mainball.velocity += mainball.acceleration;

	
}

void printAll(){
	cleardevice();
	loadimage(&bkgImg,_T(".//img//background.jpg"));
	putimage(0,0,900,900,&bkgImg,900-centball.x,900-centball.y);
	setfillcolor(WHITE);
	for(int i = 0;i < normalball_number;i++){
		if(normalball[i].kind != -1){
			fillcircle(normalball[i].x,normalball[i].y,normalball[i].radius);
		}
	}
	for(int i = 0;i < randomball_number;i++){
		if(randomball[i].kind != -1){
			fillcircle(randomball[i].x,randomball[i].y,randomball[i].radius);
		}
	}
	fillcircle(centball.x,centball.y,centball.radius);
	fillcircle(mainball.x,mainball.y,mainball.radius);
	setfillcolor(WHITE);
	line(centball.x,centball.y,mainball.x,mainball.y);
	setlinecolor(WHITE);
	Sleep(7);
	
	
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