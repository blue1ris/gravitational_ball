#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include "change2rightAngle.h"

int a = 1;//加速度
int circleVelocity = 2;
int maxDistance = 220;
int program_x = 480;
int program_y = 640;
typedef struct centralBall{
	int x;
	int y;
	int radius;
}CENTRALBALL;
typedef struct mainBall{
	int distance;
	double angle;
	int x;
	int y;
	int radius;
	int velocity;
}MAINBALL;

CENTRALBALL centball;
MAINBALL mainball;

void start_up(){
	centball.x = program_x/2;
	centball.y = program_y/2;
	centball.radius = 30;
	mainball.distance = 200;
	mainball.angle = 0;
	mainball.radius = 10;
	mainball.velocity = 1;
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
	putimage(0,0,&bkgrd_img);
	//putimage(0,0,&r_sun_img, NOTSRCERASE); 
	//putimage(0,0,&sun_img);
	getch();
	while(1){
		circle(centball.x, centball.y,centball.radius);
		circle(mainball.x,mainball.y,mainball.radius); 
		line(centball.x,centball.y,mainball.x,mainball.y);
		setlinecolor(WHITE);
			
		Sleep(40);

		putimage(0,0,&bkgrd_img);
		//putimage(0,0,&sun_img);
		change2rightAngle(centball.x,centball.y,mainball.distance,mainball.angle,&mainball.x,&mainball.y);

		if(mainball.angle==360) mainball.angle = 0;
		if(mainball.distance <= mainball.radius + centball.radius) mainball.velocity = -mainball.velocity;

		if(mainball.distance >= maxDistance) mainball.velocity = 1;
		
		if(kbhit()){
			char ch = getch();
			if(ch == ' '){
					mainball.angle += circleVelocity;	
				}		
		}
		
		mainball.distance -= mainball.velocity;
		mainball.velocity += a;
	}
	getch();
	closegraph();

}