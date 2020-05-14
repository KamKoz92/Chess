#include "Screen.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL) {

}
Screen::~Screen() {

}
bool Screen::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    m_window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
        SDL_Quit;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (m_renderer == NULL) {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    if (m_texture == NULL) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    SetBoard();
    return true;
}
void Screen::close() {
    delete[] m_buffer1;
    delete[] m_buffer2;
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
void Screen::clear() {
    memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    update();
}
void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
    if (x < 0 || x > SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }
    m_buffer1[(y * SCREEN_WIDTH) + x] = Color(red,green,blue);
}

int Screen::Color(Uint8 r, Uint8 g, Uint8 b) {
    Uint32 color = 0;
    color += r;
    color <<= 8;
    color += g;
    color <<= 8;
    color += b;
    color <<= 8;
    color += 0xFF;
    return color;
}
void Screen::update() {
    SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

void Screen::SetBoard() {
    m_buffer1 = new Uint32[SCREEN_HEIGHT * SCREEN_WIDTH];
    Uint32 col = Color(80,151,53);
    for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
        m_buffer1[i] = col;
    }
    // Maroon borders
    for (int i = 10; i < 821; i += 10) {
        drawSquare(i,10,10,128,0,0);
        drawSquare(i,820,10,128,0,0);
    }
    for (int i = 20; i < 820; i += 10) {
        drawSquare(10,i,10,128,0,0);
        drawSquare(820,i,10,128,0,0);
    }

    //Board squares
    for(int i = 20; i < SCREEN_WIDTH; i += 200) {
        for(int j = 20; j < SCREEN_HEIGHT; j += 200) {
            drawSquare(i,j,100,255,151,53);
        }
    }
    for(int i = 120; i < SCREEN_WIDTH; i += 200) {
        for(int j = 120; j < SCREEN_HEIGHT; j += 200) {
            drawSquare(i,j,100,255,151,53);
        }
    }
    update();
}

void Screen::drawSquare(int x, int y, int size, Uint8 red, Uint8 green, Uint8 blue) {
    if (x < 0 || x+size > SCREEN_WIDTH || y < 0 || y+size >= SCREEN_HEIGHT || size < 0) {
        return;
    }
    else {
        for (int i = x; i < x + size; i++)  {
            for (int j = y; j < y + size; j++) {
                setPixel(i,j,red,green,blue);
            }
        }   
    }
}