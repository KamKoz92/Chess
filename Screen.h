#ifndef SCREEN_H_
#define SCREEN_H_
#include <SDL2/SDL.h>
#include <memory>

class Screen {
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    Uint32 *m_buffer1;
    Uint32 *m_buffer2;

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
};

#endif /* SCREEN_H */