#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <string>

class Point {
public: 
    //constructor
    Point();

    Point(double x, double y);

    //destructor
    ~Point();

    double get_x_coor();

    double get_y_coor();

    Point* get_next();

    void set_next(Point* new_next_point);

private: 
    double x_coor;
    double y_coor; 
    Point* next_point;
};

#endif
