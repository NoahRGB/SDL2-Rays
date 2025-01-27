#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "Vec2.h"
#include "utils.h"
#include "drawing.h"

#define WIDTH 1500 
#define HEIGHT 1000 
#define OBJECT_COUNT 1

typedef struct Ray {
    Vec2 origin;
    Vec2 dir;
} Ray;

typedef struct RayHit {
    float t;
} RayHit;

int windowShouldClose() {
    SDL_Event event;
    int poll = SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
       return 1; 
    }
    return 0;
}

int rayCircleIntersection(Ray ray, Circle circle, float* t1_, float* t2_) {

    Vec2 d = normaliseVec2(ray.dir);
    Vec2 w = subtractVec2(ray.origin, circle.center);
    float a = 1;
    float b = 2 * dot(w, d); 
    float c = dot(w, w) - pow(circle.radius, 2);

    float discriminant = sqrt(pow(dot(w, d), 2) - (dot(w, w) - pow(circle.radius, 2)));
    float t1 = -dot(w, d) + discriminant;
    float t2 = -dot(w, d) - discriminant;

    if (discriminant > 0) {
        *t1_ = t1;
        *t2_ = t2;
        return 1;
    } else if (discriminant < 0) {
        *t1_ = -1;
        *t2_ = -1;
        return 0;
    } else {
        *t1_ = t1;
        *t2_ = t2;
        return 1;
    }
}

RayHit rayCast(Ray ray, Circle* objects) {
    for (int i = 0; i < OBJECT_COUNT; i++) {
        float t1, t2;
        if (rayCircleIntersection(ray, objects[i], &t1, &t2)) {
            if (t1 < t2) {
                return (RayHit){ t1 };
            } else {
                return (RayHit){ t2 };
            }
        }
    }
    return (RayHit){ -999 };
}

int main(int argc, char* argv[]) {

    SDL_Window* window = SDL_CreateWindow("Rays", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    Circle light = (Circle){ (Vec2){ 200, 100 }, 30 };
    Circle* objects = (Circle*)malloc(sizeof(Circle) * OBJECT_COUNT);
    objects[0] = (Circle){ 300, 300, 30 };

    //float t1, t2;
    //rayCircleIntersection((Ray){ (Vec2){ 50, 50 }, (Vec2){ 1, 0 }}, (Circle){ (Vec2){ 300, 50 }, 50 }, &t1, &t2);
    //printf("intersection at: %f and %f\n", t1, t2); 

    int running = 1;
    while (running) {
        running = !windowShouldClose();
      
        outlineCircle(objects[0], surface);
        outlineCircle(light, surface);

        int bottomY = light.center.y - light.radius;
        int topY = light.center.y + light.radius;
        int leftX = light.center.x - light.radius;
        int rightX = light.center.x + light.radius;
        for (int i = bottomY; i <= topY; i++) {
            for (int j = leftX; j <= rightX; j++) {
                Vec2 currentPixel = { j, i };
                float dist = getDist(currentPixel, light.center);
                if (dist >= light.radius - 1 && dist <= light.radius + 1) {
                    Vec2 rayDir = normaliseVec2(subtractVec2(currentPixel, light.center));
                    RayHit hit = rayCast((Ray){ currentPixel, rayDir }, objects);
                    if (hit.t != -999) {
                        drawLine(light.center, addVec2(currentPixel, multiplyVec2Float(rayDir, hit.t)), surface);
                    }
                }
            }
        }

             
        SDL_UpdateWindowSurface(window);
    }
   
    free(objects);
    printf("Closing...");
    return 0;
}

