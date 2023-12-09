#include "Node.hpp"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//Constructor
Node::Node(int m, double x0, double y0, double x1, double y1, PointDictionary *new_pointdictionary){
    //create an array to store the points in the quadtree 
    points_array = new Point*[m];
    array_index = 0;
    capacity = m;
    
    x0_coor = x0;
    y0_coor = y0;
    x1_coor = x1;
    y1_coor = y1; 

    //creates a new point dictionary to store all the points
    pointdictionary = new_pointdictionary;
    head_point = nullptr;

    top_left = nullptr; 
    top_right = nullptr;
    bottom_left = nullptr; 
    bottom_right = nullptr; 
}

Node::Node(int m, double x0, double y0, double x1, double y1, PointDictionary *new_pointdictionary, Point *head){
    //create an array to store the points in the quadtree 
    points_array = new Point*[m];
    array_index = 0;
    capacity = m;
    
    x0_coor = x0;
    y0_coor = y0;
    x1_coor = x1;
    y1_coor = y1; 

    //creates a new point dictionary to store all the points
    pointdictionary = new_pointdictionary;
    
    head_point = head;

    top_left = nullptr; 
    top_right = nullptr;
    bottom_left = nullptr; 
    bottom_right = nullptr; 
}

//Destructor
Node::~Node(){
    
    if (points_array == nullptr){
        //cout << "not leaf node" << endl;
        //cout << "top left" << endl;
        delete top_left;
        //cout << "top right" << endl;
        delete top_right;
        //cout << "bottom left" << endl;
        delete bottom_left;
        //cout << "bottom right" << endl;
        delete bottom_right;   
    }else{
        for (int i = 0; i < array_index; i++){
            delete points_array[i];
        }
    }
    
    delete[] points_array;

    pointdictionary = nullptr;
    head_point = nullptr;
}

bool Node::checkInsert(double x, double y){
    //if the point is not within the range of the quadtree
    if ((x < x0_coor) || (x > x1_coor) || (y < y0_coor) || (y > y1_coor)){
        return false;
    }

    //if the point already exists in the quadtree
    if (pointdictionary->duplicate(x,y)){
        return false;
    }

    insert(x, y,false);
    return true;
}

void Node::insert(double x, double y, bool split_node){
    //not leaf node
    if (points_array == nullptr){
        int point_pos = pointPos(x,y);

        if (point_pos == 1){
            top_left->insert(x,y,false);
        }else if (point_pos == 2){
            top_right->insert(x,y,false);
        }else if (point_pos == 3){
            bottom_left->insert(x,y,false);
        }else if (point_pos == 4){
            bottom_right->insert(x,y,false);
        }
    }

    //is a leaf node
    else{
        //there is still room in the points array
        if (array_index < capacity){
            Point *new_point = new Point(x,y);
            points_array[array_index] = new_point; 
            array_index ++;
            if (split_node){
                //bea is so sweet and cute:
                pointdictionary->addPoint(new_point); 
            }  
            //cout << "inserted" <<endl;         
        }
        //there is no more room in the points array
        else{
            //cout << "need to split" << endl;
            split();
            //points_array = nullptr;
            //Point *new_point = new Point(x,y);
            int point_pos = pointPos(x,y);

            if (point_pos == 1){
                top_left->insert(x,y,false);
            }else if (point_pos == 2){
                top_right->insert(x,y,false);
            }else if (point_pos == 3){
                bottom_left->insert(x,y,false);
            }else if (point_pos == 4){
                bottom_right->insert(x,y,false);
            }
        }
    }
}

