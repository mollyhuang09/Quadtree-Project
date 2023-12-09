#ifndef POINTDICTIONARY_HPP
#define POINTDICTIONARY_HPP

#include <iostream>
#include <string>

#include "Point.hpp"

class PointDictionary{
public: 
    PointDictionary(int m);

    ~PointDictionary();

    void addPoint(Point *point);

    bool duplicate(double x, double y);

    void nearest(double x, double y);

    void num();
private: 
    int max_points; 
    int capacity; 
    int size;
    Point **point_dictionary_array;

};

#endif
