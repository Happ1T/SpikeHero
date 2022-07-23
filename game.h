//
// Created by Honor MagicBook Pro on 19.05.2022.
//

#ifndef TEST1_GAME_H
#define TEST1_GAME_H
#include "hero.h"
#include "consts.h"
#include "view.h"
#include "enemy.h"
#include "enemy.h"
#include "levl.h"
#include "bars.h"
#include "menu.h"
#include "save.h"
#include "pause_menu.h"


bool game(RenderWindow &window, bool &is_continue) {

    bool isGame = true, isPause = false;
    float timer_pause = 0;
    int count_damage = 0;
    view.reset(FloatRect(0, 0, WIDTH_CAMERA, HEIGHT_CAMERA));
    TileMap locStart;
    locStart.load("game/texture/map/map.tmx", "game/texture/map/map1.png");
    Texture texturePlayer;
    texturePlayer.loadFromFile("game/texture/player/adventurer.png");

    Texture textureSkeleton;
    textureSkeleton.loadFromFile("game/texture/enemy/skeleton.png");

    /////////////////////////////// OBJECTS /////////////////////////////////////////////////////////////////////////////////////////////////////////

    Object playerObject = locStart.getObject("player");

    Event event;
    Bars playerHPBar;

    Hero player(playerObject.rect.left, playerObject.rect.top, playerObject.rect.width, playerObject.rect.height, "player", locStart, texturePlayer);

    list<Enemy*> enemyList;
    list<Enemy*>::iterator it;

    vector<Object> enemy = locStart.getObjectsByName("skeleton");
    for (int i = 0; i < enemy.size(); i++) {
        enemyList.push_back(new Enemy(enemy[i].rect.left, enemy[i].rect.top, enemy[i].rect.width, enemy[i].rect.height, "skeleton", locStart, textureSkeleton));
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////UPLOAD//////////////////////////////////////////////////////////////////////////////
    if (is_continue) {
        upload(player.x, player.y, player.health, 1);
        is_continue = false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Clock clock;
    float timeS = 0;

    while (window.isOpen() && isGame) {

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                save(player.x, player.y, player.health, 1);
                window.close();
            }
        }

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 1000;

        if (time > 16) time = 14;
        Event event;
        timer_pause += time;
        ////////////////////////////////////////EXIT////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (Keyboard::isKeyPressed(sf::Keyboard::Escape) && timer_pause > 100) {
            isPause = !isPause;
            timer_pause = 0;
            ButtonNum1 = 1;
        }
        if (!isPause) {
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (player.health < 1) isGame = false;
            ///////////////////////////////////ZOOM/////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (Keyboard::isKeyPressed(sf::Keyboard::G) && (ZOOM > (-10))) {
                ZOOM -= 1;
                WIDTH_CAMERA /= 1.01;
                HEIGHT_CAMERA /= 1.01;
            }
            if (Keyboard::isKeyPressed(sf::Keyboard::H) && (ZOOM < 25 * DEFAULT_WIDTH_SCREEN / WIDTH_SCREEN)) {
                ZOOM += 1;
                WIDTH_CAMERA *= 1.01;
                HEIGHT_CAMERA *= 1.01;
            }
            LEFT_LINE = (SIZE_OF_BLOCK) * ((WIDTH_CAMERA / (2 * SIZE_OF_BLOCK) - three_four + 1));
            RIGHT_LINE = (WIDTH_MAP - ((WIDTH_CAMERA / (2 * SIZE_OF_BLOCK) + three_four + 1))) * SIZE_OF_BLOCK;
            view.reset(FloatRect(0, 0, WIDTH_CAMERA, HEIGHT_CAMERA));
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            /////////////////////////////// UPDATES /////////////////////////////////////////////////////////////////////////////////////////////////////////

            player.update(time);
        }
        playerHPBar.update(player.health);


        for (it = enemyList.begin(); it != enemyList.end();) {
            Enemy *b = *it;
            (*it)->update(time);
            if ((*it)->life == false) {
                it = enemyList.erase(it);
                delete b;
            } else { it++; }

        }
        //////////////////////////////// INTERACTION /////////////////////////////////////////////////////////////////////////////////////////////////////////


        FloatRect GetRect;
        FloatRect GetRectMob;
        player.on_mob = false;
        if (player.dir) {
            GetRect = player.getRect(true, player.width_attack - player.width_simple);
        } else { GetRect = player.getRect(true, 0); }
        player.speed_animation = SPEED_ANIMATION;
        for (it = enemyList.begin(); it != enemyList.end(); it++) {

            if ((*it)->dir) { GetRectMob = (*it)->getRect(true, (*it)->width_attack - (*it)->width_simple); }
            else { GetRectMob = (*it)->getRect(true, 0); }

            if (((*it)->getRect(false, 0).intersects(player.getRect(false, 0)))) {
                if ((*it)->name == "skeleton") {
                    player.speed = SPEED_ADVENTURER / 2;
                    //player.speed_animation = SPEED_ANIMATION / 4;
                    player.on_mob = true;
                }
            }

            /////////////////////////////// ADVENTURER_ATTACK /////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (((*it)->getRect(false, 0).intersects(GetRect)) && (*it)->health > 0) {
                if (player.timer_attack > TIME_ATTACK &&
                    ((int(player.frame) >= 3 && int(player.frame) <= 5) && (player.is_attack))) {
                    (*it)->is_damage = true;
                    (*it)->health -= DAMAGE;
                    (*it)->frame = 0;
                    (*it)->speed_animation = SPEED_SKELETON_ANIMATION * 1.4;
                    player.timer_attack = 0;
                }
            }
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            /////////////////////////////// MOB_ATTACK /////////////////////////////////////////////////////////////////////////////////////////////////////////
            if ((player.getRect(false, 0).intersects(GetRectMob)) && !(*it)->is_damage) {
                if ((*it)->timer_attack > TIME_ATTACK && (*it)->frame >= 5 && (*it)->frame <= 6 &&
                    (*it)->is_attack &&
                    player.health > 0) {
                    player.is_damage = true;
                    player.health -= 10;
                    player.frame = 0;
                    if (player.health > 0) {
                        player.dy = -0.1;
                        player.speed_animation = SPEED_ANIMATION * 2;
                        if ((*it)->dir) { player.dx = -0.05; }
                        else { player.dx = 0.05; }
                    } else { (*it)->is_agr = false; }
                    (*it)->timer_attack = 0;
                }
            }
            if (!(*it)->is_attack && (*it)->health > 0 && player.health > 0) {
                if ((abs((*it)->x - player.x) <= SIZE_OF_BLOCK) &&
                    (abs((*it)->y - player.y) <= SIZE_OF_BLOCK * 2) && (*it)->is_agr) {
                    (*it)->is_attack = true;
                    (*it)->frame = 0;
                    (*it)->dx = 0;
                    (*it)->speed_animation = SPEED_SKELETON_ANIMATION / 1.3;
                } else if (abs((*it)->x - player.x) < 8 * SIZE_OF_BLOCK &&
                           (abs((*it)->y - player.y) < SIZE_OF_BLOCK * 5) && player.health > 0) {
                    (*it)->is_agr = true;
                    (*it)->speed = SPEED_SKELETON * 4;
                    (*it)->speed_animation = SPEED_SKELETON_ANIMATION * 4;
                    if (player.x - (*it)->x > 0) {
                        (*it)->dir = false;
                        (*it)->dx = (*it)->speed;
                    } else {
                        (*it)->dir = true;
                        (*it)->dx = -(*it)->speed;
                    }
                } else if (((abs((*it)->x - player.x) >= 8 * SIZE_OF_BLOCK ||
                             (abs((*it)->y - player.y) >= SIZE_OF_BLOCK * 5)) && (*it)->is_agr) ||
                           player.health <= 0) {
                    (*it)->is_agr = false;
                    (*it)->dx = SPEED_SKELETON;
                    (*it)->speed_animation = SPEED_SKELETON_ANIMATION;
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    window.setView(view);
    window.clear(Color(77, 83, 140));
    window.draw(locStart);
    window.draw(player.sprite);

    for (it = enemyList.begin(); it != enemyList.end(); it++) {
        window.draw((*it)->sprite);
    }

    playerHPBar.draw(window);

    if (isPause) { pauseMenu(window, player.x, player.y, time, isPause, isGame, player.health); }

    window.display();
    sleep(milliseconds(7));
}



    if  (ZOOM > (1)) {
        while(ZOOM!=1){
        ZOOM -= 1;
        WIDTH_CAMERA /= 1.01;
        HEIGHT_CAMERA /= 1.01;
        }
    }
    if (ZOOM < 1) {
        while(ZOOM!=1)
        {
        ZOOM += 1;
        WIDTH_CAMERA *= 1.01;
        HEIGHT_CAMERA *= 1.01;
        }
    }
    LEFT_LINE = (SIZE_OF_BLOCK) * ((WIDTH_CAMERA / (2 * SIZE_OF_BLOCK) - three_four + 1));
    RIGHT_LINE = (WIDTH_MAP - ((WIDTH_CAMERA / (2 * SIZE_OF_BLOCK) + three_four + 1))) * SIZE_OF_BLOCK;
    view.reset(FloatRect(0, CENTER, WIDTH_CAMERA, HEIGHT_CAMERA));
    view.reset(FloatRect(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN));
    SetPlayerCoordForView(0, 0, false);
    window.setView(view);
    window.getDefaultView();

    return 0;
}
#endif //TEST1_GAME_H