void Node::split(){
    //spliting the current node into 4 more nodes 
    top_left = new Node(capacity, x0_coor, (y0_coor+y1_coor)/2, (x0_coor+x1_coor)/2, y1_coor,pointdictionary, head_point);
    top_right = new Node(capacity, (x0_coor+x1_coor)/2, (y0_coor+y1_coor)/2, x1_coor, y1_coor, pointdictionary, head_point);
    bottom_left = new Node(capacity, x0_coor, y0_coor, x1_coor/2, (y0_coor+y1_coor)/2, pointdictionary, head_point);
    bottom_right = new Node(capacity, (x0_coor+x1_coor)/2, y0_coor, x1_coor, (y0_coor+y1_coor)/2, pointdictionary, head_point);

    for (int i = 0; i < array_index; i++){
        double x = points_array[i]->get_x_coor();
        //cout << x << endl;
        double y = points_array[i]->get_y_coor();
        //cout << y << endl;
        delete points_array[i];

        int point_pos = pointPos(x,y);

        if (point_pos == 1){
            top_left->insert(x,y,true);
            //cout << "top left" << endl;
        }else if (point_pos == 2){
            top_right->insert(x,y,true);
            //cout << "top right" << endl;
        }else if (point_pos == 3){
            bottom_left->insert(x,y,true);
            //cout << "bottom left" << endl;
        }else if (point_pos == 4){
            bottom_right->insert(x,y,true);
            //cout << "bottom right" << endl;
        }
    //cout << "done" << endl;
    }
    delete[] points_array;
    points_array = nullptr;
}

int Node::pointPos(double x, double y){
    if ((x>x0_coor) && (x<=(x0_coor+x1_coor)/2)){
        //if point is in the top left quadrant
        if ((y>=(y0_coor+y1_coor)/2) && (y<y1_coor)){return 1;}
        //the point is in the bottom left quadrant 
        else{return 3;}
    }
        
    else if ((x>(x0_coor+x1_coor)/2) && (x<x1_coor)) {
        //if point is in the top right quadrant
        if ((y>=(y0_coor+y1_coor)/2) && (y<y1_coor)){return 2;}
        //the point is in the bottom right quadrant
        else{return 4;}
    }

    //if the point is exactly in the middle 
    if ((x == (x0_coor+x1_coor)/2) && (y == (y0_coor+y1_coor)/2)){return 1;}

    return 0;
}

