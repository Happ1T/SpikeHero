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
    Sprite BackToMenuS(BackToMenu),BackGroundS(BackGround),ContinueS(Continue);
    float razn   = WIDTH_CAMERA/DEFAULT_WIDTH_SCREEN;
    float razn_W = WIDTH_SCREEN/DEFAULT_WIDTH_SCREEN;
    float razn_H = HEIGHT_SCREEN/DEFAULT_HEIGHT_SCREEN;
    float tempX = x;
    if (x < LEFT_LINE)
        tempX = LEFT_LINE;
    else if (x > RIGHT_LINE)
        tempX = RIGHT_LINE;

    BackGroundS.setPosition(0, 0);

    float butx = tempX + WIDTH_CAMERA/4  - 340 * razn;
    float but1y = (y - HEIGHT_CAMERA/2 + HEIGHT_CAMERA/6 * 1) + 30 * 0 *razn, but2y = y - HEIGHT_CAMERA/5 * 2, but3y = (y - HEIGHT_CAMERA/2 + HEIGHT_CAMERA/6 * 3) + 30 * 2 * razn;


    ContinueS.setPosition(butx , but1y);

    BackToMenuS.setPosition(butx ,but3y );


    BackToMenuS.setScale(Vector2f(razn,razn));
    ContinueS.setScale(Vector2f(razn,razn));


    BackToMenuS.setTextureRect(IntRect(0, 0, 680, 170));
    ContinueS.setTextureRect(IntRect(0, 0, 680, 170));


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

    if (IntRect(WIDTH_SCREEN/2 - 340*razn_W, (HEIGHT_SCREEN/6) + 30 * 1 *razn_H, 680 * razn_W, 170 * razn_H).contains(Mouse::getPosition(window))) {
        ButtonNum = 1;
        ContinueS.setTextureRect(IntRect(0, 171, 680, 170));
    }
    if (IntRect(WIDTH_SCREEN/2 - 340*razn_W, (HEIGHT_SCREEN/6 * 3) + 30 * 2 *razn_H, 680 * razn_W, 170 * razn_H).contains(Mouse::getPosition(window))) {
        ButtonNum = 3;
        BackToMenuS.setTextureRect(IntRect(0, 171, 680, 170));
    }

    if (Mouse::isButtonPressed(Mouse::Left)){
        switch(ButtonNum) {
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
    window.draw(ContinueS);
    sleep(milliseconds(50));
}
#endif //TEST1_PAUSE_MENU_H
