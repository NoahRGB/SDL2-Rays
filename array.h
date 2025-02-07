#include <stdlib.h>
#include <stdio.h>

#include "Vec2.h"

typedef struct {
    Vec2* data;
    int used, capacity;
} Array;

void initialiseArray(Array arr, int size) {
    arr.capacity = size;
    arr.data = (Vec2*)malloc(size * sizeof(Vec2));
}

void setElement(Array arr, int index, Vec2 element) {
    if (index < arr.capacity) {
        arr.data[index] = element;
    }
}

Vec2 getElement(Array arr, int index) {
    if (index < arr.capacity) {
        return arr.data[index];
    }
    return (Vec2){ -1, -1 };
}

void appendArr(Array arr, Vec2 element) {
    if (arr.used == arr.capacity) {
        arr.capacity = 2 * arr.capacity;
        Vec2* newData = (Vec2*)malloc(arr.capacity * sizeof(Vec2));
        memcpy(newData, arr.data, arr.used * sizeof(Vec2));

    }

}