Point* Node::range(double xr0, double yr0, double xr1, double yr1, Point *head){
    head_point = head;

    //we are at a leaf node 
    if (points_array != NULL){
        for (int i = 0; i < array_index; i++){
            double point_x = points_array[i]->get_x_coor();
            double point_y = points_array[i]->get_y_coor();

            if ( (point_x > xr0) && (point_x < xr1) && (point_y > yr0) && (point_y < yr1) ){
                Point *current_point;
                Point *new_point = new Point(point_x,point_y);

                if (head_point == nullptr){
                    head_point = new_point;
                }else{
                    current_point = head_point; 

                    while (current_point->get_next() != nullptr){
                        current_point = current_point->get_next();
                    }

                    current_point->set_next(new_point); 
                }
            }
        }

        return head_point;
    }

    //left quad
    if (xr0 < (x0_coor+x1_coor)/2){
        //only bottom left quad
        if ( yr0 < (y0_coor+y1_coor)/2 && yr1 < (y0_coor+y1_coor)/2) {
            //cout << "only bottom left" << endl;
            head_point = bottom_left->range(xr0, yr0, xr1, yr1, head_point);
        }
        //only top left quad
        else if (yr0 > (y0_coor+y1_coor)/2 && yr1 > (y0_coor+y1_coor)/2){
            //cout << "only top left" << endl;
            head_point = top_left->range(xr0, yr0, xr1, yr1, head_point);
        }
        //both top and bottom quad 
        else if (yr0 < (y0_coor+y1_coor)/2 && yr1 > (y0_coor+y1_coor)/2){
            //cout << "both top and bottom left" << endl;
            head_point = top_left->range(xr0, yr0, xr1, yr1, head_point);
            //cout << head_point->get_x_coor() << " " << head_point->get_y_coor() << endl;
            head_point = bottom_left->range(xr0, yr0, xr1, yr1, head_point);
            //cout << head_point->get_x_coor() << " " << head_point->get_y_coor() << endl;
        }

        //range goes to the right side as well
        if (xr1 > (x0_coor+x1_coor)/2){
            if ( yr0 < (y0_coor+y1_coor)/2 && yr1 < (y0_coor+y1_coor)/2) {
            //cout << "only bottom right" << endl;
            head_point = bottom_right->range(xr0, yr0, xr1, yr1, head_point);
            }
            //only top left quad
            else if (yr0 > (y0_coor+y1_coor)/2 && yr1 > (y0_coor+y1_coor)/2){
                //cout << "only top right" << endl;
                head_point = top_right->range(xr0, yr0, xr1, yr1, head_point);
            }
            //both top and bottom quad 
            else if (yr0 < (y0_coor+y1_coor)/2 && yr1 > (y0_coor+y1_coor)/2){
                //cout << "both top and bottom right" << endl;
                head_point = top_right->range(xr0, yr0, xr1, yr1, head_point);
                head_point = bottom_right->range(xr0, yr0, xr1, yr1, head_point);
            }        
        }
    }
    //range is only on the right side 
    else if (xr0 > (x0_coor+x1_coor)/2){
        if ( yr0 < (y0_coor+y1_coor)/2 && yr1 < (y0_coor+y1_coor)/2) {
            //cout << "only bottom right" << endl;
            head_point = bottom_right->range(xr0, yr0, xr1, yr1, head_point);
        }
        //only top left quad
        else if (yr0 > (y0_coor+y1_coor)/2 && yr1 > (y0_coor+y1_coor)/2){
            //cout << "only top right" << endl;
            head_point = top_right->range(xr0, yr0, xr1, yr1, head_point);
        }
        //both top and bottom quad 
        else if (yr0 < (y0_coor+y1_coor)/2 && yr1 > (y0_coor+y1_coor)/2){
            //cout << "both top and bottom right" << endl;
            head_point = top_right->range(xr0, yr0, xr1, yr1, head_point);
            head_point = bottom_right->range(xr0, yr0, xr1, yr1, head_point);
        }      
    }
    return head_point;
}

void Node::displayRange(double xr0, double yr0, double xr1, double yr1, Point *head){

    head_point = range(xr0, yr0, xr1, yr1, head);

    if (head_point == nullptr){
        cout << "no points within range" << endl;
    }else{
        Point *current_point = head_point;

         while (current_point != nullptr){
            double x = current_point->get_x_coor();
            double y = current_point->get_y_coor();

            std::cout << x << " " << y << " ";

            current_point = current_point->get_next();
            //if (current_point == nullptr){cout<<"null"<<endl;}
        }
        cout << endl;
    }

    Point *temp = head_point; 
            //cout << current_point->get_x_coor() << " " << current_point->get_y_coor() << endl;
    while (head_point != nullptr){
        head_point = head_point->get_next();
        delete temp; 
        temp = nullptr; 
        temp = head_point;
    }
}

void Node::search(double x, double y, double d){
    head_point = range(x-d, y-d, x+d, y+d, head_point);
    //cout << "range found" << endl;

    if (head_point == nullptr){
        cout << "no point exists" << endl;
    }else{
        Point *current_point = head_point; 
        while (current_point != nullptr){
            int point_x = current_point->get_x_coor();
            int point_y = current_point->get_y_coor();

            int distance = sqrt( ((point_x - x)*(point_x - x)) + ((point_y - y)*(point_y - y)) );

            if (distance < d){
                cout << "point exists" << endl;
                return;
            }

            current_point = current_point->get_next();
        }
        cout << "no point exists" << endl;

        current_point = head_point; 
        while (head_point != nullptr){
            head_point = head_point->get_next();
            delete current_point; 
            current_point = nullptr; 
            current_point = head_point;
        }
    }
}
