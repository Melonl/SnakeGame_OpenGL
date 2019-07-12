#pragma once
#include "Snake.h"
#include <iostream>
#include<thread>
#include <ctime>
#include <atomic>  
#include"Food.h"

using namespace std;

class Level {

private:
	atomic<bool> thread_run;//用于结束线程的标志
	Snake snake;
	Food food;
	int sleep_duration = 200;//绘制间隔
	int food_eaten_sum = 0;//吃到的食物数量
	thread game_thread;
	

	void GenFood();//随机生成食物
	void IsEat();//判断是否吃到食物并做相应处理
	void ChangeSpeed();//根据吃到的食物数量调整速度
	void GameTick();//游戏绘制循环

public:
	Level();
	~Level();
	void draw();//绘制函数
	void setDirect(enum Direct d);//设置蛇头方向

};
