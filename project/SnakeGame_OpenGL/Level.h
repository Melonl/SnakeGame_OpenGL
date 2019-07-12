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
	atomic<bool> thread_run;//���ڽ����̵߳ı�־
	Snake snake;
	Food food;
	int sleep_duration = 200;//���Ƽ��
	int food_eaten_sum = 0;//�Ե���ʳ������
	thread game_thread;
	

	void GenFood();//�������ʳ��
	void IsEat();//�ж��Ƿ�Ե�ʳ�ﲢ����Ӧ����
	void ChangeSpeed();//���ݳԵ���ʳ�����������ٶ�
	void GameTick();//��Ϸ����ѭ��

public:
	Level();
	~Level();
	void draw();//���ƺ���
	void setDirect(enum Direct d);//������ͷ����

};
