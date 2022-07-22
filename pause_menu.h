//
// Created by Honor MagicBook Pro on 05.06.2022.
//

#ifndef TEST1_PAUSE_MENU_H
#define TEST1_PAUSE_MENU_H
#include "hero.h"
#include "consts.h"
#include "view.h"
#include "save.h"

float timer_press = 0;
int ButtonNum1 = 1;
void pauseMenu(RenderWindow &window,float x,float y, float time, bool &isPause, bool &isGame,int health){

    Texture BackGround,BackToMenu,Continue,Coop;
    BackToMenu.loadFromFile("game/texture/pause menu/back_to_menu_button.png");
    BackGround.loadFromFile("game/texture/pause menu/BackGround.png");
    Continue.loadFromFile("game/texture/pause menu/continue_button.png");
    Coop.loadFromFile("game/texture/pause menu/Coop_button.png");
    Sprite BackToMenuS(BackToMenu),BackGroundS(BackGround),ContinueS(Continue),CoopS(Coop);
    float razn=WIDTH_CAMERA/DEFAULT_WIDTH_SCREEN;
    float razn_s = WIDTH_SCREEN/DEFAULT_WIDTH_SCREEN;

    float tempX = x;
    if (x < LEFT_LINE)
        tempX = LEFT_LINE;
    else if (x > RIGHT_LINE)
        tempX = RIGHT_LINE;

    BackGroundS.setPosition(0, 0);

    float but1x = tempX + (three_four * SIZE_OF_BLOCK * razn),       but1y = y - 350*razn;
    float but2x = tempX + (three_four * SIZE_OF_BLOCK * razn),       but2y = y - 100*razn;
    float but3x = tempX + (three_four * SIZE_OF_BLOCK * razn),       but3y = y + 150*razn;

    ContinueS.setPosition(but1x , but1y);
    CoopS.setPosition( but2x, but2y);
    BackToMenuS.setPosition(but3x ,but3y );


    BackToMenuS.setScale(Vector2f(razn,razn));
    ContinueS.setScale(Vector2f(razn,razn));
    CoopS.setScale(Vector2f(razn,razn));

    BackToMenuS.setTextureRect(IntRect(0, 0, 680, 170));
    ContinueS.setTextureRect(IntRect(0, 0, 680, 170));
    CoopS.setTextureRect(IntRect(0, 0, 680, 170));

    timer_press += time;
    if (timer_press > 50) {
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (ButtonNum1 == 1) ButtonNum1 = 3;
            else ButtonNum1 -= 1;
            timer_press = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (ButtonNum1 == 3) ButtonNum1 = 1;
            else ButtonNum1 += 1;
            timer_press = 0;
        }

    }
    switch(ButtonNum1) {
        case 1:{
            ContinueS.setTextureRect(IntRect(0, 171, 680, 170));
        }  break;
        case 2:{
            CoopS.setTextureRect(IntRect(0, 171, 680, 170));
        }  break;
        case 3:{
            BackToMenuS.setTextureRect(IntRect(0, 171, 680, 170));
        }break;
    }

    if (Keyboard::isKeyPressed(Keyboard::Enter)){
        switch(ButtonNum1) {
            case 1:{
                isPause = false;

            }  break;
            case 2:{

            }  break;
            case 3:{
                save(x,y,health,0);
                isGame=false;

            }break;
        }
    }

    window.draw(BackGroundS);
    window.draw(BackToMenuS);
    window.draw(CoopS);
    window.draw(ContinueS);
}
#endif //TEST1_PAUSE_MENU_H
