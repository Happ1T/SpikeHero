#ifndef TEST1_MENU_H
#define TEST1_MENU_H
#include <SFML/Network.hpp>
#include "hero.h"
#include "consts.h"
#include "view.h"
#include "entity.h"
#include "enemy.h"
#include "levl.h"
#include "bars.h"
#include "options.h"
#include "save.h"
#include "network.h"
bool check_load=false;
Texture newGameButton,continueButton, coopButton, optionsButton, menuBackground,exitButton;
Sprite newGameS,continueS, coopS, optionsS, exitS, menuBgS;
void menu(RenderWindow &window, bool &is_continue ){
    Event event;
    float emptity = 0;
    int empt = 0;
    float razn = WIDTH_SCREEN/DEFAULT_WIDTH_SCREEN;
    if(!check_load) {
        newGameButton.loadFromFile("game/texture/menu/New_Game_button.png");
        continueButton.loadFromFile("game/texture/menu/Continue_button.png");
        coopButton.loadFromFile("game/texture/menu/Coop_button.png");
        optionsButton.loadFromFile("game/texture/menu/Options_button.png");
        exitButton.loadFromFile("game/texture/menu/Exit_button.png");
        menuBackground.loadFromFile("game/texture/menu/BackGround.png");
        newGameS.setTexture(newGameButton), continueS.setTexture(continueButton), coopS.setTexture(coopButton), optionsS.setTexture(optionsButton), exitS.setTexture(exitButton), menuBgS.setTexture(menuBackground);
        check_load=true;
    }
    bool isMenu = true;
    int ButtonNum = 0;



    //////////////////////////////МЕНЮ///////////////////

        while (isMenu && window.isOpen()) {

            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }
            razn=WIDTH_SCREEN/DEFAULT_WIDTH_SCREEN;
            newGameS.setPosition(570*razn, 59*razn);
            continueS.setPosition(570*razn, (59+(170+20))*razn);
            coopS.setPosition(570*razn, (59+(170+20)*2)*razn);
            optionsS.setPosition(570*razn, (59+(170+20)*3)*razn);
            exitS.setPosition(570*razn, (59+(170+20)*4)*razn);
            menuBgS.setPosition(0, 0);

            newGameS.setScale(Vector2f(razn,razn));
            continueS.setScale(Vector2f(razn,razn));
            coopS.setScale(Vector2f(razn,razn));
            optionsS.setScale(Vector2f(razn,razn));
            exitS.setScale(Vector2f(razn,razn));
            ButtonNum = 0;


            window.clear(Color(129, 181, 221));

            newGameS.setTextureRect(IntRect(0, 171, 680, 170));
            continueS.setTextureRect(IntRect(0, 171, 680, 170));
            coopS.setTextureRect(IntRect(0, 171, 680, 170));
            optionsS.setTextureRect(IntRect(0, 171, 680, 170));
            exitS.setTextureRect(IntRect(0, 171, 680, 170));

            if (IntRect(570*razn, (59 + 10)*razn, 680*razn, 170*razn).contains(Mouse::getPosition(window))) {
                newGameS.setTextureRect(IntRect(0, 0, 680, 170));
                ButtonNum = 1;
            }
            if (IntRect(570*razn, (59 + (170 + 20)) * razn, 680*razn, 170*razn).contains(Mouse::getPosition(window))) {
                continueS.setTextureRect(IntRect(0, 0, 680, 170));
                ButtonNum = 2;
            }
            if (IntRect(570*razn, (59 + (170 + 20) * 2)*razn, 680*razn, 170*razn).contains(Mouse::getPosition(window))) {
                //coopS.setTextureRect(IntRect(0, 0, 680, 170));
                //ButtonNum = 3;
            }
            if (IntRect(570*razn, (59 + (170 + 20) * 3)*razn, 680*razn, 170*razn).contains(Mouse::getPosition(window))) {
                optionsS.setTextureRect(IntRect(0, 0, 680, 170));
                ButtonNum = 4;
            }
            if (IntRect(570*razn, (59 + (170 + 20) * 4)*razn, 680*razn, 170*razn).contains(Mouse::getPosition(window))) {
                exitS.setTextureRect(IntRect(0, 0, 680, 170));
                ButtonNum = 5;
            }
            bool check = false;
            if (Mouse::isButtonPressed(Mouse::Left)) {
                if (ButtonNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню
                if (ButtonNum == 2) { is_continue = upload(emptity, emptity, empt, 1); isMenu = false;

                }
                if (ButtonNum == 3) {

                }
                if (ButtonNum == 4) {options(window,menuBgS);}
                if (ButtonNum == 5) {window.close();isMenu = false;}
            }

            window.draw(menuBgS);
            window.draw(newGameS);
            window.draw(optionsS);
            window.draw(coopS);
            window.draw(exitS);
            window.draw(continueS);
            window.display();
            sleep(milliseconds(50));
        }
        ////////////////////////////////////////////////////
}
#endif //TEST1_MENU_H
