#ifndef TEST1_HERO_H
#define TEST1_HERO_H
#include "consts.h"
#include "view.h"
#include "entity.h"
#include "levl.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Hero:public Entity {
public:
    int countJump = 0, stamina, line = 0;
    bool is_shift = true, on_mob = false;
    float timerJump = 0;
    Hero(int X, int Y, int W, int H, String Name,TileMap &lev,Texture &texture ) : Entity(X, Y, W, H, Name,texture) {
        obj = lev.getAllObjects();

            health = 100;
            width_attack = WIDTH_ATTACK_ADVENTURE;
            height_attack = HEIGTH_ATTACK_ADVENTURE;

        width_simple = width;
        dy=0;frame=0;

    }

    void control() {
        if (Keyboard::isKeyPressed(Keyboard::LShift)) {
            is_shift = true;

        }
        if (!is_shift && !on_mob && !is_damage) {
            speed = SPEED_ADVENTURER;
            speed_animation = SPEED_ANIMATION;

        } else if (is_shift && !on_mob && !is_damage)  {
            speed = SPEED_ADVENTURER * 1.5;
            speed_animation = SPEED_ANIMATION * 2;
        }
        is_shift = false;
        if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
            if (is_attack)
            {frame = 0;  is_attack = false; width = width_simple; }
            dx = -speed;
            dir = true;

        } else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
            if (is_attack)
            {frame = 0;  is_attack = false; width = width_simple; }
            dx = speed;
            dir = false;

        } else if (Keyboard::isKeyPressed(Keyboard::F)) {
            if (!is_attack) {
                frame = 0;
                is_attack = true;
            }
            dx = 0;
        } else if (!is_damage) {
            dx = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space) ) {
            if (timerJump == 0) {
                dy = JUMP_RANGE;
                countJump = 1;
            } else if (timerJump > 200 && countJump == 1) {
                dy = JUMP_RANGE;
                countJump = 2;
            }
            is_ground = false;

        }
    }

    void update(float time) {
        timer_attack += time;
        control();

        if (!is_ground) {
            timerJump += time;
            dy += 0.0005 * time / 2;
        }
        x += dx * time;
        InteractWorld(0);
        y += dy * time;
        InteractWorld(1);



    dy += 0.0005 * time/2;


        flag = false;
        if (health <= 0) { speed_animation=SPEED_ANIMATION/2;}
        frame += speed_animation * time;
        if (is_attack) {
            flag=true;
            if (frame > 7) {
                frame = 0;
                is_attack = false;
                flag = false;
            }
            if (dir) {
                sprite.setTextureRect(IntRect(width_attack * (int(frame) + 1), height * 3, -width_attack, height));
            } else {
                sprite.setTextureRect(IntRect((width_attack * int(frame)), height * 3, width_attack, height));
            }
        }
        else if (health<=0){

            dx=0;flag=true;
            if (frame > 8){ life=false; }
            if (dir) {

                sprite.setTextureRect(IntRect(width_simple * int(frame + 1), height * 5, -width_simple, height));
            } else {
                sprite.setTextureRect(IntRect(width_simple * int(frame), height * 5, width_simple, height));
            }
        }
        else if(is_damage){
            flag=true;
            if(frame>4){
                is_damage=false;
                is_attack=false;
                dx=speed;
                frame=0;
                flag=false;
            }
            if (dir) {
                sprite.setTextureRect(IntRect(width_simple * int(frame + 1), height * 4, -width_simple, height));
            } else {
                sprite.setTextureRect(IntRect(width_simple * int(frame), height * 4, width_simple, height));
            }
        }
        else if (timerJump > 0) {
            flag = true;
            if (countJump == 2) {
                frame = 0.1;
                countJump = 0;
            }
            if (frame > 7)
                frame = 7;
            if (dir) {
                sprite.setTextureRect(IntRect(width_simple * int(frame + 1), height * 2, -width_simple, height));
            } else {
                sprite.setTextureRect(IntRect(width_simple * int(frame), height * 2, width_simple, height));
            }
        } else if (dx > 0) {
            flag=true;
            if (frame > 6){
                frame = 0;
                flag=false;}
            sprite.setTextureRect(IntRect((width_simple) * (int(frame)), height * 1, width_simple, height));
        } else if (dx < 0) {
            flag=true;
            if (frame > 6){
                frame = 0;
                flag = false;}
            sprite.setTextureRect(IntRect((width_simple) * (int(frame) + 1), height * 1, -width_simple, height));
        }
        if (!flag) {
            if (frame > 4)
                frame -= 4;
            if (dir)
                sprite.setTextureRect(IntRect(width_simple * (int(frame) + 1), 0, -width_simple, height));
            else
                sprite.setTextureRect(IntRect((width_simple * int(frame)), 0, width_simple, height));
        }
        if(dir && is_attack)
            sprite.setPosition(x-(width_attack-width_simple), y);
        else
            sprite.setPosition(x, y);



        SetPlayerCoordForView(x, y, true);

    }

    void InteractWorld(int dir) {
        for (int i = 0; i < obj.size(); i++)
            if (getRect(false,0).intersects(obj[i].rect))
            {
                if(obj[i].name=="floor"){
                    if (dy > 0 && dir == 1) {
                        y = obj[i].rect.top - height;
                        dy = 0;
                        is_ground = true;
                        timerJump = 0;
                        countJump = 0;
                    }
                    if (dy < 0 && dir == 1) {
                        y = y = obj[i].rect.top + obj[i].rect.height;
                        dy = 0;
                    }
                    if (dx > 0 && dir == 0) {
                        x = obj[i].rect.left - width;
                        dx = 0;
                    }
                    if (dx < 0 && dir == 0) {
                        x = obj[i].rect.left + obj[i].rect.width;
                        dx = 0;
                    }
                }
            }
            else {

                is_ground = false;
            }

    }
};

#endif//TEST1_HERO_H

