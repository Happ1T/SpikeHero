#include "consts.h"
#include "game.h"
#include "menu.h"



int main() {
    bool is_continue = false;
    RenderWindow window(VideoMode(WIDTH_SCREEN, HEIGHT_SCREEN), "Fil gay", Style::Close);
   while(window.isOpen()) {
       menu(window, is_continue);
       game(window, is_continue);
   }
   //Fill gay fuuuul gay
   // pidr 823yfhcewhcih2ehc
    return 0;
}