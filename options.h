//
// Created by Honor MagicBook Pro on 25.05.2022.
//

#ifndef TEST1_OPTIONS_H
#define TEST1_OPTIONS_H
#include "hero.h"
#include "consts.h"
#include "view.h"
#include "entity.h"
#include "enemy.h"
#include "levl.h"
#include "bars.h"
#include "menu.h"


Event event;
int  ButtonNum;
int razreshenie = r640x360;
bool check_load1=false;
Texture rasr,rasr1920x1080,rasr640x360,apply_button,back_button,rasr1600x900,rasr1440x900,rasr1280x720;
Sprite rasrS,rasrS1920x1080, rasrS640x360,apply_button_s, back_button_s,rasrS1600x900,rasrS1440x900,rasrS1280x720;
void options(RenderWindow &window,Sprite &background) {
   float razn_W=WIDTH_SCREEN/DEFAULT_WIDTH_SCREEN;
   float razn_H=HEIGHT_SCREEN/DEFAULT_HEIGHT_SCREEN;
    bool isOptions = true;
    if(!check_load1) {
        rasr.loadFromFile("game/texture/menu/options/rasr.png");
        rasr1920x1080.loadFromFile("game/texture/menu/options/1920x1080.png");
        rasr1600x900.loadFromFile("game/texture/menu/options/1600x900.png");
        rasr1280x720.loadFromFile("game/texture/menu/options/1280x720.png");
        rasr1440x900.loadFromFile("game/texture/menu/options/1440x900.png");
        rasr640x360.loadFromFile("game/texture/menu/options/640x360.png");
        apply_button.loadFromFile("game/texture/menu/options/apply_button.png");
        back_button.loadFromFile("game/texture/menu/options/back_button.png");
        rasrS.setTexture(rasr), rasrS1920x1080.setTexture(rasr1920x1080), rasrS640x360.setTexture(rasr640x360),rasrS1440x900.setTexture(rasr1440x900),rasrS1600x900.setTexture(rasr1600x900),rasrS1280x720.setTexture(rasr1280x720), apply_button_s.setTexture(apply_button), back_button_s.setTexture(back_button);
        check_load1=true;
    }




    while (isOptions && window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        ButtonNum = 0;
        razn_W=WIDTH_SCREEN/DEFAULT_WIDTH_SCREEN;
        razn_H=HEIGHT_SCREEN/DEFAULT_HEIGHT_SCREEN;
        rasrS.setPosition(20*razn_W, 20*razn_H);
        rasrS1920x1080.setPosition(1000*razn_W, 20*razn_H);
        rasrS640x360.setPosition(1000*razn_W, 20*razn_H);
        rasrS1600x900.setPosition(1000*razn_W,20*razn_H);
        rasrS1440x900.setPosition(1000*razn_W,20*razn_H);
        rasrS1280x720.setPosition(1000*razn_W,20*razn_H);
        apply_button_s.setPosition(1220*razn_W, 800*razn_H);
        back_button_s.setPosition(20*razn_W, 800*razn_H);

        rasrS.setScale(Vector2f(razn_W, razn_H));
        rasrS640x360.setScale(Vector2f(razn_W, razn_H));
        rasrS1920x1080.setScale(Vector2f(razn_W, razn_H));
        rasrS1440x900.setScale(Vector2f(razn_W, razn_H));
        rasrS1280x720.setScale(Vector2f(razn_W, razn_H));
        rasrS1600x900.setScale(Vector2f(razn_W, razn_H));
        apply_button_s.setScale(Vector2f(razn_W, razn_H));
        back_button_s.setScale(Vector2f(razn_W, razn_H));

        rasrS1920x1080.setTextureRect(IntRect(0, 0, 400, 110));
        rasrS640x360.setTextureRect(IntRect(0, 0, 400, 110));
        rasrS1280x720.setTextureRect(IntRect(0,0,400,110));
        rasrS1600x900.setTextureRect(IntRect(0,0,400,110));
        rasrS1440x900.setTextureRect(IntRect(0,0,400,110));


        window.clear(Color(129, 181, 221));
        rasrS.setTextureRect(IntRect(0, 0, 800, 100));

        apply_button_s.setTextureRect(IntRect(0, 171, 680, 170));
        back_button_s.setTextureRect(IntRect(0, 171, 680, 170));
        if (IntRect(1000*razn_W, 20*razn_H, 680*razn_W, 170*razn_H).contains(Mouse::getPosition(window))) {
            ButtonNum = 1;
        }
        if (IntRect(20*razn_W, 800*razn_H, 680*razn_W, 170*razn_H).contains(Mouse::getPosition(window))) {
            back_button_s.setTextureRect(IntRect(0, 0, 680, 170));
            ButtonNum = 2;
        }
        if (IntRect(1220*razn_W, 800*razn_H, 680*razn_W, 170*razn_H).contains(Mouse::getPosition(window))) {
            apply_button_s.setTextureRect(IntRect(0, 0, 680, 170));
            ButtonNum = 3;
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (ButtonNum == 1) {
                if (razreshenie == r640x360) razreshenie = r1920x1080;
                else razreshenie++;
                sleep(milliseconds(100));
            }
            if (ButtonNum == 2) { isOptions = false; }
            if (ButtonNum == 3) {
                switch (razreshenie) {
                    case r1920x1080:{ WIDTH_SCREEN = 1920; HEIGHT_SCREEN = 1080;} break;
                    case r640x360:  { WIDTH_SCREEN = 640;  HEIGHT_SCREEN = 360; } break;
                    case r1600x900: { WIDTH_SCREEN = 1600; HEIGHT_SCREEN = 900; } break;
                    case r1440x900: { WIDTH_SCREEN = 1440; HEIGHT_SCREEN = 900; } break;
                    case r1280x720: { WIDTH_SCREEN = 1280; HEIGHT_SCREEN = 720; } break;
                }
                WIDTH_CAMERA = WIDTH_SCREEN / 4;
                HEIGHT_CAMERA = HEIGHT_SCREEN / 4;
                three_four = (WIDTH_CAMERA / (SIZE_OF_BLOCK * 4));
                window.create(VideoMode(WIDTH_SCREEN, HEIGHT_SCREEN), "Fil gay", Style::Close);
            }

        }


        window.draw(background);
        switch (razreshenie) {
            case r1920x1080:
                window.draw(rasrS1920x1080);
                break;
            case r640x360:
                window.draw(rasrS640x360);
                break;
            case r1280x720:
                window.draw(rasrS1280x720);
                break;
            case r1440x900:
                window.draw(rasrS1440x900);
                break;
            case r1600x900:
                window.draw(rasrS1600x900);
                break;
        }
        window.draw(rasrS);
        window.draw(apply_button_s);
        window.draw(back_button_s);
        window.display();
        sleep(milliseconds(50));

    }
}
#endif //TEST1_OPTIONS_H
