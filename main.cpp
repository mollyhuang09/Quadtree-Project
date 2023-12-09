#include "Node.hpp"
#include "PointDictionary.hpp"
#include "Point.hpp"

#include <iostream>
#include <string>
#include <exception>

using namespace std;

class IllegalException : public exception{
    virtual const char* what() const throw(){
        return "illegal argument";
    }
}illegal_exception;

int main(){
    Node *new_quadtree;
    PointDictionary *new_pointdictionary;
    string command; 

    while (cin >> command){
        if (command == "INIT"){
            int m;
            double x0;
            double y0;
            double x1;
            double y1; 
            cin >> m;
            cin >> x0;
            cin >> y0;
            cin >> x1;
            cin >> y1;

            new_pointdictionary = new PointDictionary(m);
            new_quadtree = new Node(m, x0, y0, x1, y1, new_pointdictionary);
            
            try {
                if (x0 < x1 && y0 < y1){
                    cout << "success" << endl;  
                }else{
                    throw illegal_exception;
                }              
            }

            catch(exception& ex){
                cout << ex.what() << endl;
            }
/*             if (x0 < x1 && y0 < y1){
                new_pointdictionary = new PointDictionary(m);
                new_quadtree = new Node(m, x0, y0, x1, y1, new_pointdictionary);
                cout << "success" << endl;
            }else{
                cout << "illegal argument" << endl;
            } */
        }

        else if (command == "INSERT"){
            double x;
            double y;
            cin >> x;
            cin >> y; 

            if (new_quadtree->checkInsert(x,y)){
                cout << "success" << endl; 
            }else{
                cout << "failure" << endl;
            }
        }

        else if (command == "SEARCH"){
            double x; 
            double y;
            double d; 
            cin >> x;
            cin >> y;
            cin >> d;

            new_quadtree->search(x,y,d);
        }

        else if (command == "NEAREST"){
            double x;
            double y;
            cin >> x;
            cin >> y;

            new_pointdictionary->nearest(x,y);
        }

        else if (command == "RANGE"){
            double xr0;
            double yr0;
            double xr1;
            double yr1; 
            cin >> xr0;
            cin >> yr0;
            cin >> xr1;
            cin >> yr1;

            try {
                if (xr0 < xr1 && yr0 < yr1){
                    Point* head = nullptr;
                    new_quadtree->displayRange(xr0, yr0, xr1, yr1, head); 
                }else{
                    throw illegal_exception;
                }              
            }

            catch(exception& ex){
                cout << ex.what() << endl;
            }
        }

        else if (command == "NUM"){
            new_pointdictionary->num();
        }

        else if (command == "EXIT"){
            delete new_quadtree;
            delete new_pointdictionary;
        }
    }

    return 0;

}

