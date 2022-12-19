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


#define DEBUG

#ifdef DEBUG
namespace DEBUG_TOOLS{

    static clock_t starting_time;

    static void StartProgramExecutionTimer()   
    {
        starting_time = clock();
    }

    static void StopProgramExecutionTimer()
    {
        static clock_t end_time = (clock() - starting_time);

        //std::cout << "\033[0;32m Program execution time: "<< end_time <<" ms.\033[0m\n"; //working
       
       //with bold ms
       std::cout << "\033[0;32m Program execution time: \033[0m" << "\033[1;32m" << (end_time / (double) CLOCKS_PER_SEC)<< "\033[0m" <<"\033[0;92m seconds.\033[0m\n";

        
        
//                  foreground background
// black        30         40
// red          31         41
// green        32         42
// yellow       33         43
// blue         34         44
// magenta      35         45
// cyan         36         46
// white        37         47

// Additionally, you can use these:

// reset             0  (everything back to normal)
// bold/bright       1  (often a brighter shade of the same colour)
// underline         4
// inverse           7  (swap foreground and background colours)
// bold/bright off  21
// underline off    24
// inverse off      27

    
    
        //exerimental colored composition
        std::string magenta_opener{"\033[0;33m"};
        std::string message_1{"msg_1: something"};
        std::string closure{"\033[0m"};

        std::string msg = magenta_opener + message_1 + closure;

        std::cout << msg << std::endl;
        
        
        //std::cout << "\033[0;32mProgram execution time: \033[0m"<< end_time <<"\033[0;32m ms.\033[0m\n";
        //std::cout << "Program execution time: " << end_time  << " ms." << std::endl;
    }  
}
#endif


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
    addRect(WIDTH/2-100,HEIGHT-50,WIDTH,30,false);
}

void display()
{
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

static       SDL_Rect rect;

int main(int argc,char** argv)
{
    SDL_Window *window;
    SDL_Surface *image;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "3");

    // create the window like normal
    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    window = SDL_CreateWindow("Falling boxes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, flags);

    ren2 = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //SDL_RENDERER_SOFTWARE for no HW aceleration and SDL_RENDERER_ACCELERATED to use it

    Uint32 start;
    SDL_Event event;
    bool running=true;
    init();

    int x{100};
    
    rect.x = 50;
    rect.y = 100;
    rect.w = 200;
    rect.h = 100;

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

                            case SDLK_k:
                            x -= 20;

                             for(size_t i{0}; i < 200; ++i){
                     auto side_a = (rand() % 1 + 1); 
                     auto side_b = (rand() % 1 + 1); 
                //////
                    addRect(rand() % 1500 + 10, rand() % 680 + 10, side_a, side_a, true);
                            }

                            break;

                            case SDLK_l:
                            x -= 200;

                            //randomized sizes of boxes
                            for(size_t i{0}; i < 20; ++i){
                     auto side_a = (rand() % 70 + 10); 
                     auto side_b = (rand() % 70 + 10); 
                //////
                    addRect(rand() % 1500 + 10, rand() % 680 + 10, side_a, side_a, true);
                            }


                            break;        

                            case SDLK_w:



                            for(size_t i{0}; i < world->GetBodyCount(); ++i){
                                    world->DestroyBody(world->GetBodyList()); //will destroy last created body
                            }
                            break;

                            case SDLK_a:
                            rect.w += 20;
                            break;

                            case SDLK_s:
                            x -= 200;
                            break;

                            case SDLK_d:
                            rect.h -= 20;
                            break;               
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                //randomized sizes of boxes
                     auto side_a = (rand() % 70 + 10); 
                     auto side_b = (rand() % 70 + 10); 
                //////
                    addRect(event.button.x, event.button.y, side_a, side_a, true);

                    x += 15;

                    break;
            }
        }



        // clr scr
        SDL_SetRenderDrawColor(ren2, 0, 0, 0, 255);
        SDL_RenderClear(ren2);

        // draw example
        SDL_SetRenderDrawColor(ren2, 255, 255, 255, 255);
         SDL_RenderDrawLine(ren2, x, rect.y, rect.w, rect.h);
        // SDL_RenderFillRect(ren2, &rect);

        display();

        SDL_RenderPresent(ren2);

        world->Step(1.0/60.0,8,3);  //update
//        SDL_Flip(screen);
//        SDL_UpdateWindowSurface(window);
        if(1000.0/60>SDL_GetTicks()-start)
            SDL_Delay(1000.0/60-(SDL_GetTicks()-start));
    }

    SDL_Quit();
}
