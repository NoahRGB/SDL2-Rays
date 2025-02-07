#include <stdlib.h>
#include "Vec2.h"

typedef struct Array {
    Vec2* data;
    int used, capacity;
} Array;

void setArraySize(Array arr, int size) {
    arr.data = (Vec2*)malloc(size * sizeof(Vec2));
}

void setArrayElement(Array arr, int index, Vec2 element) {
    arr.data[index] = element;
}

Vec2 getArrayElement(Array arr, int index) {
    return arr.data[index];
}
