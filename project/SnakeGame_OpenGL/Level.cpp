#include "Level.h"
#include<cstdlib>
#include <chrono>

void Level::GenFood()
{
	float x, y;
	
	do {
		x = rand() % 38 * snake.width - 0.95; 
		y = rand() % 38 * snake.width - 0.95;
	} while (snake.contains(x, y));
	cout << x
		<< ","
		<< y
		<< endl;
	food.upgrade(x, y);
}

void Level::IsEat()
{
	Cube& head = snake.GetHead();
	if (abs(head.x - food.x) <= 1e-6 && abs(head.y - food.y) <= 1e-6) {
		snake.eat();
		GenFood();
		food_eaten_sum++;
	}
}

void Level::ChangeSpeed()
{
	if (food_eaten_sum == 5) {
		sleep_duration = 150;
	}
	else if (food_eaten_sum == 12) {
		sleep_duration = 100;
	}
	else if (food_eaten_sum == 20) {
		sleep_duration = 80;
	}
	else if (food_eaten_sum == 30) {
		sleep_duration = 40;
	}
	else if (food_eaten_sum == 45) {
		sleep_duration = 20;
	}
}

Level::Level():thread_run(true),snake(0.0, 0.0),food(-1,-1),game_thread(&Level::GameTick,this)
{
	time_t t;
	time(&t);
	srand(t);
	GenFood();
}

Level::~Level()
{
	thread_run = false;
	game_thread.join();
}

void Level::GameTick()
{
	
	while (thread_run) {
		std::chrono::milliseconds dura(sleep_duration);
		std::this_thread::sleep_for(dura);
		IsEat();
		snake.update();
		//GenFood();
		ChangeSpeed();
	}

}

void Level::draw()
{
	
	food.draw();
	snake.draw();
}

void Level::setDirect(enum Direct d)
{
	snake.setDirect(d);
}
