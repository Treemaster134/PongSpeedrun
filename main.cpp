//standard c/c++ headers
#include <list>
#include <iostream>
#include <math.h>
#include <string>
#include <stdio.h>

//raylib headers
#include "raylib.h"

const int screenWidth = 1080;
const int screenHeight = 720;

struct Player{
    int y = 360;
    int score = 0;
};

struct {
    Vector2 pos = {540, 360};
    Vector2 vel = {0.5f, 1.0f};
} Ball;

Player p1;
Player p2;


float degreesToRads(int deg)
{
    return deg * PI/180;
}

int radsToDegrees(float rad)
{
    return rad * 180/PI;
}

void drawGame()
{
    BeginDrawing();
    ClearBackground(BLACK);


    DrawText(TextFormat("%i", p1.score), 480 - MeasureText(TextFormat("%i", p1.score), 48)/2, 80, 48, WHITE);
    DrawText(TextFormat("%i", p2.score), 600 - MeasureText(TextFormat("%i", p2.score), 48)/2, 80, 48, WHITE);

    DrawRectangle(530, 0, 20, 720, WHITE);

    DrawRectangle(30, p1.y - 90, 30, 180, RED);
    DrawRectangle(1020, p2.y - 90, 30, 180, BLUE);

    DrawCircle(Ball.pos.x, Ball.pos.y, 15.0f, WHITE);
    

    EndDrawing();

    return;
}

void gameLogic()
{
    if(IsKeyDown(KEY_UP) && p2.y > 12){p2.y -= 12;}
    if(IsKeyDown(KEY_DOWN) && p2.y < 708){p2.y += 12;}

    if(IsKeyDown(KEY_W) && p1.y > 12){p1.y -= 12;}
    if(IsKeyDown(KEY_S) && p1.y < 708){p1.y += 12;}

    if((Ball.pos.y + 7.5f) - 12 * Ball.vel.y < 0)
    {
        Ball.vel.y *= -1;
    }

    if((Ball.pos.y + 7.5f) - 12 * Ball.vel.y > 720)
    {
        Ball.vel.y *= -1;
    }

    if(Ball.pos.y < p1.y + 90 && Ball.pos.y > p1.y - 90)
    {
        if(Ball.pos.x - 7.5f > 30 && Ball.pos.x - 7.5f < 60)
        {
            Ball.vel.x *= -1;
        }
    }

    if(Ball.pos.y < p2.y + 90 && Ball.pos.y > p2.y - 90)
    {
        
        if(Ball.pos.x + 7.5f > 1005 && Ball.pos.x + 7.5f < 1035)
        {
            Ball.vel.x *= -1;
        }
    }

    if(Ball.pos.x < 0){p2.score += 1; Ball.pos = {540, 360}; Ball.vel = {GetRandomValue(1, 2) * 0.5f, GetRandomValue(-2, -1) * 0.5f};}
    if(Ball.pos.x > 1080){p1.score += 1; Ball.pos = {540, 360}; Ball.vel = {GetRandomValue(1, 2) * 0.5f, GetRandomValue(-2, -1) * 0.5f};}

    Ball.pos.x += 12 * Ball.vel.x;
    Ball.pos.y += 12 *- Ball.vel.y;

    return;
}

int main()
{
    
    //öppna ett nytt fönster

    InitWindow(screenWidth, screenHeight, "Pong");
    InitAudioDevice();
    SetTargetFPS(60);



    //huvudloop
    while (!WindowShouldClose())
    {
        gameLogic();
        drawGame();
        
    }

    CloseWindow();
    
}

