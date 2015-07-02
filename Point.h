#pragma once

#ifndef GAME_OF_LIFE_POINT_H
#define GAME_OF_LIFE_POINT_H

struct Point{
	int x;
	int y;

	Point(int x, int y) : x(x), y(y){}
};

bool operator==(const Point& pnt_1, const Point& pnt_2);
bool operator!=(const Point& pnt_1, const Point& pnt_2);

#endif