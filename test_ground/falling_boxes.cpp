//http://www.youtube.com/user/thecplusplusguy
//The Box2D main program with SDL
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "../lib/box2d/include/box2d/box2d.h"

const int WIDTH=1540;
const int HEIGHT=780;
b2World* world;
SDL_Surface* screen;
SDL_Renderer* ren2;
const float M2P=20;
const float P2M=1/M2P;

void putPixel(SDL_Surface* dest,int x,int y,int r,int g,int b)
{
//  std::cout << x << " " << y << std::endl;
//    if(x>=0 && x<dest->w && y>=0 && y<dest->h)
//        ((Uint32*)dest->pixels)[y*dest->pitch/4+x]=SDL_MapRGB(dest->format,r,g,b);
}

void swapValue(int& a,int& b)
{
    int tmp=a;
    a=b;
    b=tmp;
}

void drawLine(SDL_Surface* dest,int x0,int y0,int x1,int y1)
{

    SDL_RenderDrawLine(ren2, x0, y0, x1, y1);

//    int tmp;
//    bool step;

//    step=abs(y1-y0)>abs(x1-x0);
//    if(step)
//    {
//        swapValue(x0,y0);
//        swapValue(x1,y1);
//    }

//    if(x0>x1)
//    {
//        swapValue(x1,x0);
//        swapValue(y1,y0);
//    }
//    float error=0.0;
//    float y=y0;
//    float roundError=(float)abs(y1-y0)/(x1-x0);
//    int ystep=(y1>y0 ? 1 : -1);
//    for(int i=x0;i<x1;i++)
//    {
////        if(step)
////            putPixel(dest,y,i,255,255,255);
////        else
////            putPixel(dest,i,y,255,255,255);
//        error+=roundError;
//        if(error>=0.5)
//        {
//            y+=ystep;
//            error-=1;
//        }
//    }
}

void rotateTranslate(b2Vec2& vector,const b2Vec2& center,float angle)
{
    b2Vec2 tmp;
    tmp.x=vector.x*cos(angle)-vector.y*sin(angle);
    tmp.y=vector.x*sin(angle)+vector.y*cos(angle);
    vector=tmp+center;
}


b2Body* addRect(int x,int y,int w,int h,bool dyn=true)
{
    b2BodyDef bodydef;
    bodydef.position.Set(x*P2M,y*P2M);
    if(dyn)
        bodydef.type=b2_dynamicBody;
    b2Body* body=world->CreateBody(&bodydef);

    b2PolygonShape shape;
    shape.SetAsBox(P2M*w/2,P2M*h/2);

    b2FixtureDef fixturedef;
    fixturedef.shape=&shape;
    fixturedef.density=1.0;
    body->CreateFixture(&fixturedef);

}

void drawSquare(b2Vec2* points,b2Vec2 center,float angle)
{
    for(int i=0;i<4;i++)
        drawLine(screen,points[i].x*M2P,points[i].y*M2P,points[(i+1)>3 ? 0 : (i+1)].x*M2P,points[(i+1)>3 ? 0 : (i+1)].y*M2P);
}


void init()
{
    world=new b2World(b2Vec2(0.0,9.81));
    addRect(WIDTH/2,HEIGHT-50,WIDTH,30,false);
}

void display()
{
//    SDL_FillRect(screen,NULL,0);
    b2Body* tmp=world->GetBodyList();
    b2Vec2 points[4];
    while(tmp)
    {
        for(int i=0;i<4;i++)
        {
            points[i]=((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->m_vertices[i];
            rotateTranslate(points[i],tmp->GetWorldCenter(),tmp->GetAngle());
        }
        drawSquare(points,tmp->GetWorldCenter(),tmp->GetAngle());
        tmp=tmp->GetNext();
    }
}

int main(int argc,char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
//    screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);
    SDL_Window *window;
    SDL_Surface *image;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "3");

    // create the window like normal
    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, flags);

    ren2 = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Uint32 start;
    SDL_Event event;
    bool running=true;
    init();
    while(running)
    {
        start=SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running=false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            running=false;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    addRect(event.button.x,event.button.y,20,20,true);
                    break;

            }
        }

        SDL_Rect rect;
        rect.x = 50;
        rect.y = 50;
        rect.w = 10;
        rect.h = 10;

        // clr scr
        SDL_SetRenderDrawColor(ren2, 0, 0, 0, 255);
        SDL_RenderClear(ren2);

        // draw example
        SDL_SetRenderDrawColor(ren2, 255, 255, 255, 255);
        SDL_RenderDrawLine(ren2, 100, 100, 200, 100);
        SDL_RenderFillRect(ren2, &rect);



        display();







        SDL_RenderPresent(ren2);


        world->Step(1.0/30.0,8,3);  //update
//        SDL_Flip(screen);
//        SDL_UpdateWindowSurface(window);
        if(1000.0/30>SDL_GetTicks()-start)
            SDL_Delay(1000.0/30-(SDL_GetTicks()-start));
    }
    SDL_Quit();
}