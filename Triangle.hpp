#include <iostream>

template <typename T>
class Triangle{
public:
    std::pair<T, T> vertex[3];

    Triangle(){
        for (int i = 0; i < 3; i++){
            vertex[i].first = 0;
            vertex[i].second = 0;
        }
    }

    Triangle(T h, T l){
        vertex[0].first = -l/2;
        vertex[0].second = 0;
        vertex[1].first = l/2;
        vertex[1].second = 0;
        vertex[2].first = 0;
        vertex[2].second = h;
    }

    T Area(){
        return (vertex[2].second -  vertex[0].second) * (vertex[1].first - vertex[0].first) / 2;
    }

    void Input(){
        T h, l, x, y;
        std::cout << "Enter height and base of the triangle: ";
        std::cin >> h >> l;
        std::cout << "Input top peak: ";
        std::cin >> x >> y;

        vertex[0].first = -l/2 + x;
        vertex[0].second = y - h;
        vertex[1].first = l/2 + x;
        vertex[1].second = y - h;
        vertex[2].first = x;
        vertex[2].second = y;
    }

};

template <class T>
std::ostream& operator << (std::ostream& cout, const Triangle<T>& t){
    cout << "(" << t.vertex[0].first << ", " << t.vertex[0].second << ")";
    cout << "(" << t.vertex[1].first << ", " << t.vertex[1].second << ")";
    cout << "(" << t.vertex[2].first << ", " << t.vertex[2].second << ")";
    return cout;
}

