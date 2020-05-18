#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL2/SDL.h>
#include <memory>
#include <SDL2/SDL_image.h>
#include "Board.h"

class Screen {
public:
    
private:
    Board board;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer1;
    Uint32 *m_buffer2;
    SDL_Texture *bB;
    SDL_Texture *bK;
    SDL_Texture *bN;
    SDL_Texture *bP;
    SDL_Texture *bQ;
    SDL_Texture *bR;
    SDL_Texture *wB;
    SDL_Texture *wK;
    SDL_Texture *wN;
    SDL_Texture *wP;
    SDL_Texture *wQ;
    SDL_Texture *wR;
    int selectedSquare;

public:
    const static int SCREEN_HEIGHT = 840;
    const static int SCREEN_WIDTH = 840;
    Screen();
    ~Screen();
    bool init();
    void close();
    void update();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void clear();
    void SetBoard();
    void drawSquare(int x, int y, int size, Uint8 red, Uint8 green, Uint8 blue);
    int Color(Uint8 r, Uint8 g, Uint8 b);
    void loadPNG();
    void renderPieces();
    void updateSelection(int x, int y);
    SDL_Texture* getPieceTexture(int type);
};

#endif /* SCREEN_H */