#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>



#include <stdio.h>
#include<iostream>
#include<string>
#include<cmath>
#include <ctime>
#include <stdlib.h>

using namespace std;

const int BALL_X=390;
const int BALL_Y=290;

Uint32 white;


SDL_Window* window;
SDL_Surface* screen;
SDL_Event e;
SDL_Rect playerpaddle;
SDL_Rect aipaddle;
SDL_Rect ball;
int xvel,yvel;

bool angleoverlapping(int x, int y, SDL_Rect rec)
{
    if(x>rec.x && y>rec.y && x<rec.x+rec.w && y<rec.y+rec.h)
    {
        return true;
    }
    return false;
}

bool collisioncheck(SDL_Rect obj1, SDL_Rect obj2)
{
    if(angleoverlapping(obj1.x, obj1.y, obj2)==true||angleoverlapping(obj1.x+obj1.w, obj1.y, obj2)==true||angleoverlapping(obj1.x, obj1.y+obj1.h, obj2)==true||angleoverlapping(obj1.x+obj1.w, obj1.y+obj1.h, obj2)==true)
    {
        return true;
    }
    return false;
}
int getrndnum(int high, int low)
{
    return rand()%high+low;
}

void moveball()
{
    ball.x=BALL_X;
    ball.y=BALL_Y;
    xvel=getrndnum(2, -2);
    yvel=getrndnum(2, -2);
}

void loadgame()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    
    window=SDL_CreateWindow("PPong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    screen=SDL_GetWindowSurface(window);
    
    playerpaddle.x=20;
    playerpaddle.w=20;
    playerpaddle.y=250;
    playerpaddle.h=100;
    
    aipaddle.x=760;
    aipaddle.y=250;
    aipaddle.h=100;
    aipaddle.w=20;
    
    ball.x=BALL_X;
    ball.y=BALL_Y;
    ball.w=20;
    ball.h=20;

    white=SDL_MapRGB(screen->format, 255, 255, 255);
    
    srand(time(NULL));
    
    moveball();
}

void gamelogic()
{
    if(e.type==SDL_KEYDOWN && e.key.repeat==0)
    {
        switch (e.key.keysym.sym) {
                
            case SDLK_UP: playerpaddle.y -= 1;
                break;
            case SDLK_DOWN: playerpaddle.y += 1;
                break;
        }
    
    }
    
    //auto movements on key press?
    else if (e.type==SDL_KEYUP && e.key.repeat==0)
    {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                playerpaddle.y-=1;
                break;
                
            case SDLK_DOWN:
                playerpaddle.y+=1;
                break;
        }
    }
    
    if(playerpaddle.y<1)
    {
        playerpaddle.y=1;
    }
    
    if(playerpaddle.y+playerpaddle.h>599)
    {
        playerpaddle.y=599-playerpaddle.h;
    }
    
    ball.x+=xvel;
    ball.y+=yvel;
    
    if(ball.y<1)
    {
        ball.y-=yvel;
    }
    
    if (ball.y+ball.h>599)
    {
        ball.y-=yvel;
    }
    
    if(ball.x<2)
    {
        moveball();
    }
    if(ball.x+ball.w>798)
    {
        moveball();
    }
    
    if(collisioncheck(ball, playerpaddle)==true)
    {
        ball.x-=xvel;
    }
    
    if(collisioncheck(ball, aipaddle)==true)
    {
        ball.x-=xvel;
    }
    
}

void drawscreen()
{
    SDL_FillRect(screen, NULL, 0);
    SDL_FillRect(screen, &playerpaddle, white);
    SDL_FillRect(screen, &aipaddle, white);
    SDL_FillRect(screen, &ball, white);
    
    SDL_UpdateWindowSurface(window);

}

void quit()
{
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    
    loadgame();
    bool gamerunning=true;
    
    while (gamerunning)
    {
        SDL_PollEvent(&e);
        if(e.type==SDL_QUIT)
        {
            gamerunning=false;
        
        }
        gamelogic();
        drawscreen();
    }
    
    
    return 0;
}
