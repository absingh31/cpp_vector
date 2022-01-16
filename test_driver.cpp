#include "abvector.hpp"
#include <iostream>

template<typename T>
void print(const abvector<T> &arr) {
    for (size_t idx = 0; idx < arr.size(); idx++) {
        std::cout << arr[idx] << std::endl;
    }
}

struct abc
{
public:
    int data {10};
    char cdata {'d'};

    abvector<abc*> childs;
};


int main() {
    struct abc anObj, mn;


    mn.data = 34;
    mn.cdata = 'r';
    struct abc *anObjChild = &mn;


    anObj.data = 13;
    anObj.cdata = 'p';

    anObj.childs.push_back(anObjChild);

    std::cout << anObj.childs[0]->data << std::endl;


   //print(arr);
}