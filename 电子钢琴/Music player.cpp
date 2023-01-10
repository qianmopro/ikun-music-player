#include<stdio.h>
#include <iostream>
#include <graphics.h>// 依赖于easyx     中文官方网站：https://easyx.cn/
#include <Windows.h>
#include <mmsystem.h>	//音乐
#pragma comment(lib,"winmm.lib")
#include <conio.h>//控制

using namespace std;

//定义常量，注意：后面无需加分号
#define WIDTH 350//窗口的宽
#define HEIGHT 650//窗口的高
#define NUM 3// 3 表示图片的数量（不包括灰色图片）

IMAGE img[NUM];//定义三张图片
IMAGE down;
void playmusic(int idx);
void initGame();
void showGame();
void ctolGame();

int main() {
	mciSendString("open begin.mp3", NULL, NULL, NULL);
	mciSendString("play begin.mp3", 0, 0, 0);
	initGame();
	while (1)
	{
		showGame();
		ctolGame();
	}
	while(1);
	return 0;
}
//准备
void initGame() {
	initgraph(NUM * WIDTH, HEIGHT,SHOWCONSOLE);
	char buff[256];

	//加载图片
	for (int i = 0; i < NUM; i++) {
	memset(buff, 0, 256);//清空数组
	sprintf(buff, "images\\%d.png", i + 1);
	loadimage(&img[i], buff, WIDTH, HEIGHT, true);
	}
	loadimage(&down, "images\\down.png", WIDTH, HEIGHT, true);
}
//显示
void showGame() {
	//贴图片
	for (int i = 0; i < NUM; i++) {
		putimage(i * WIDTH, 0, &img[i]);
	}
}
//控制
void  ctolGame() {
	int n;
	n= _getch();
	printf("%d\n", n);
	//启用多线程
	CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE) playmusic,(LPVOID)(n-48),NULL,NULL);
}
//播放对应的音乐
void playmusic(int idx) {
	char buff[256];
	sprintf(buff, "open %d.mp3 alias m", idx);
	mciSendString(buff,0,0,0);
	mciSendString("play m",  0, 0, 0);
	putimage((idx-1)*WIDTH,0,&down);//添加一张灰色图片
	Sleep(50);
	putimage((idx-1)*WIDTH,0,&img[idx-1]);//再返回原来的图片
	Sleep(3000);
	mciSendString("close m", 0, 0, 0);
}