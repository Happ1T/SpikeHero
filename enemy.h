#ifndef TEST1_ENEMY_H
#define TEST1_ENEMY_H
#include "entity.h"
#include "levl.h"
class Enemy: public Entity{
public:
    float time_dx = 0;
    bool is_stay = false;
    Enemy(int X, int Y, int W, int H, String Name,TileMap &lev, Texture &texture): Entity(X,Y,W,H,Name, texture){
         obj=lev.getObjectsByName("floor");
        if (Name == "skeleton"){
            health = 100;
            damage = 10;
            speed = SPEED_SKELETON;
            dx = speed;
            speed_animation = SPEED_SKELETON_ANIMATION;
            height_attack = HEIGHT_OF_SKELETON_ATTACK;
            width_attack = WIDTH_OF_SKELETON_ATTACK;
        }
        dy = 0; frame=0; is_damage = false; dir = true; width_simple = width;
    }

    void InteractWorldEnemy(int dir) {
        for (int i = 0; i < obj.size(); i++)
            if (getRect(false,0).intersects(obj[i].rect))
            {
                if (obj[i].name == "floor") {
                    if (dy > 0 && dir == 1) {
                        y = obj[i].rect.top - height;
                        dy = 0;
                        is_ground = true;
                    }
                    if (dy < 0 && dir == 1) {
                        y = y = obj[i].rect.top + obj[i].rect.height;
                        dy = 0;
                    }
                    if (dx > 0 && dir == 0) {
                        x = obj[i].rect.left - width;
                        dx = -dx;
                        dir = !dir;
                    }
                    if (dx < 0 && dir == 0) {
                        x = obj[i].rect.left + obj[i].rect.width;
                        dx = -dx;
                        dir = !dir;
                    }
                }
            } else {
                is_ground = false;
            }
    }

    void update(float time){
        timer_attack += time;
        if (name == "skeleton") {
            if (!is_agr) {
                move_timer += time;
                if (move_timer > 5000 && !is_stay) {
                    is_stay = true;
                    move_timer = 0;
                    time_dx = dx;
                    dx = 0;
                    dir = !dir;
                } else if (move_timer > 5000 && is_stay) {
                    dx = -time_dx;
                    is_stay = false;
                    move_timer = 0;
                }
            }
            InteractWorldEnemy(0);
            if (!is_ground) {
                dy += 0.0005 * time;
            }

            x += dx * time;
            y += dy * time;

            InteractWorldEnemy(1);
            frame += speed_animation*time;
            flag = false;
            if( health <= 0 ) {
                flag = true;
                speed_animation=SPEED_SKELETON_ANIMATION;
                dx=0;
                if (frame > 15){ life=false; }
                if (dir)
                    sprite.setTextureRect(IntRect(width * int(frame + 1), height * 3, -width, height));
                else
                    sprite.setTextureRect(IntRect(width * int(frame), height * 3, width, height));
            }
            else if (frame > 12) { frame = 0;  is_attack = false;}

            else if (is_damage){
                flag = true;
                if (frame > 8) {
                    is_damage = false;
                    frame = 0;
                    is_attack = false;
                    speed_animation=SPEED_SKELETON_ANIMATION;
                    flag = false;
                }
                if (dir)
                    sprite.setTextureRect(IntRect(width * int(frame + 1) , height * 2, -width, height));
                else
                    sprite.setTextureRect(IntRect(width * int(frame) , height * 2 , width, height));
            }
            else if(is_agr && is_attack){
                flag = true;
                if (dir) {
                    sprite.setTextureRect(IntRect(width_attack * (int(frame) + 1), height * 5, -width_attack, height));
                } else {
                    sprite.setTextureRect(IntRect((width_attack * int(frame)), height * 5, width_attack, height));
                }
            }
            else if (is_agr){
                flag = true;
                if (dir) {
                    sprite.setTextureRect(IntRect(width * (int(frame) + 1), height * 4, -width, height));
                } else {
                    sprite.setTextureRect(IntRect((width * int(frame)), height * 4, width, height));
                }
            }
            if (!flag) {
                if (dx == 0) {

                    if (dir)
                        sprite.setTextureRect(IntRect(width * int(frame + 1), height * 0, -width, height));
                    else
                        sprite.setTextureRect(IntRect(width * int(frame), height * 0, width, height));
                } else if (dx > 0) {
                    sprite.setTextureRect(IntRect(width * int(frame), height * 1, width, height));
                } else if (dx < 0) {
                    sprite.setTextureRect(IntRect(width * int(frame + 1), height * 1, -width, height));
                }
            }
            if(dir && is_attack && !is_damage)
                sprite.setPosition(x-(width_attack-width_simple), y);
            else
                sprite.setPosition(x, y);

        }
    }
};
#endif //TEST1_ENEMY_H
