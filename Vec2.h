#ifndef VEC2I_H_
#define VEC2I_H_

#include <stdio.h>
#include <math.h>

typedef struct Vec2 {
    float x, y;
} Vec2;

void printVec2(Vec2 v) {
    printf("(%f, %f)\n", v.x, v.y);
}

Vec2 subtractVec2(Vec2 v1, Vec2 v2) {
    return (Vec2){ v1.x - v2.x, v1.y - v2.y };
}

Vec2 addVec2(Vec2 v1, Vec2 v2) {
    return (Vec2){ v1.x + v2.x, v1.y + v2.y };
}

Vec2 multiplyVec2(Vec2 v1, Vec2 v2) {
    return (Vec2){ v1.x * v2.x, v1.y * v2.y };
}

Vec2 multiplyVec2Float(Vec2 v, float f) {
    return (Vec2){ v.x * f, v.y * f };
}

float getDist(Vec2 v1, Vec2 v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

float length(Vec2 v) {
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

Vec2 normaliseVec2(Vec2 v) {
    float l = length(v);
    return (Vec2) { v.x / l, v.y / l};
}

float dot(Vec2 v1, Vec2 v2) {
    return v1.x * v2.x + v1.y * v2.y; 
}


#endif
