#include "PointDictionary.hpp"

#include <iostream>
#include <string>
#include <cmath>

using namespace std; 

PointDictionary::PointDictionary(int m){
    max_points = m;
    capacity = m;
    size = 0;
    point_dictionary_array = new Point*[capacity];
}

PointDictionary::~PointDictionary(){
    delete[] point_dictionary_array;
}

void PointDictionary::addPoint(Point *point){
    point_dictionary_array[size] = point;

    size ++;

    if (size >= capacity){
        capacity += max_points;
        Point **temp = new Point*[capacity];

        for (int i = 0; i < size; i++){
            temp[i] = point_dictionary_array[i];
        }

        delete[] point_dictionary_array;
        point_dictionary_array = temp;
    }
}

bool PointDictionary::duplicate(double x, double y){

    for (int i = 0; i < size; i++){
        if (x == point_dictionary_array[i]->get_x_coor() && y == point_dictionary_array[i]->get_y_coor()){
            return true;
        }
    }

    return false;
}

void PointDictionary::nearest(double x, double y){
    double nearest_distance = -1;
    double nearest_x = 0; 
    double nearest_y = 0;

    if (size == 0){
        cout << "no point exists" << endl;
        return;
    }

    for (int i = 0; i < size; i++){
        double point_x = point_dictionary_array[i]->get_x_coor();
        double point_y = point_dictionary_array[i]->get_y_coor();
        double distance = sqrt( ((point_x-x)*(point_x-x)) + ((point_y-y)*(point_y-y)) );

        if (nearest_distance == -1){
            nearest_distance = distance; 
            nearest_x = point_x;
            nearest_y = point_y;
        }else if (distance < nearest_distance){
            nearest_distance = distance;
            nearest_x = point_x; 
            nearest_y = point_y;
        }else if (distance == nearest_distance){
            if (point_x > x){
                nearest_distance = distance; 
                nearest_x = point_x; 
                nearest_y = point_y; 
            }else if ((point_x == x) && point_y > y){
                nearest_distance = distance; 
                nearest_x = point_x; 
                nearest_y = point_y;                
            }
        }
    }

    cout << nearest_x << " " << nearest_y << endl;
}

void PointDictionary::num() { 
    cout << size+1 << endl;
 }
