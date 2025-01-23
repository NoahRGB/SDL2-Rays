#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

typedef struct Vec2I {
    int x, y;
} Vec2I;

typedef struct Circle {
    Vec2I center;
    int radius;
} Circle;

int windowShouldClose() {
    SDL_Event event;
    int poll = SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
       return 1; 
    }
    return 0;
}

int getDist(Vec2I v1, Vec2I v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

void fillCircle(Circle circle, SDL_Surface* surface) {
    int bottomY = circle.center.y - circle.radius;
    int topY = circle.center.y + circle.radius;
    int leftX = circle.center.x - circle.radius;
    int rightX = circle.center.x + circle.radius;

    for (int i = bottomY; i <= topY; i++) {
        for (int j = leftX; j <= rightX; j++) {
            Vec2I currentPixel = { i, j };
            if (getDist(currentPixel, circle.center) <= circle.radius) {
                SDL_Rect rect = { i, j, 1, 1 };
                SDL_FillRect(surface, &rect, 0xFFFFFFFF);
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
            Vec2I currentPixel = { i, j };
            if (getDist(currentPixel, circle.center) == circle.radius) {
                SDL_Rect rect = { i, j, 1, 1 };
                SDL_FillRect(surface, &rect, 0xFFFFFFFF);
            }
        }
    }
}

int main(int argc, char* argv[]) {

    SDL_Window* window = SDL_CreateWindow("Rays", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    Circle circle1 = { 100, 100, 30};
    Circle circle2 = { 300, 300, 20};

    int running = 1;
    while (running) {
        running = !windowShouldClose();
      
        
        fillCircle(circle1, surface);
        outlineCircle(circle2, surface);
        SDL_UpdateWindowSurface(window);
    }
    
    printf("Closing...");
    return 0;
}




