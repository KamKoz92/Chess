#include "Screen.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Board.h"

using namespace std;

Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), selectedSquare(-1), prevSquare(-1) {
    updateRectBoard.h = 100;
    updateRectBoard.w = 100;
    updateRectPiece.h = 80;
    updateRectPiece.w = 80;
}


Screen::~Screen() {

}

bool Screen::init() {

    // Screen initialization
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
    tempTexture1 = SDL_CreateTexture(m_renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 100, 100);

    if (tempTexture1 == NULL)   {
        cout << "Cannot create temp Texture!" << endl;
    }
    if (m_texture == NULL) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }
    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "Failed to initialise SDL_image for PNG" << endl;
        return false;
    }
    // Setting the board
    SetBoard();
    return true;
}
void Screen::close() {
    delete[] m_buffer1;
    delete[] tempBuffer;
    SDL_DestroyTexture(bB);
    SDL_DestroyTexture(bQ);
    SDL_DestroyTexture(bK);
    SDL_DestroyTexture(bP);
    SDL_DestroyTexture(bR);
    SDL_DestroyTexture(bN);
    SDL_DestroyTexture(wB);
    SDL_DestroyTexture(wQ);
    SDL_DestroyTexture(wK);
    SDL_DestroyTexture(wP);
    SDL_DestroyTexture(wR);
    SDL_DestroyTexture(wN);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyTexture(tempTexture1);
    SDL_DestroyTexture(tempTexture2);
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

Uint32 Screen::Color(Uint8 r, Uint8 g, Uint8 b) {
    Uint32 color = 0;
    color += r;
    color <<= 8;
    color += g;
    color <<= 8;
    color += b;
    color <<= 8;
    color += 0xFF;
    return color;
    //Orange 255,151,53
    //Green 80,151,53
    //Marron 128,0,0
    //Grey 191,191,191
}
void Screen::update() {
    SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

void Screen::SetBoard() {
    tempBuffer = new Uint32[10000];
    Uint32 c = Color(191,191,191);
    for (int i = 0; i < 10000; i++) {
        tempBuffer[i] = c;
    }
    //Graphical initialization of the board
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
    SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
    SDL_UpdateTexture(tempTexture1, NULL, tempBuffer, 100 * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    loadPNG();
    renderPieces();
    SDL_RenderPresent(m_renderer);
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

void Screen::loadPNG() {
    SDL_Surface *imageSurface1 = IMG_Load("pngs/bB.png");
    bB = SDL_CreateTextureFromSurface(m_renderer, imageSurface1);

    SDL_Surface *imageSurface2 = IMG_Load("pngs/bK.png");
    bK = SDL_CreateTextureFromSurface(m_renderer, imageSurface2);

    SDL_Surface *imageSurface3 = IMG_Load("pngs/bN.png");
    bN = SDL_CreateTextureFromSurface(m_renderer, imageSurface3);

    SDL_Surface *imageSurface4 = IMG_Load("pngs/bP.png");
    bP = SDL_CreateTextureFromSurface(m_renderer, imageSurface4);

    SDL_Surface *imageSurface5 = IMG_Load("pngs/bQ.png");
    bQ = SDL_CreateTextureFromSurface(m_renderer, imageSurface5);

    SDL_Surface *imageSurface6 = IMG_Load("pngs/bR.png");
    bR = SDL_CreateTextureFromSurface(m_renderer, imageSurface6);

    SDL_Surface *imageSurface7 = IMG_Load("pngs/wB.png");
    wB = SDL_CreateTextureFromSurface(m_renderer, imageSurface7);

    SDL_Surface *imageSurface8 = IMG_Load("pngs/wK.png");
    wK = SDL_CreateTextureFromSurface(m_renderer, imageSurface8);

    SDL_Surface *imageSurface9 = IMG_Load("pngs/wN.png");
    wN = SDL_CreateTextureFromSurface(m_renderer, imageSurface9);

    SDL_Surface *imageSurface10 = IMG_Load("pngs/wP.png");
    wP = SDL_CreateTextureFromSurface(m_renderer, imageSurface10);

    SDL_Surface *imageSurface11 = IMG_Load("pngs/wQ.png");
    wQ = SDL_CreateTextureFromSurface(m_renderer, imageSurface11);

    SDL_Surface *imageSurface12 = IMG_Load("pngs/wR.png");
    wR = SDL_CreateTextureFromSurface(m_renderer, imageSurface12);
   
    if(imageSurface1 == NULL || imageSurface2 == NULL || 
    imageSurface3 == NULL || imageSurface4 == NULL || 
    imageSurface5 == NULL || imageSurface6 == NULL || 
    imageSurface7 == NULL || imageSurface8 == NULL || 
    imageSurface9 == NULL || imageSurface10 == NULL || 
    imageSurface11 == NULL || imageSurface12 == NULL) {
        cout << "Problem with loading pngs" << endl;
        return;
    }

    SDL_FreeSurface(imageSurface1);
    SDL_FreeSurface(imageSurface2);
    SDL_FreeSurface(imageSurface3);
    SDL_FreeSurface(imageSurface4);
    SDL_FreeSurface(imageSurface5);
    SDL_FreeSurface(imageSurface6);
    SDL_FreeSurface(imageSurface7);
    SDL_FreeSurface(imageSurface8);
    SDL_FreeSurface(imageSurface9);
    SDL_FreeSurface(imageSurface10);
    SDL_FreeSurface(imageSurface11);
    SDL_FreeSurface(imageSurface12);
}

void Screen::renderPieces() {

    //rendering black pieces
    SDL_Rect m_destination;
    m_destination.h = 80;
    m_destination.w = 80;

    m_destination.x = 30;
    m_destination.y = 30;
    SDL_RenderCopy(m_renderer, bR, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bN, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bB, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bQ, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bK, NULL, &m_destination);
    
    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bB, NULL, &m_destination);
    
    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bN, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bR, NULL, &m_destination);

    m_destination.x = 30;
    m_destination.y = 130;
    SDL_RenderCopy(m_renderer, bP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, bP, NULL, &m_destination);


    //rendering white pieces
    m_destination.x = 30;
    m_destination.y = 730;
    SDL_RenderCopy(m_renderer, wR, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wN, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wB, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wQ, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wK, NULL, &m_destination);
    
    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wB, NULL, &m_destination);
    
    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wN, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wR, NULL, &m_destination);

    m_destination.x = 30;
    m_destination.y = 630;
    SDL_RenderCopy(m_renderer, wP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wP, NULL, &m_destination);

    m_destination.x += 100;
    SDL_RenderCopy(m_renderer, wP, NULL, &m_destination);
}
void Screen::updateSelection(int x, int y) {
    int temp = board.returnSpot(x-20,y-20);
    if(temp != -1) {
        if(selectedSquare != temp) {
            prevSquare = selectedSquare;
            selectedSquare = temp;

            updateRectBoard.x = board.panel[selectedSquare].x;
            updateRectBoard.y = board.panel[selectedSquare].y;
            SDL_RenderCopy(m_renderer, tempTexture1, NULL, &updateRectBoard);
            tempTexture2 = getPieceTexture(board.panel[selectedSquare].occpuiedBy);
            if(tempTexture2 != NULL) {
                updateRectPiece.x = updateRectBoard.x + 10;
                updateRectPiece.y = updateRectBoard.y + 10;
                SDL_RenderCopy(m_renderer,tempTexture2,NULL,&updateRectPiece);
            }

            if(prevSquare != -1) {
                updateRectBoard.x = board.panel[prevSquare].x;
                updateRectBoard.y = board.panel[prevSquare].y;
                SDL_RenderCopy(m_renderer, m_texture, &updateRectBoard, &updateRectBoard);
                tempTexture2 = getPieceTexture(board.panel[prevSquare].occpuiedBy);
                if(tempTexture2 != NULL) {
                    updateRectPiece.x = updateRectBoard.x + 10;
                    updateRectPiece.y = updateRectBoard.y + 10;
                    SDL_RenderCopy(m_renderer,tempTexture2,NULL,&updateRectPiece);
                }
            }
            



            SDL_RenderPresent(m_renderer);
        }
    }
    

}
SDL_Texture* Screen::getPieceTexture(int type) {
    switch (type)
    {
    case 1:
        return wK;
        break;
    case 2:
        return wQ;
        break;
    case 3:
        return wB;
        break;
    case 4:
        return wN;
        break;
    case 5:
        return wR;
        break;
    case 6:
        return wP;
        break;
    case -1:
        return bK;
        break;  
    case -2:
        return bQ;
        break;
    case -3:
        return bB;
        break;
    case -4:
        return bN;
        break;
    case -5:
        return bR;
        break;
    case -6:
        return bP;
        break;  
    default:
        return NULL;
        break;
    }
}