#include <cstdlib>
#include <iostream>
#include "Screen.h"

using namespace std;
int main(int argc, char *argv[]) {
    Screen screen;
    if (screen.init() == false) {
        cout << "SDL initialization failed." << endl;
    }
    bool flag = false;
    SDL_Event event;
    for (int i = 0; i < 10; i++) {
        cout << " Hello world !" << endl;
    }
    while (!flag) {     
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                flag = true;
            }
        }
    }
    screen.close();
    return 0;
}
