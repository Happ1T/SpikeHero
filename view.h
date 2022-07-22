#ifndef TEST1_VIEW_H
#define TEST1_VIEW_H
#include <SFML/Graphics.hpp>
#include "consts.h"
using namespace sf;

View view;

View SetPlayerCoordForView(float x, float y, bool isGame) {
   if(isGame) {
       float tempX = x;
       if (x < LEFT_LINE)
           tempX = LEFT_LINE;
       else if (x > RIGHT_LINE)
           tempX = RIGHT_LINE;
       view.setCenter(tempX + (three_four * SIZE_OF_BLOCK), y);
   }else view.setCenter(WIDTH_SCREEN/2,HEIGHT_SCREEN/2);
    return view;
}



#endif //TEST1_VIEW_H