#include "Point.hpp"

#include <iostream>
#include <string>

using namespace std; 

//constructor 
Point::Point(){
    x_coor = 0;
    y_coor = 0;
    next_point = nullptr;
}

Point::Point(double x, double y){
    x_coor = x; 
    y_coor = y;
    next_point = nullptr;
}

//destructor
Point::~Point(){
    next_point = nullptr;
}

double Point::get_x_coor(){
    return x_coor;
}

double Point::get_y_coor(){
    return y_coor;
}

Point *Point::get_next() { return next_point; }

void Point::set_next(Point *new_next_point){
    next_point = new_next_point;
}
