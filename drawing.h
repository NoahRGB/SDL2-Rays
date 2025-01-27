#ifndef DRAWING_H_
#define DRAWING_H_

#include <SDL2/SDL.h>

#include "Vec2.h"
#include "utils.h"

typedef struct Circle {
    Vec2 center;
    int radius;
} Circle;

void drawPixel(int x, int y, SDL_Surface* surface) {
    SDL_Rect rect = { x, y, 1, 1 };
    SDL_FillRect(surface, &rect, 0xFFFFFFFF);
}

void fillCircle(Circle circle, SDL_Surface* surface) {
    int bottomY = circle.center.y - circle.radius;
    int topY = circle.center.y + circle.radius;
    int leftX = circle.center.x - circle.radius;
    int rightX = circle.center.x + circle.radius;

    for (int i = bottomY; i <= topY; i++) {
        for (int j = leftX; j <= rightX; j++) {
            Vec2 currentPixel = { j, i };
            if (getDist(currentPixel, circle.center) <= circle.radius) {
                drawPixel(j, i, surface);    
            }
        }
    }
}

void outlineCircle(Circle circle, SDL_Surface* surface) {
    int bottomY = circle.center.y - circle.radius;
    int topY = circle.center.y + circle.radius;
    int leftX = circle.center.x - circle.radius;
    int rightX = circle.center.x + circle.radius;

    for (int i = bottomY; i <= topY; i++) {
        for (int j = leftX; j <= rightX; j++) {
            Vec2 currentPixel = { j, i };
            float dist = getDist(currentPixel, circle.center);
            if (dist >= circle.radius - 1 && dist <= circle.radius + 1) {
                drawPixel(j, i, surface);
            }
        }
    }
}

void drawLine(Vec2 start, Vec2 end, SDL_Surface* surface) {
    int steep = 0;

    if (abs(start.x - end.x) < abs(start.y - end.y)) {
        swapFloats(&start.x, &start.y);
        swapFloats(&end.x, &end.y);
        steep = 1;
    }

    // if endpoints were given wrong way around, swap them
    if (start.x > end.x) {
        swapFloats(&start.x, &end.x);
        swapFloats(&start.y, &end.y);
    }

    for (int x = start.x; x <= end.x; x++) {
        float progress = (x - start.x) / (float)(end.x - start.x);
        int y = start.y * (1 - progress) + end.y * progress;
        if (steep) {
            drawPixel(y, x, surface);
        } else {
            drawPixel(x, y, surface);
        }
    }
}

#endif
