#ifndef NODE_HPP
#define NODE_HPP

#include "PointDictionary.hpp"
#include "Point.hpp"
//#include "illegal_exception.cpp"

#include <iostream>
#include <string>

class Node {
public: 
    //constructor
    Node(int m, double x0, double y0, double x1, double y1, PointDictionary *new_pointdictionary);

    Node(int m, double x0, double y0, double x1, double y1, PointDictionary *new_pointdictionary, Point* head);

    //destructor
    ~Node();

    bool checkInsert(double x, double y);

    void insert(double x, double y, bool split_node);

    void split();

    int pointPos(double x, double y);

    Point* range(double xr0, double yr0, double xr1, double yr1, Point* head);
    
    void displayRange(double xr0, double yr0, double xr1, double yr1, Point* head);

    void search(double x, double y, double d);

private: 
    Point **points_array; //A pointer variable pointing to pointers of instances of Point objects
    Point *head_point;
    double x0_coor;
    double y0_coor;
    double x1_coor;
    double y1_coor;
    int array_index;
    int capacity;
    Node *top_left;
    Node *top_right;
    Node *bottom_left;
    Node *bottom_right;
    PointDictionary *pointdictionary;
};

#endif
