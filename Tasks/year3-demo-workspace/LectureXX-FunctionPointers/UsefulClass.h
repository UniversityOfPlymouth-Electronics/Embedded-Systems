#pragma once
#include <iostream>
#include <functional>
using namespace std;


template <class T, int N>
class UsefulClass {
public:
    typedef T(*transform_t)(T);

private:
    transform_t _tx;
    T data[N] = {(T)0};
    int index;

public:
    UsefulClass(transform_t tx) : _tx(tx) {
        index = 0;
    }
    const T& operator[](int idx) {
        return data[idx%N];
    }
    void operator<<(T nextVal) {
        data[index] = _tx(nextVal);
        index = (index + 1) % N;
    }

};