#ifndef UTILS_H_
#define UTILS_H_

void swapFloats(float* float1, float* float2) {
    float temp = *float1;
    *float1 = *float2;
    *float2= temp;
}

void swapInts(int* int1, int* int2) {
    int temp = *int1;
    *int1 = *int2;
    *int2 = temp;
}

#endif
