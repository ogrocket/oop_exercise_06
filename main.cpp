#include "queue.hpp"
#include <iostream>
#include <algorithm>
#include "Triangle.hpp"

void menu();

int main(){
    Queue<Triangle<int>, allocator<Triangle<int>, 20>> q;
    int variant, index;
    Triangle<int> t;
    menu();

    do{
    	std::cin >> variant;
    	switch(variant){
    		case 1:{
    			t.Input();
    			q.Push(t);
    			std::cout << "Triangle successfully added\n";
    			break;
    		}

    		case 2:{
                q.Pop();
                std::cout << "Triangle successfully deleted\n";
                break;
    		}

    		case 3:{
                std::cout << q.Top() << "\n";
                break;
    		}

    		case 4:{
    		    std::for_each(q.Begin(), q.End(), [](Triangle<int> tri) {std::cout << tri <<" Area " << tri.Area() << std::endl;});
    		    break;
    		}
    	}
    }while (variant != 0);
    return 0;
}

void menu() {
    std::cout << "0. Exit\n";
    std::cout << "1. Push triangle in queue\n";
    std::cout << "2. Pop triangle\n";
    std::cout << "3. Top triangle in queue\n";
    std::cout << "4. Print triangles from the collection\n";
}
