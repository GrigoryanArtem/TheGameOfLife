#include "Point.h"

bool operator==(const Point& pnt_1, const Point& pnt_2){
	return pnt_1.x == pnt_2.x && pnt_1.y == pnt_2.y;
}

bool operator!=(const Point& pnt_1, const Point& pnt_2){
	return pnt_1.x != pnt_2.x || pnt_1.y != pnt_2.y;
}